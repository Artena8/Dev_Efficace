/*
    prototype et déclaration des constantes
*/

#pragma region Constantes
/*
    =======================================

            Prototype des fonctions
                Constantes

    =======================================
*/

// Constantes


// Codes Erreurs

#pragma endregion Constantes

#pragma region Levenshtein
/*
    =======================================

            Prototype des fonctions
                Levenshtein

    =======================================
*/

// Structure pour représenter un tableau associé à l'algorithme de Levenshtein
typedef struct {
    int lenS;   // Longueur de la chaîne S
    int lenT;   // Longueur de la chaîne T
    int* tab;   // Tableau d'entiers
} LevArray;

// Fonction pour calculer le minimum de deux entiers
int min(int a, int b);

// Fonction pour initialiser un tableau pour des chaînes de tailles données
LevArray init(int lenS, int lenT);

// Fonction pour insérer une valeur dans le tableau
void set(LevArray a, int indexS, int indexT, int val);

// Fonction pour récupérer une valeur du tableau
int get(LevArray a, int indexS, int indexT);

// Fonction pour calculer la distance de Levenshtein entre deux chaînes
int levenshtein(char * S, char * T);

#pragma endregion Levenshtein

#pragma region NewGame
/*
    =======================================

            Prototype des fonctions
                New Game

    =======================================
*/



#pragma endregion  NewGame