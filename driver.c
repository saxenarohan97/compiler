#include "lexer.h"
#include "parser.h"
#include <string.h>

char * tokens[] = {"ASSIGNOP", "COMMENT", "FUNID", "ID", "NUM", "RNUM",
"STR", "END", "INT", "REAL", "STRING", "MATRIX", "MAIN", "SQO", "SQC", "OP",
"CL", "SEMICOLON", "COMMA", "IF", "ELSE", "ENDIF", "READ", "PRINT",
"FUNCTION", "PLUS", "MINUS", "MUL", "DIV", "SIZE", "AND", "OR", "NOT", "LT",
"LE", "EQ", "GT", "GE", "NE"};

void print_lexeme(token id)
{
    char lexeme[10];

    switch(id)
    {
        case ASSIGNOP:
            strcpy(lexeme, "=");
        break;

        case END:
            strcpy(lexeme, "end");
        break;

        case INT:
            strcpy(lexeme, "int");
        break;

        case REAL:
            strcpy(lexeme, "real");
        break;

        case STRING:
            strcpy(lexeme, "string");
        break;

        case MATRIX:
            strcpy(lexeme, "matrix");
        break;

        case MAIN:
            strcpy(lexeme, "main");
        break;

        case SQO:
            strcpy(lexeme, "[");
        break;

        case SQC:
            strcpy(lexeme, "]");
        break;

        case OP:
            strcpy(lexeme, "(");
        break;

        case CL:
            strcpy(lexeme, ")");
        break;

        case SEMICOLON:
            strcpy(lexeme, ";");
        break;

        case COMMA:
            strcpy(lexeme, ",");
        break;

        case IF:
            strcpy(lexeme, "if");
        break;

        case ELSE:
            strcpy(lexeme, "else");
        break;

        case ENDIF:
            strcpy(lexeme, "endif");
        break;

        case READ:
            strcpy(lexeme, "read");
        break;

        case PRINT:
            strcpy(lexeme, "print");
        break;

        case FUNCTION:
            strcpy(lexeme, "function");
        break;

        case PLUS:
            strcpy(lexeme, "+");
        break;

        case MINUS:
            strcpy(lexeme, "-");
        break;

        case MUL:
            strcpy(lexeme, "*");
        break;

        case DIV:
            strcpy(lexeme, "/");
        break;

        case SIZE:
            strcpy(lexeme, "@");
        break;

        case AND:
            strcpy(lexeme, ".and.");
        break;

        case OR:
            strcpy(lexeme, ".or.");
        break;

        case NOT:
            strcpy(lexeme, ".not.");
        break;

        case LT:
            strcpy(lexeme, "<");
        break;

        case LE:
            strcpy(lexeme, "<=");
        break;

        case EQ:
            strcpy(lexeme, "==");
        break;

        case GT:
            strcpy(lexeme, ">");
        break;

        case GE:
            strcpy(lexeme, ">=");
        break;

        case NE:
            strcpy(lexeme, "=/=");
        break;

        default:
            printf("Error");
        break;
    }

    printf("%s \n", lexeme);
}

int main(int argc, char * argv[])
{
    int choice;

    printf("Do you want to: \n");
    printf("1. Remove comments \n");
    printf("2. Get tokens \n");
    printf("3. Generate parse table \n");
    printf("Note: remove comments (via option 1) before passing the file to lexer! \n");
    printf("Please enter your choice: ");

    scanf("%d", &choice);

    FILE * input = fopen(argv[1], "r");

    switch(choice)
    {
        case 1:
        {
            char output[1024];
            removeComments(input, output);

            int i;

            printf("Code without comments: \n\n");

            printf("%s", output);
        }
        break;

        case 2:
        {
            int i;

            tokenInfo * token;

            while((token = getNextToken(input)))
            {
                if(token->id == ERROR_SYMBOL)
                    printf("Line number: %d, Lexical error: Unknown symbol %c \n", token->lineNum, token->lexeme[0]);

                else if(token->id == ERROR_PATTERN)
                    printf("Line number: %d, Lexical error: Unknown pattern %s \n", token->lineNum, token->lexeme);

                else if(token->id == ERROR_ID_LENGTH)
                    printf("Line number: %d, Lexical error: Identifier is longer than the prescribed length \n", token->lineNum);

                else if(token->id == ERROR_STR_LENGTH)
                    printf("Line number: %d, Lexical error: String is longer than the prescribed length \n", token->lineNum);

                else
                {
                    printf("Line number: %d, Token ID: %s, ", token->lineNum, tokens[token->id]);

                    if(!(token->lexeme))
                    {
                        printf("Lexeme: ");
                        print_lexeme(token->id);
                    }

                    else
                        printf("Lexeme: %s \n", token->lexeme);

                }

                printf("\n");
            }

            printf("Lexer reached end of file \n");
        }
        break;

        case 3:
            createParseTable();
        break;

        default:
            printf("Incorrect choice entered");
        break;
    }

    fclose(input);

    return 0;
}
