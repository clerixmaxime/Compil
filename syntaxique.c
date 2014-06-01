#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "syntaxique.h"

int valide; // s'il vaut 0 la syntaxe est valide.
int result;
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
    printf("inst token value : %d \n",tok.code);
    if (tok.code == FIN) {
        valide = 2;
    }
    if (tok.code == ID) {
        tok = nextToken(source);
        if (tok.code == AFFECT) {
            if (expr(source,0) == 0) {
                valide = 0;
            }
        }
    }
    if (tok.code == PRINT) {
        if (expr(source,0) == 0) {
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
    /* Traitement production suiteInst -> inst suiteInst */
    result = inst(source);
    if (result == 0) {
        if (suiteInst(source) == 0) {
            valide = 0;
        }
    }
    if (result == 2){
        valide = 0;
    }
    /*Traitement production suiteInst -> ɛ
    if (valide != 0) {
        tok = nextToken(source);
        printf("inst suiteInst value : %d \n",tok.code);
        if (tok.code == FIN) {
            valide = 0;
        }
    }*/
    printf("suiteInst return value : %d \n",valide);
    return(valide);
}

/* règle de production : expr -> atome resteExpr */
int expr(FILE *source,int par){
    printf("appel expr \n");
    valide = 1;
    /* Traitement production expr -> atome resteExpr */
    if (atome(source) == 0) {
        if (par == 1) {
            valide = resteExpr(source,1);
        }
        else{
            valide = resteExpr(source,0);
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
    printf("atome token value : %d \n",tok.code);
    /* Traitement production atome -> ID */
    if(tok.code == ID){
        valide = 0;
    }
    /* Traitement production atome -> NB */
    if (tok.code == NB) {
        valide = 0;
    }
    /* 
       Traitement de la production atome -> PARGAUCHE expr PARDROITE
       Dans ce cas, on fait appel à la fonction expr avec le second paramètre avec valeur 1
       Cela signifie qu'on attend comme caractère de fin PARDROITE
    */
    if (tok.code == PARGAUCHE) {
        result = expr(source,1);
        if (result == 2) {
            valide = 0;
        }
    }
    printf("atome return value : %d \n",valide);
    return(valide);
}

/* règle de production : resteExpr -> PLUS atome resteExpr | MOINS atome resteExpr | ɛ 
    Valeurs de retour : 
    - 0 : Token PTVIRG ou FIN
    - 1 : Token invalide
    - 2 : Token PARDROITE
 */
int resteExpr(FILE *source, int par){
    printf("appel resteExpr \n");
    valide = 1;
    tok = nextToken(source);
    printf("resteExpr token value : %d \n",tok.code);
    /* Traitement production resteExpr -> PLUS atome resteExpr */
    if (tok.code == PLUS) {
        if (atome(source) == 0) {
            if (resteExpr(source,par) == 0) {
                valide = 0;
            }
        }
    }
    /* Traitement production resteExpr -> MOINS atome resteExpr */
    if (tok.code == MOINS) {
        if (atome(source) == 0) {
            if (resteExpr(source,par) == 0) {
                valide = 0;
            }
        }
    }
    /* Traitement production resteExpr -> ɛ */
    if (valide != 0){
        /* On teste la valeur de par, si elle est égale à 1 cela veut dire que l'on attend le Token PARDROITE.
        Sinon cela signifie que l'on attend le Token PTVIRG*/
        if (par == 1) {
            if (tok.code == PARDROITE) {
                valide = 2;
            }
        }
        else{
            if (tok.code == PTVIRG) {
                valide = 0;
            }
        }
    }
    printf("resteExpr return value : %d \n",valide);
    return(valide);
}
