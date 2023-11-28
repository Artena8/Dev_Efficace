#include "stdlib.h"
#include "stdio.h"
#include "assert.h"
#include "string.h"
#include "../headers/game.h"

int main(int argc, char * arv[]) {
    printf("Calcul de la similarite orthographique \n");

    if (argc != 3) {
        printf("Usage: <word1> <word2> \n");
        return ERROR_INVALID_INPUT; // Code d'erreur personnalisé
    }

    printf("Mots fournis :\n");
    for (int i = 1; i < argc; ++i) {
        printf("Mot %d: %s\n", i, arv[i]);
    }

    char S[100];
    char T[100];
    strcpy(S, arv[1]);
    strcpy(T, arv[2]);
    //printf("distance %s-%s : %d \n", S, T, levenshtein(S, T));
    printf("Score de similarite orthographique : %d\n",levenshtein(S, T));
    return levenshtein(S, T);
}
