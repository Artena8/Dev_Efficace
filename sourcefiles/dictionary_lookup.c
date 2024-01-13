#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/game.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_lex.lex> <mot>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dictionnary_filename = argv[1];
    const char *word_to_lookup = argv[2];

    // Ouverture du fichier .lex en mode lecture binaire
    FILE* dictionnary = fopen(dictionnary_filename, "rb");
    if (!dictionnary) {
        perror("Erreur lors de l'ouverture du dictionnaire");
        printf("%s", dictionnary_filename);
        return EXIT_FAILURE;
    }

    // Chargement de l'arbre statique depuis le fichier .lex
    StaticTreeWithOffset st = loadStaticTreeWithOffsetFromFile(dictionnary);
    //printf("Dico chargé\n");

    //printDetailsStaticTree(&st);
    int findedword = searchWordInStaticTree(&st, word_to_lookup);
    printf("\nMot %s trouve, son offset est de %i\n",word_to_lookup,findedword);
    // Fermeture du fichier
    fclose(dictionnary);

    // Le reste de votre code ici...

    return EXIT_SUCCESS;
}