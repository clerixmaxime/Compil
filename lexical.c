#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexical.h"

Token nextToken(FILE *source){
    
    Token token;
    char current_char;
    char current_token[30];
    int cpt = 0;
    
    token.code = ERREURLEX;
    
    /* Je lis le premier caractère */
    current_char = fgetc(source);
    
    /* Si je suis à la fin du fichier je retourne le token de FIN */
    if (feof(source)) {
        token.code = FIN;
    }
    /* j'ignore les espaces tabulations et retour ligne */
    if (current_char == ' ' || current_char == '\n' || current_char == '\t'){
        current_char = fgetc(source);
    }
    
    /* --- Test du caractère courant --- */
    
    if(current_char == '+'){
        token.code = PLUS;
    }
    if(current_char == '-'){
        token.code = MOINS;
    }
    if(current_char == ';'){
        token.code = PTVIRG;
    }
    if(current_char == '('){
        token.code = PARGAUCHE;
    }
    if(current_char == ')'){
        token.code = PARDROITE;
    }
    if(current_char == ':'){
        current_char = fgetc(source);
        if(current_char == '='){
            token.code = AFFECT;
        }
    }
    /* Je regarde si c'est un nb */
    if(isdigit((int)current_char) != 0){
        while (isdigit(current_char) != 0){
            current_char = fgetc(source);
        }
        ungetc(current_char,source);
        token.code = NB;
    }
    /* Je regarde si c'est un token */
    if(isalpha(current_char) != 0){
        current_token[cpt] = current_char;
       while (isalnum(current_char) != 0) {
           current_char = fgetc(source);
           cpt++;
           current_token[cpt] = current_char;
       }
      /* On ajoute le caractère de fin de chaîne */
        current_token[cpt] = '\0';
        printf("Token courant : %s \n",current_token);
      /* On enlève le dernier caractère lu dans le while */
      ungetc(current_char,source);
              
      if(strcmp(current_token,"print") == 0){
          token.code = PRINT;
      }
      else{
          token.code = ID;
      }
    }
    return(token);
}
