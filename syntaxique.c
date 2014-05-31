#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "syntaxique.h"

int valide; // s'il vaut 0 la syntaxe est valide.
Token tok;

/* règle de production : prog -> inst suiteInst FIN */
int prog(FILE *source){
    printf("appel prog \n");
    valide = 1;
    if (inst(source) == 0) {
        if (suiteInst(source) == 0) {
            valide = 0;
        }
    }
    printf("prog return value : %d \n",valide);
    return(valide);
}

/* règle de production : inst -> ID AFFECT expr PTVIRG | PRINT expr PTVIRG */
int inst(FILE *source){
    printf("appel inst \n");
    valide = 1;
    tok = nextToken(source);
    if (tok.code == ID) {
        tok = nextToken(source);
        if (tok.code == AFFECT) {
            if (expr(source) == 0) {
                valide = 0;
            }
        }
    }
    if (tok.code == PRINT) {
        if (expr(source) == 0) {
            valide = 0;
        }
    }
    printf("inst return value : %d \n",valide);
    return (valide);
}

/* règle de production : suiteInst -> inst suiteInst | ɛ */
int suiteInst(FILE *source){
    printf("appel suiteInst \n");
    valide = 1;
    if (inst(source) == 0) {
        if (suiteInst(source) == 0) {
            valide = 0;
        }
    }
    /* Traitement de la production ɛ */
    if (valide != 0) {
        tok = nextToken(source);
        if (tok.code == FIN) {
            valide = 0;
        }
    }
    printf("suiteInst return value : %d \n",valide);
    return(valide);
}

/* règle de production : expr -> atome resteExpr */
int expr(FILE *source){
    printf("appel expr \n");
    valide = 1;
    if (atome(source) == 0) {
        if (resteExpr(source) == 0) {
            valide = 0;
        }
    }
    printf("expr return value : %d \n",valide);
    return(valide);
}

/* règle de production : atome -> ID | NB | PARGAUCHE expr PARDROITE */
int atome(FILE *source){
    printf("appel atome \n");
    valide = 1;
    tok = nextToken(source);
    printf("valeur token atome: %d \n",tok.code);
    if(tok.code == ID){
        valide = 0;
    }
    if (tok.code == NB) {
        valide = 0;
    }
    if (tok.code == PARGAUCHE) {
        if (expr(source) == 0) {
            tok = nextToken(source);
            printf("valeur token atome: %d \n",tok.code);
            if (tok.code == PARDROITE) {
                valide = 0;
            }
        }
    }
    printf("atome return value : %d \n",valide);
    return(valide);
}

/* règle de production : resteExpr -> PLUS atome resteExpr | MOINS atome resteExpr | ɛ */
int resteExpr(FILE *source){
    printf("appel resteExpr \n");
    valide = 1;
    tok = nextToken(source);
    printf("valeur token restExpr: %d \n",tok.code);
    if (tok.code == PLUS) {
        if (atome(source) == 0) {
            if (resteExpr(source) == 0) {
                valide = 0;
            }
        }
    }
    if (valide != 0) {
        if (tok.code == MOINS) {
            if (atome(source) == 0) {
                if (resteExpr(source) == 0) {
                    valide = 0;
                }
            }
        }
    }
    /* Traitement de la production ɛ */
    if (valide != 0){
        tok = nextToken(source);
        printf("valeur token restExpr: %d \n",tok.code);
        if (tok.code == PTVIRG  || tok.code == FIN) {
            valide = 0;
        }
    }
    printf("resteExpr return value : %d \n",valide);
    return(valide);
}
