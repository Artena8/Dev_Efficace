#include <stdio.h>

int main(int argc, char *argv[]) {
    /*
    Args =  dictionnary = dictionnaire.bin
            words [] = liste des mots de départs
    
    Todo = 
    x faire le dic.lex et l'output pour ensuite
        - build_lex_index dictionnaire.bin
    x renvoyer un fichier de partie qui a :
        - liste mots de départs ( words[])
        - l'offset de chaque mot dans le dictionnaire
        - la distance entre chaque paire de mot
        - DONC TABLEAU :
        | Mot Entrant | Mot Cible | Similarité |
    */
    if (argc < 2) {
        printf("Usage: %s <arg1> <arg2> ... <argN>\n", argv[0]);
        return 1; // Code d'erreur
    }

    // Affiche les arguments fournis
    printf("Arguments fournis :\n");
    for (int i = 1; i < argc; ++i) {
        printf("%d: %s\n", i, argv[i]);
    }

    return 0; // Tout s'est bien passé
}
