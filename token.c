#include "lexer.c"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 128

int line = 1;
char current = '^';

tokenInfo getNextToken(FILE * fp)
{
    int state = 1;
    int i = 0;
    char lexeme[LENGTH];

    memset(lexeme, '\0', LENGTH);

    tokenInfo temp;

    if(current == '^')
        current = getNextChar(fp);

    while(isspace(current))
    {
        if(current == '\n')
            line++;

        current = getNextChar(fp);
    }

    while(1)
    {
        /* `current` has been read already before this – in the first iteration
        and in the subsequent iterations */

        // Optimistically put current character in buffer. Remove if it's incorrect
        lexeme[i++] = current;

        switch(state)
        {

            case 1:

                switch(current)
                {
                    case '=':
                        state = 2;
                        current = getNextChar(fp);
                    break;

                    case '_':
                        state = 8;
                        current = getNextChar(fp);
                    break;

                    case 'a'...'z':
                    case 'A'...'Z':
                        state = 10;
                        current = getNextChar(fp);
                    break;

                    case '0'...'9':
                        state = 12;
                        current = getNextChar(fp);
                    break;

                    case '.':
                        state = 45;
                        current = getNextChar(fp);
                    break;

                    case '"':
                        state = 27;
                        current = getNextChar(fp);
                    break;

                    case '[':
                        state = 30;

                        temp.id = SQO;
                        temp.lexeme = NULL;
                        temp.lineNum = line;

                        current = '^';

                        return temp;

                    case ']':
                        state = 31;

                        temp.id = SQC;
                        temp.lexeme = NULL;
                        temp.lineNum = line;

                        current = '^';

                        return temp;

                    case '(':
                        state = 32;

                        temp.id = OP;
                        temp.lexeme = NULL;
                        temp.lineNum = line;

                        current = '^';

                        return temp;

                    case ')':
                        state = 33;

                        temp.id = CL;
                        temp.lexeme = NULL;
                        temp.lineNum = line;

                        current = '^';

                        return temp;

                    case ';':
                        state = 34;

                        temp.id = SEMICOLON;
                        temp.lexeme = NULL;
                        temp.lineNum = line;

                        current = '^';

                        return temp;

                    case ',':
                        state = 35;

                        temp.id = COMMA;
                        temp.lexeme = NULL;
                        temp.lineNum = line;

                        current = '^';

                        return temp;

                    case '+':
                        state = 36;

                        temp.id = PLUS;
                        temp.lexeme = NULL;
                        temp.lineNum = line;

                        current = '^';

                        return temp;

                    case '-':
                        state = 37;

                        temp.id = MINUS;
                        temp.lexeme = NULL;
                        temp.lineNum = line;

                        current = '^';

                        return temp;

                    case '*':
                        state = 38;

                        temp.id = MUL;
                        temp.lexeme = NULL;
                        temp.lineNum = line;

                        current = '^';

                        return temp;

                    case '/':
                        state = 39;

                        temp.id = DIV;
                        temp.lexeme = NULL;
                        temp.lineNum = line;

                        current = '^';

                        return temp;

                    case '@':
                        state = 40;

                        temp.id = SIZE;
                        temp.lexeme = NULL;
                        temp.lineNum = line;

                        current = '^';

                        return temp;

                    case '<':
                        state = 41;
                        current = getNextChar(fp);
                    break;

                    case '>':
                        state = 43;
                        current = getNextChar(fp);
                    break;

                    default:

                        lexeme[--i] = '\0';
                        printf("Line number: %d, Lexical error: Unknown symbol %c \n", line, current);
                        exit(0);

                    break;
                }
            break;

            case 2:

                switch(current)
                {
                    case '=':
                        state = 3;

                        temp.id = EQ;
                        temp.lexeme = NULL;
                        temp.lineNum = line;

                        current = '^';

                        return temp;
                    break;

                    case '/':
                        state = 4;
                        current = getNextChar(fp);
                    break;

                    default:
                        lexeme[--i] = '\0';

                        temp.id = ASSIGNOP;
                        temp.lexeme = NULL;
                        temp.lineNum = line;

                        return temp;
                    break;
                }
            break;

            case 4:

                if(current == '=')
                {
                    state = 5;

                    temp.id = NE;
                    temp.lexeme = NULL;
                    temp.lineNum = line;

                    current = '^';

                    return temp;
                }

                else
                {
                    printf("Line number: %d, Lexical error: Unknown pattern %s \n", line, lexeme);
                    exit(0);
                }

            break;

            case 8:

                if(isalpha(current))
                {
                    state = 9;
                    current = getNextChar(fp);
                }

                else
                {
                    printf("Line number: %d, Lexical error: Unknown pattern %s \n", line, lexeme);
                    exit(0);
                }

            break;

            case 9:

                if(isalpha(current) || isdigit(current))
                    current = getNextChar(fp);

                else
                {
                    lexeme[--i] = '\0';

                    temp.id = FUNID;
                    temp.lineNum = line;
                    temp.lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp.lexeme, lexeme);

                    return temp;
                }

            break;

            case 10:

                if(isalpha(current))
                    current = getNextChar(fp);

                else if(isdigit(current))
                {
                    state = 11;

                    if(strlen(lexeme) > 20)
                    {
                        printf("Line number: %d, Lexical error: Identifier is longer than the prescribed length \n", line);
                        exit(0);
                    }

                    temp.id = ID;
                    temp.lineNum = line;
                    temp.lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp.lexeme, lexeme);

                    current = '^';

                    return temp;
                }

                else
                {
                    lexeme[--i] = '\0';

                    if(strlen(lexeme) > 20)
                    {
                        printf("Line number: %d, Lexical error: Identifier is longer than the prescribed length \n", line);
                        exit(0);
                    }

                    temp.id = ID;
                    temp.lineNum = line;
                    temp.lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp.lexeme, lexeme);

                    return temp;
                }

            break;

            case 12:

                if(isdigit(current))
                    current = getNextChar(fp);

                else if(current == '.')
                {
                    state = 13;
                    current = getNextChar(fp);
                }

                else
                {
                    lexeme[--i] = '\0';

                    temp.id = NUM;
                    temp.lineNum = line;
                    temp.lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp.lexeme, lexeme);

                    return temp;
                }

            break;

            case 27:

                if(islower(current))
                {
                    state = 28;
                    current = getNextChar(fp);
                }

                else
                {
                    printf("Line number: %d, Lexical error: Unknown pattern %s \n", line, lexeme);
                    exit(0);
                }

            break;

            case 28:

                if(islower(current))
                    current = getNextChar(fp);

                else if(current == '"')
                {
                    temp.id = STR;
                    temp.lineNum = line;
                    temp.lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp.lexeme, lexeme);

                    current = '^';

                    return temp;
                }

                else
                {
                    printf("Line number: %d, Lexical error: Unknown pattern %s \n", line, lexeme);
                    exit(0);
                }

            break;
        }
    }
}

int main()
{
    FILE * fp = fopen("testcases/test.txt", "r");

    int i;

    tokenInfo token;

    for(i = 1; i <= 5; i++)
    {
        token = getNextToken(fp);
        printf("%d \n", token.id);

        if(token.lexeme)
            printf("%s \n", token.lexeme);

        printf("\n");
    }

    return 0;
}
