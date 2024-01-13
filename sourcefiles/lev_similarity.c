#include "stdlib.h"
#include "stdio.h"
#include "assert.h"
#include "string.h"
#include "../headers/game.h"

int main(int argc, char * arv[]) {
    printf("Calcul de la similarite orthographique \n");

    if (argc == 1){
        printf("FC RATS NOMS A DEFINIR \n");
    }

    else if (argc != 3) {
        printf("Usage: <dico.lex> <word1> <word2> \n");
        return ERROR_INVALID_INPUT; // Code d'erreur personnalisé
    }

    char S[100];
    char T[100];
    strcpy(S, arv[1]);
    strcpy(T, arv[2]);

    printf("Score de similarite orthographique : %0.2f\n",levenshtein(S, T)); // FLOAT
    return 1;
}
