#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexical.h"

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

Token nextToken(FILE *source){
    
    Token token;
    char current_char;
    char* current_token = NULL;
    
    token.code = ERREURLEX;
    
    /* Je lis le premier caractère */
    current_char = fgetc(source);
    
    /* Si je suis à la fin du fichier je retourne le token de FIN */
    if (feof(source)) {
        token.code = FIN;
    }
    else{
        /* j'ignore les espaces tabulations et retour ligne */
        if (current_char == ' ' || current_char =='\t' || current_char == '\n'){
            current_char = fgetc(source);
        }
        else{
            /* Je regarde si c'est un nb */
            if(isdigit((int)current_char) != 0){
                while (isdigit((int)current_char != 0)) {
                    current_char = fgetc(source);
                }
                ungetc(current_char,source);
                token.code = NB;
            }
            /* Je regarde si c'est un token */
            if(isalpha(current_char) != 0){
                current_token = concat(current_token,&current_char);
               while (isalnum((int)current_char != 0)) {
                   current_char = fgetc(source);
                   current_token = concat(current_token,&current_char);
               }
              /* On enlève le dernier caractère lu dans le while */
              ungetc(current_char,source);
                      
              if(strcmp(current_token,"print") == 0){
                  free(current_token);
                  token.code = PRINT;
              }
              else{
                  token.code = ID;
              }
            }
            /*On regarde si c'est un plus... */
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
        }
    }
    return(token);
}
