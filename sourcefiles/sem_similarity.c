#include "stdlib.h"
#include "stdio.h"
#include "assert.h"
#include "string.h"
#include "../headers/game.h"

int main(int argc, char * arv[]) {
    printf("Calcul de la similarite semantique \n");

    if (argc == 1){
        printf("FC RATS NOMS A DEFINIR \n");
        exit(0);
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

    int offsetword1 = searchWordInStaticTree(&st, word1);
    if (offsetword1 == -1){
        printf("Mot non trouvé dans le dictionnaire");
        exit(EXIT_FAILURE);
    }

    int offsetword2 = searchWordInStaticTree(&st, word2);
    if (offsetword2 == -1){
        printf("Mot non trouvé dans le dictionnaire");
        exit(EXIT_FAILURE);
    }

    printf("Score de similarite semantique : %0.2f\n",calculScalaire(offsetword1, offsetword2));

    return 1;
}
