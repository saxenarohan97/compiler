#include "lexer.c"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 128

char * tokens[] = {"ASSIGNOP", "COMMENT", "FUNID", "ID", "NUM", "RNUM",
"STR", "END", "INT", "REAL", "STRING", "MATRIX", "MAIN", "SQO", "SQC", "OP",
"CL", "SEMICOLON", "COMMA", "IF", "ELSE", "ENDIF", "READ", "PRINT",
"FUNCTION", "PLUS", "MINUS", "MUL", "DIV", "SIZE", "AND", "OR", "NOT", "LT",
"LE", "EQ", "GT", "GE", "NE"};

int line = 1;
char current = '^';

tokenInfo * getNextToken(FILE * fp)
{
    int state = 1;
    int i = 0;
    char lexeme[LENGTH];

    memset(lexeme, '\0', LENGTH);

    tokenInfo * temp = malloc(sizeof(tokenInfo));

    if(current == '^')
        current = getNextChar(fp);

    while(isspace(current))
    {
        if(current == '\n')
            line++;

        current = getNextChar(fp);
    }

    if(current == '\0')
        return NULL;

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

                        temp->id = SQO;
                        temp->lexeme = NULL;
                        temp->lineNum = line;

                        current = '^';

                        return temp;

                    case ']':
                        state = 31;

                        temp->id = SQC;
                        temp->lexeme = NULL;
                        temp->lineNum = line;

                        current = '^';

                        return temp;

                    case '(':
                        state = 32;

                        temp->id = OP;
                        temp->lexeme = NULL;
                        temp->lineNum = line;

                        current = '^';

                        return temp;

                    case ')':
                        state = 33;

                        temp->id = CL;
                        temp->lexeme = NULL;
                        temp->lineNum = line;

                        current = '^';

                        return temp;

                    case ';':
                        state = 34;

                        temp->id = SEMICOLON;
                        temp->lexeme = NULL;
                        temp->lineNum = line;

                        current = '^';

                        return temp;

                    case ',':
                        state = 35;

                        temp->id = COMMA;
                        temp->lexeme = NULL;
                        temp->lineNum = line;

                        current = '^';

                        return temp;

                    case '+':
                        state = 36;

                        temp->id = PLUS;
                        temp->lexeme = NULL;
                        temp->lineNum = line;

                        current = '^';

                        return temp;

                    case '-':
                        state = 37;

                        temp->id = MINUS;
                        temp->lexeme = NULL;
                        temp->lineNum = line;

                        current = '^';

                        return temp;

                    case '*':
                        state = 38;

                        temp->id = MUL;
                        temp->lexeme = NULL;
                        temp->lineNum = line;

                        current = '^';

                        return temp;

                    case '/':
                        state = 39;

                        temp->id = DIV;
                        temp->lexeme = NULL;
                        temp->lineNum = line;

                        current = '^';

                        return temp;

                    case '@':
                        state = 40;

                        temp->id = SIZE;
                        temp->lexeme = NULL;
                        temp->lineNum = line;

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

                        temp->lineNum = line;
                        temp->id = ERROR_SYMBOL;
                        temp->lexeme = malloc(sizeof(char));
                        temp->lexeme[0] = lexeme[0];

                        current = '^';

                        return temp;

                    break;
                }
            break;

            case 2:
                switch(current)
                {
                    case '=':
                        state = 3;

                        temp->id = EQ;
                        temp->lexeme = NULL;
                        temp->lineNum = line;

                        current = '^';

                        return temp;
                    break;

                    case '/':
                        state = 4;
                        current = getNextChar(fp);
                    break;

                    default:
                        lexeme[--i] = '\0';

                        temp->id = ASSIGNOP;
                        temp->lexeme = NULL;
                        temp->lineNum = line;

                        return temp;
                    break;
                }
            break;

            case 4:
                if(current == '=')
                {
                    state = 5;

                    temp->id = NE;
                    temp->lexeme = NULL;
                    temp->lineNum = line;

                    current = '^';

                    return temp;
                }

                else
                {
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);
                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
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
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);
                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

            break;

            case 9:
                if(isalpha(current) || isdigit(current))
                    current = getNextChar(fp);

                else
                {
                    lexeme[--i] = '\0';

                    temp->lineNum = line;

                    if(strcmp(lexeme, "_main") == 0)
                    {
                        temp->id = MAIN;
                        temp->lexeme = NULL;
                    }

                    else
                    {
                        temp->id = FUNID;
                        temp->lexeme = malloc(strlen(lexeme) + 1);

                        strcpy(temp->lexeme, lexeme);
                    }

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
                        temp->lineNum = line;
                        temp->id = ERROR_ID_LENGTH;
                        temp->lexeme = NULL;

                        current = '^';

                        return temp;
                    }

                    temp->lineNum = line;
                    temp->lexeme = NULL;

                    int sum = 0;
                    int j;

                    for(j = 0; lexeme[j] != '\0'; j++)
                        sum += lexeme[j];

                    int flag = 0;

                    switch(sum)
                    {
                        case 311:
                            if(strcmp(lexeme, "end") == 0)
                                temp->id = END;

                            else
                                flag = 1;
                        break;

                        case 331:
                            if(strcmp(lexeme, "int") == 0)
                                temp->id = INT;

                            else
                                flag = 1;
                        break;

                        case 420:
                            if(strcmp(lexeme, "real") == 0)
                                temp->id = REAL;

                            else
                                flag = 1;
                        break;

                        case 663:
                            if(strcmp(lexeme, "string") == 0)
                                temp->id = STRING;

                            else
                                flag = 1;
                        break;

                        case 661:
                            if(strcmp(lexeme, "matrix") == 0)
                                temp->id = MATRIX;

                            else
                                flag = 1;
                        break;

                        case 207:
                            if(strcmp(lexeme, "if") == 0)
                                temp->id = IF;

                            else
                                flag = 1;
                        break;

                        case 425:
                            if(strcmp(lexeme, "else") == 0)
                                temp->id = ELSE;

                            else
                                flag = 1;
                        break;

                        case 518:
                            if(strcmp(lexeme, "endif") == 0)
                                temp->id = ENDIF;

                            else
                                flag = 1;
                        break;

                        case 412:
                            if(strcmp(lexeme, "read") == 0)
                                temp->id = READ;

                            else
                                flag = 1;
                        break;

                        case 557:
                            if(strcmp(lexeme, "print") == 0)
                                temp->id = PRINT;

                            else
                                flag = 1;
                        break;

                        case 870:
                            if(strcmp(lexeme, "function") == 0)
                                temp->id = FUNCTION;

                            else
                                flag = 1;
                        break;

                        default:
                            temp->id = ID;
                            temp->lexeme = malloc(strlen(lexeme) + 1);

                            strcpy(temp->lexeme, lexeme);
                        break;
                    }

                    if(flag)
                    {
                        temp->id = ID;
                        temp->lexeme = malloc(strlen(lexeme) + 1);

                        strcpy(temp->lexeme, lexeme);
                    }

                    current = '^';

                    return temp;
                }

                else
                {
                    lexeme[--i] = '\0';

                    if(strlen(lexeme) > 20)
                    {
                        temp->lineNum = line;
                        temp->id = ERROR_ID_LENGTH;
                        temp->lexeme = NULL;

                        current = '^';

                        return temp;
                    }

                    temp->lineNum = line;
                    temp->lexeme = NULL;

                    int sum = 0;
                    int j;

                    for(j = 0; lexeme[j] != '\0'; j++)
                        sum += lexeme[j];

                    int flag = 0;

                    switch(sum)
                    {
                        case 311:
                            if(strcmp(lexeme, "end") == 0)
                                temp->id = END;

                            else
                                flag = 1;
                        break;

                        case 331:
                            if(strcmp(lexeme, "int") == 0)
                                temp->id = INT;

                            else
                                flag = 1;
                        break;

                        case 420:
                            if(strcmp(lexeme, "real") == 0)
                                temp->id = REAL;

                            else
                                flag = 1;
                        break;

                        case 663:
                            if(strcmp(lexeme, "string") == 0)
                                temp->id = STRING;

                            else
                                flag = 1;
                        break;

                        case 661:
                            if(strcmp(lexeme, "matrix") == 0)
                                temp->id = MATRIX;

                            else
                                flag = 1;
                        break;

                        case 207:
                            if(strcmp(lexeme, "if") == 0)
                                temp->id = IF;

                            else
                                flag = 1;
                        break;

                        case 425:
                            if(strcmp(lexeme, "else") == 0)
                                temp->id = ELSE;

                            else
                                flag = 1;
                        break;

                        case 518:
                            if(strcmp(lexeme, "endif") == 0)
                                temp->id = ENDIF;

                            else
                                flag = 1;
                        break;

                        case 412:
                            if(strcmp(lexeme, "read") == 0)
                                temp->id = READ;

                            else
                                flag = 1;
                        break;

                        case 557:
                            if(strcmp(lexeme, "print") == 0)
                                temp->id = PRINT;

                            else
                                flag = 1;
                        break;

                        case 870:
                            if(strcmp(lexeme, "function") == 0)
                                temp->id = FUNCTION;

                            else
                                flag = 1;
                        break;

                        default:
                            temp->id = ID;
                            temp->lexeme = malloc(strlen(lexeme) + 1);

                            strcpy(temp->lexeme, lexeme);
                        break;
                    }

                    if(flag)
                    {
                        temp->id = ID;
                        temp->lexeme = malloc(strlen(lexeme) + 1);

                        strcpy(temp->lexeme, lexeme);
                    }

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

                    temp->id = NUM;
                    temp->lineNum = line;
                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    return temp;
                }

            break;

            case 13:

                switch(current)
                {
                    case '0'...'9':
                        state = 14;
                        current = getNextChar(fp);
                    break;

                    case 'a':
                        state = 16;
                        current = getNextChar(fp);
                    break;

                    case 'o':
                        state = 20;
                        current = getNextChar(fp);
                    break;

                    case 'n':
                        state = 23;
                        current = getNextChar(fp);
                    break;

                    default:
                        temp->lineNum = line;
                        temp->id = ERROR_PATTERN;

                        temp->lexeme = malloc(strlen(lexeme) + 1);

                        strcpy(temp->lexeme, lexeme);

                        current = '^';

                        return temp;
                    break;
                }

            break;

            case 14:

                if(isdigit(current))
                {
                    state = 15;

                    temp->id = RNUM;
                    temp->lineNum = line;
                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

                else
                {
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

            break;

            case 16:

                if(current == 'n')
                {
                    state = 17;
                    current = getNextChar(fp);
                }

                else
                {
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

            break;

            case 17:

                if(current == 'd')
                {
                    state = 18;
                    current = getNextChar(fp);
                }

                else
                {
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

            break;

            case 18:

                if(current == '.')
                {
                    state = 19;

                    temp->id = AND;
                    temp->lineNum = line;
                    temp->lexeme = NULL;

                    current = '^';

                    return temp;
                }

                else
                {
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

            break;

            case 20:

                if(current == 'r')
                {
                    state = 21;
                    current = getNextChar(fp);
                }

                else
                {
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

            break;

            case 21:

                if(current == '.')
                {
                    state = 22;

                    temp->id = OR;
                    temp->lineNum = line;
                    temp->lexeme = NULL;

                    current = '^';

                    return temp;
                }

                else
                {
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

            break;

            case 23:

                if(current == 'o')
                {
                    state = 24;
                    current = getNextChar(fp);
                }

                else
                {
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

            break;

            case 24:

                if(current == 't')
                {
                    state = 25;
                    current = getNextChar(fp);
                }

                else
                {
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

            break;

            case 25:

                if(current == '.')
                {
                    state = 26;

                    temp->id = NOT;
                    temp->lineNum = line;
                    temp->lexeme = NULL;

                    current = '^';

                    return temp;
                }

                else
                {
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

            break;

            case 27:

                if(islower(current) || current == '\t' || current == ' ')
                {
                    state = 28;
                    current = getNextChar(fp);
                }

                else
                {
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

            break;

            case 28:

                if(islower(current) || current == '\t' || current == ' ')
                    current = getNextChar(fp);

                else if(current == '"')
                {
                    state = 29;

                    if(strlen(lexeme) > 20)
                    {
                        temp->lineNum = line;
                        temp->id = ERROR_STR_LENGTH;
                        temp->lexeme = NULL;

                        current = '^';

                        return temp;
                    }

                    temp->id = STR;
                    temp->lineNum = line;
                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

                else
                {
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                }

            break;

            case 45:

                switch(current)
                {
                    case 'a':
                        state = 16;
                        current = getNextChar(fp);
                    break;

                    case 'o':
                        state = 20;
                        current = getNextChar(fp);
                    break;

                    case 'n':
                        state = 23;
                        current = getNextChar(fp);
                    break;

                    default:
                    temp->lineNum = line;
                    temp->id = ERROR_PATTERN;

                    temp->lexeme = malloc(strlen(lexeme) + 1);

                    strcpy(temp->lexeme, lexeme);

                    current = '^';

                    return temp;
                    break;
                }

            break;
        }
    }
}

int main()
{
    FILE * fp = fopen("testcases/test.txt", "r");

    int i;

    tokenInfo * token;

    for(i = 1; i <= 75; i++)
    {
        token = getNextToken(fp);

        if(!token)
        {
            printf("Reached end of file \n");
            break;
        }

        else if(token->id == ERROR_SYMBOL)
            printf("Line number: %d, Lexical error: Unknown symbol %c \n", token->lineNum, token->lexeme[0]);

        else if(token->id == ERROR_PATTERN)
            printf("Line number: %d, Lexical error: Unknown pattern %s \n", token->lineNum, token->lexeme);

        else if(token->id == ERROR_ID_LENGTH)
            printf("Line number: %d, Lexical error: Identifier is longer than the prescribed length \n", token->lineNum);

        else if(token->id == ERROR_STR_LENGTH)
            printf("Line number: %d, Lexical error: String is longer than the prescribed length \n", token->lineNum);

        else
        {
            printf("%d: %s ", token->lineNum, tokens[token->id]);

            if(token->lexeme)
                printf("Lexeme: %s \n", token->lexeme);
        }

        printf("\n");
    }

    return 0;
}
