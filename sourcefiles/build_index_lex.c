#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../headers/game.h"

int main(int argc, char *argv[]) {
    if (argc == 1){
        printf("Ce programme a ete code par la team FC RATS:\n -BREDEAU Kellian\n-CHEVALIER Helena\n-COUTELLIER Loelia\n-DESSERTENNE Leo\nLancement d'une fonction de test avec les arguments :\n");
        //Fonction de test minimaliste
    }
    else if (argc==2 && strcmp("--help", argv[1])==0){
        printf("Usage: exec <fichier_word2vec.bin> <dico.lex>\n");
        printf("where fichier_word2vec.bin le fichier bin au modele word2vec, dico.lex le chemin du dictionnaire lexicogrpahique\n");
        exit(0);
    }
    else if (argc != 3) {
        printf("Mauvais usage de la fonction \n");
        return ERROR_INVALID_INPUT; // Code d'erreur personnalisé
    }

    const char *word2vec_filename = argv[1];
    const char *lex_filename = argv[2];
    setlocale(LC_ALL, "");

    // Construire le dictionnaire Word2Vec à partir du fichier binaire
    CSTree word2vec_dictionary = buildWord2VecDictionaryFromFile(word2vec_filename);
    
    StaticTreeWithOffset st =  exportStaticTreeWithOffset(word2vec_dictionary);
    //printf("Dico chargé %c %d\n", st.nodeArray[1].elem, st.nodeArray[1].nSiblings);

    //printNicePrefixStaticTree(&st);

    //int findedword = searchWordInStaticTree(&st, "normoxie");
    //printf("\nMot trouve : %i\n",st.nodeArray[findedword].nSiblings);

    // Exporter le dictionnaire dans un fichier .lex
    exportTreeToFile(word2vec_dictionary, lex_filename);
    
    printf("Arbre lexicographique dans %s.\n", lex_filename);


    return EXIT_SUCCESS;
}
