#include<stdio.h>

typedef enum {AFFECT, PRINT, PTVIRG, PLUS, MOINS, PARGAUCHE,
    PARDROITE, ID, NB, FIN, ERREURLEX} codeToken;

struct t_Token{
    codeToken code;
}
 ;

typedef struct t_Token Token;

Token nextToken(FILE *source);
/* precondition : le fichier source est supposé ouvert */
/* retourne le code du prochain token à partir de la position courante dans
   le fichier, FIN si on arrive en fin de fichier, ERREURLEX s'il n'y a pas
de token;*/
/* après l'appel, la position courante dans le fichier correspond au premier
caractère suivant le lexème associé au token reconnu */
