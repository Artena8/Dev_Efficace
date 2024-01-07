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

    else if (argc != 4) {
        printf("Usage: <dico.lex> <word1> <word2> \n");
        return ERROR_INVALID_INPUT; // Code d'erreur personnalisé
    }

    const char *dictionnary_filename = arv[1];
    char *word1 = arv[2];
    char *word2 = arv[3];

    FILE* dictionnary = fopen(dictionnary_filename, "rb");
    if (!dictionnary) {
        perror("Erreur lors de l'ouverture du dictionnaire");
        printf("%s", dictionnary_filename);
        return EXIT_FAILURE;
    }
    StaticTreeWithOffset st = loadStaticTreeWithOffsetFromFile(dictionnary);

    printf("Mots fournis :\n");
    for (int i = 2; i < 4; ++i) {
        printf("Mot %d: %s\n", i-1, arv[i]);
        int findedword = searchWordInStaticTree(&st, arv[i]);
        if (findedword == -1){
            printf("Mot non trouvé dans le dictionnaire");
        }
    }

    char S[100];
    char T[100];
    strcpy(S, arv[2]);
    strcpy(T, arv[3]);

    printf("Score de similarite orthographique : %f\n",levenshtein(S, T)); // FLOAT
    return 1;
}
