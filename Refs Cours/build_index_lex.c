#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./CSTrees.c"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_word2vec.bin> <fichier_lex.lex>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *word2vec_filename = argv[1];
    const char *lex_filename = argv[2];

    // Construire le dictionnaire Word2Vec à partir du fichier binaire
    CSTree word2vec_dictionary = buildWord2VecDictionaryFromFile(word2vec_filename);

    // Exporter le dictionnaire dans un fichier .lex
    exportTreeToFile(word2vec_dictionary, lex_filename);

    printf("Arbre lexicographique généré et sauvegardé dans %s.\n", lex_filename);


    return EXIT_SUCCESS;
}
