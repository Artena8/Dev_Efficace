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

    else if ((argc==2 && strcmp("--help", argv[1])==0)) {
        printf("Usage:\n");
        printf(" exec1 name1 name2\n");
        printf(" where name1, name2 are two strings in the dictionnary\n");
        exit(255);
    }

    else if (argc != 3) {
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
    printf("Score de similarite orthographique : %d\n",levenshtein(S, T));
    return levenshtein(S, T);
}
