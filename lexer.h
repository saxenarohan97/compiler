#include <stdio.h>
#include <stdlib.h>

typedef enum token
{
    AND,
    ASSIGNOP,
    CL,
    COMMA,
    COMMENT,
    DIV,
    ELSE,
    END,
    ENDIF,
    EQ,
    FUNCTION,
    FUNID,
    GE,
    GT,
    ID,
    IF,
    INT,
    LE,
    LT,
    MAIN,
    MATRIX,
    MINUS,
    MUL,
    NE,
    NOT,
    NUM,
    OP,
    OR,
    PLUS,
    PRINT,
    READ,
    REAL,
    RNUM,
    SEMICOLON,
    SIZE,
    SQC,
    SQO,
    STR,
    STRING,
    ERROR_SYMBOL, ERROR_PATTERN, ERROR_ID_LENGTH, ERROR_STR_LENGTH

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
