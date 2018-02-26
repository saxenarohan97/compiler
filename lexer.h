#include <stdio.h>
#include <stdlib.h>

typedef enum token
{
    ASSIGNOP, COMMENT, FUNID, ID, NUM, RNUM, STR, END, INT, REAL, STRING,
    MATRIX, MAIN, SQO, SQC, OP, CL, SEMICOLON, COMMA, IF, ELSE, ENDIF, READ,
    PRINT, FUNCTION, PLUS, MINUS, MUL, DIV, SIZE, AND, OR, NOT, LT, LE, EQ, GT,
    GE, NE, ERROR_SYMBOL, ERROR_PATTERN, ERROR_ID_LENGTH, ERROR_STR_LENGTH

} token;

typedef struct tokenInfo
{
    int lineNum;
    token id;
    char * lexeme;

} tokenInfo;

FILE * getStream(FILE * fp);

void removeComments(FILE * fp, char * cleanFile);

tokenInfo * getNextToken(FILE * fp);
