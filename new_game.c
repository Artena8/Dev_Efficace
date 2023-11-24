#include <stdio.h>

int main(int argc, char *argv[]) {
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
