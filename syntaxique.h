#include "lexical.h"

int prog(FILE* source);
int inst(FILE* source);
int suiteInst(FILE* source);
int expr(FILE* source, int par);
int atome(FILE* source);
int resteExpr(FILE* source, int par);
