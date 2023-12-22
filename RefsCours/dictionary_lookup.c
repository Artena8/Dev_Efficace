#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/game.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_lex.lex> <mot>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dictionnary = argv[2];
    const char *mot_search = argv[1];

    printf("ETAPE 1.\n");
    // Chargez le StaticTree depuis le fichier
    StaticTreeWithOffset st = loadStaticTreeWithOffsetFromFile(dictionnary);
    printDetailsStaticTree(&st);
    
    printf("ETAPE 2.\n");
    // Recherche du mot dans le StaticTree
    int mot_existe = searchWordInStaticTree(&st, mot_search);

    // Fermez le fichier
    fclose(dictionnary);

    // Vérifiez le résultat de la recherche
    if (mot_existe) {
        printf("Le mot '%s' existe dans le dictionnaire.\n", mot_search);
    } else {
        printf("Le mot '%s' n'existe pas dans le dictionnaire.\n", mot_search);
    }



    return EXIT_SUCCESS;
}
