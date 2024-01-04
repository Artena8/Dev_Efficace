#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../headers/game.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_word2vec.bin> <fichier_lex.lex>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *word2vec_filename = argv[1];
    const char *lex_filename = argv[2];
    setlocale(LC_ALL, "");

    // Construire le dictionnaire Word2Vec à partir du fichier binaire
    CSTree word2vec_dictionary = buildWord2VecDictionaryFromFile(word2vec_filename);
    
    StaticTreeWithOffset st =  exportStaticTreeWithOffset(word2vec_dictionary);
    printf("Dico chargé %c %d\n", st.nodeArray[1].elem, st.nodeArray[1].nSiblings);

    //printNicePrefixStaticTree(&st);

    int findedword = searchWordInStaticTree(&st, "normoxie");
    printf("\nMot trouve : %i\n",st.nodeArray[findedword].nSiblings);

    // Exporter le dictionnaire dans un fichier .lex
    //exportTreeToFile(word2vec_dictionary, lex_filename);
    
    printf("Arbre lexicographique généré et sauvegardé dans %s.\n", lex_filename);


    return EXIT_SUCCESS;
}
