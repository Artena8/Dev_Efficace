#include <stdio.h>
#include <stdlib.h>
#include "../headers/game.h"

int main(int argc, char *arv[]) {
    if (argc == 1){
        printf("Ce programme a ete code par la team FC RATS:\n -BREDEAU Kellian\n-CHEVALIER Helena\n-COUTELLIER Loelia\n-DESSERTENNE Leo\nLancement d'une fonction de test avec les arguments :\n");
        exit(0);
    }

    else if (argc != 3) {
        printf("Usage: <dico.lex> <word>\n");
        return ERROR_INVALID_INPUT; // Code d'erreur personnalisé
    }

    const char *dictionnary_filename = arv[1];
    char *word1 = arv[2];

    FILE* dictionnary = fopen(dictionnary_filename, "rb");
    if (!dictionnary) {
        perror("Erreur lors de l'ouverture du dictionnaire");
        printf("%s", dictionnary_filename);
        return EXIT_FAILURE;
    }

    StaticTreeWithOffset st = loadStaticTreeWithOffsetFromFile(dictionnary);

    int offset1 = searchWordInStaticTree(&st, arv[2]);
    if (offset1 == -1){
        printf("Mot non trouvé dans le dictionnaire");
        exit(EXIT_FAILURE);
    }

    addWordToFile("game.txt", arv[2],offset1);

    return 0; 
}
