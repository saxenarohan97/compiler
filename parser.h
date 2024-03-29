void createParseTable();

void parseInputSourceCode();

// Used for mapping:

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
