#include <stdio.h>
#include <string.h>

char * terms[] = {
    "rightHandSide_type1",
    "sizeExpression",
    "var_list",
    "declarationStmt",
    "logicalOp",
    "matrixElement",
    "stmtsAndFunctionDefs",
    "inputParameterList",
    "parameter_list",
    "assignmentStmt_type1",
    "elseStmt",
    "operator_lowPrecedence",
    "ioStmt",
    "matrix",
    "stmt",
    "arithmeticTerm",
    "relationalOp",
    "operator_highPrecedence",
    "recArithmeticTerm",
    "type",
    "rightHandSide_type2",
    "constrainedVars",
    "arithmeticExpression",
    "recStmtsAndFunctionDefs",
    "assignmentStmt_type2",
    "leftHandSide_listVar",
    "stmtOrFunctionDef",
    "listVar",
    "recArithmeticExpression",
    "var",
    "mainFunction",
    "remainingColElements",
    "factor",
    "more_ids",
    "otherStmts",
    "ifStmt",
    "booleanExpression",
    "recRow",
    "rows",
    "funCallStmt",
    "row",
    "functionDef",
    "remainingList",
    "recRows",
    "leftHandSide_singleVar",

    "RNUM",
    "GT",
    "REAL",
    "EQ",
    "SEMICOLON",
    "STR",
    "COMMA",
    "LT",
    "NUM",
    "AND",
    "END",
    "SQC",
    "DIV",
    "CL",
    "IF",
    "MATRIX",
    "PRINT",
    "ENDIF",
    "SIZE",
    "ID",
    "INT",
    "ASSIGNOP",
    "SQO",
    "PLUS",
    "FUNCTION",
    "ELSE",
    "MINUS",
    "NE",
    "LE",
    "OP",
    "FUNID",
    "MAIN",
    "STRING",
    "READ",
    "OR",
    "GE",
    "MUL",
    "EPSILON",
    "NOT"
};


int main()
{
    char buffer[128];
    int final[90][32];

    int j = 0, k = 0;

    for(j = 0; j < 90; j++)
    {
        for(k = 0; k < 32; k++)
            final[j][k] = 0;
    }

    FILE * fp = fopen("grammar", "r");
    FILE * output = fopen("encoded_grammar", "w");

    char c;

    j = k = 0;

    while(fscanf(fp, "%s%c", buffer, &c) == 2)
    {
        if(strcmp(buffer, "->") == 0)
            continue;

        int i = 0;

        for(i = 0; i < 84; i++)
        {
            if(strcmp(terms[i], buffer) == 0)
                break;
        }

        final[j][k++] = i + 1;

        if(c == '\n')
        {
            j++;
            k = 0;
        }
    }

    for(j = 0; j < 90; j++)
    {
        for(k = 0; final[j][k] != 0; k++)
            fprintf(output, "%d ", final[j][k]);

        fprintf(output, "\n");
    }

    return 0;
}
