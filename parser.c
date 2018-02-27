#include "lexer.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>

extern char * terms[];

int table[44][39];

int grammar[86][17];
int first[86][17];
int follow[44][17];

char c;

void createParseTable()
{
    int i = 0, j = 0;

    for(i = 0; i < 86; i++)
    {
        for(j = 0; j < 17; j++)
        {
            grammar[i][j] = 0;
            first[i][j] = 0;
        }
    }

    for(i = 0; i < 44; i++)
    {
        for(j = 0; j < 17; j++)
            follow[i][j] = 0;
    }

    for(i = 0; i < 44; i++)
    {
        for(j = 0; j < 39; j++)
            table[i][j] = 0;
    }

    // Load grammar

    FILE * fgram = fopen("encoded_grammar", "r");

    i = j = 0;

    while(fscanf(fgram, "%d%c", &grammar[i][j++], &c) == 2)
    {
        if(c == '\n')
        {
            i++;
            j = 0;
        }
    }

    fclose(fgram);

    FILE * ffirst = fopen("encoded_rule_first", "r");

    i = j = 0;

    while(fscanf(ffirst, "%d%c", &first[i][j++], &c) == 2)
    {
        if(c == '\n')
        {
            i++;
            j = 0;
        }
    }

    fclose(ffirst);

    FILE * ffollow = fopen("encoded_follow", "r");

    i = j = 0;

    while(fscanf(ffollow, "%d%c", &follow[i][j++], &c) == 2)
    {
        if(c == '\n')
        {
            i++;

            if(i == 18)
                i++;

            j = 0;
        }
    }

    fclose(ffollow);

    for(i = 0; i < 86; i++)
    {
        int terminal, nonTerminal, flag = 0;

        nonTerminal = grammar[i][0] - 1;

        for(j = 1; first[i][j] != 0; j++)
        {
            terminal = first[i][j] - 45;

            if(terminal == 8)
                flag = 1;

            if(table[nonTerminal][terminal] != 0)
            {
                printf("Here %d: ", i + 1);
                printf("NT: %s, T: %s \n", terms[nonTerminal], terms[terminal + 44]);
            }

            table[nonTerminal][terminal] = i + 1;
        }

        if(flag)
        {
            for(j = 1; follow[nonTerminal][j] != 0; j++)
            {
                terminal = follow[nonTerminal][j] - 45;

                if(table[nonTerminal][terminal] != 0)
                {
                    printf("%d: ", i + 1);
                    printf("NT: %d, T: %d \n", nonTerminal, terminal);
                }

                table[nonTerminal][terminal] = i + 1;
            }
        }
    }

    // for(i = 0; i < 44; i++)
    // {
    //     for(j = 0; j < 39; j++)
    //         printf("%2d ", table[i][j]);
    //
    //     printf("\n");
    // }
}

void parseInputSourceCode(FILE * fp)
{
    tokenInfo * token;

    Node * top = NULL;

    push(&top, 19);
    printList(top);

    // getNextToken returns things in enum indexing. `grammar` is indexed as per mapping used for encoding

    token = getNextToken(fp);

    while(token)
    {
        if(top->id == 53)
        {
            pop(&top);
            continue;
        }

        int terminal = (token->id) + 44;

        if(terminal > 82)
        {
            printf("Lexical error. Not continuing to parse. \n");
            return;
        }

        int topTerm = top->id;

        if(topTerm > 44)
        {
            if(topTerm == terminal + 1)
            {
                pop(&top);
                token = getNextToken(fp);
            }

            else
            {
                printf("Parsing error 1: %d %d \n", topTerm, terminal + 1);
                return;
            }
        }

        else
        {
            int rule = table[topTerm - 1][terminal - 44];

            if(rule == 0)
            {
                printf("Parsing error 2: %s %s \n", terms[topTerm - 1], terms[terminal]);
                return;
            }

            pop(&top);

            int index;

            printf("Rule: %d \n", rule);

            for(index = 1; grammar[rule - 1][index] != 0; )
                index++;

            for(index-=1 ; index >= 1; index--)
                push(&top, grammar[rule - 1][index]);

            topTerm = top->id;

            if(topTerm == terminal + 1)
            {
                pop(&top);
                token = getNextToken(fp);
            }

            printList(top);
        }
    }
}


// int main()
// {
//     createParseTable();
//
//     FILE * input = fopen("testcases/testcase1.txt", "r");
//
//     parseInputSourceCode(input);
//
//     fclose(input);
//
//     return 0;
// }
