#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntaxique.h"

int main(){
    FILE* fichier;
    int result;
    fichier = fopen("./test.txt","r");

    result = prog(fichier);
    printf("Résultat exécution : %d",result);
    
    fclose(fichier);
}
