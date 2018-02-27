#include <stdio.h>
#include <string.h>

char * terms[] = {
    "arithmeticExpression",
    "arithmeticTerm",
    "assignmentStmt_type1",
    "assignmentStmt_type2",
    "booleanExpression",
    "constrainedVars",
    "declarationStmt",
    "elseStmt",
    "factor",
    "funCallStmt",
    "functionDef",
    "ifStmt",
    "inputParameterList",
    "ioStmt",
    "leftHandSide_listVar",
    "leftHandSide_singleVar",
    "listVar",
    "logicalOp",
    "mainFunction",
    "matrix",
    "matrixElement",
    "more_ids",
    "operator_highPrecedence",
    "operator_lowPrecedence",
    "otherStmts",
    "parameter_list",
    "recArithmeticExpression",
    "recArithmeticTerm",
    "recRows",
    "recStmtsAndFunctionDefs",
    "relationalOp",
    "remainingColElements",
    "remainingList",
    "rightHandSide_type1",
    "rightHandSide_type2",
    "row",
    "rows",
    "sizeExpression",
    "stmt",
    "stmtOrFunctionDef",
    "stmtsAndFunctionDefs",
    "type",
    "var",
    "var_list",

    "AND",
    "ASSIGNOP",
    "CL",
    "COMMA",
    "DIV",
    "ELSE",
    "END",
    "ENDIF",
    "EPSILON",
    "EQ",
    "FUNCTION",
    "FUNID",
    "GE",
    "GT",
    "ID",
    "IF",
    "INT",
    "LE",
    "LT",
    "MAIN",
    "MATRIX",
    "MINUS",
    "MUL",
    "NE",
    "NOT",
    "NUM",
    "OP",
    "OR",
    "PLUS",
    "PRINT",
    "READ",
    "REAL",
    "RNUM",
    "SEMICOLON",
    "SIZE",
    "SQC",
    "SQO",
    "STR",
    "STRING"
};


int main()
{
    char buffer[128];
    int final[43][64];

    int j = 0, k = 0;

    for(j = 0; j < 43; j++)
    {
        for(k = 0; k < 64; k++)
            final[j][k] = 0;
    }

    FILE * fp = fopen("follow.txt", "r");
    FILE * output = fopen("encoded_follow", "w");

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

    for(j = 0; j < 43; j++)
    {
        for(k = 0; final[j][k] != 0; k++)
            fprintf(output, "%d ", final[j][k]);

        fprintf(output, "\n");
    }

    fclose(fp);
    fclose(output);

    return 0;
}
