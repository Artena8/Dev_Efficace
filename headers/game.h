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
#define NONE -1;

// Codes Erreurs
#define ERROR_FILE_NOT_FOUND 111
#define ERROR_INVALID_INPUT 222


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

#pragma region CSTree
/*
    =======================================

            Prototype des fonctions
                CSTREE

    =======================================
*/

// Définition du type child Sibling Tree (CSTree)
typedef char Element;

typedef struct node {
    Element elem;
    struct node* firstChild;
    struct node* nextSibling;
} Node;

typedef Node* CSTree;

typedef struct {
    Element elem;
    unsigned int firstChild;
    unsigned int nSiblings;
    unsigned int offset;
} ArrayCell;

typedef struct {
    ArrayCell* nodeArray;
    unsigned int nNodes;
} StaticTree;

// Fonction pour allouer un nouveau noeud pour un CSTree
CSTree newCSTree(Element elem, CSTree firstChild, CSTree nextSibling);

// Fonction pour construire l'arbre de l'exemple (A(B,C,D(F,G),E))
CSTree example();

// Fonction pour imprimer l'arbre en ordre préfixe
void printPrefix(CSTree t);

// Fonction pour compter le nombre de noeuds dans l'arbre t
int size(CSTree t);

// Fonctions pour compter le nombre d'enfants d'un nœud
int nSiblings(CSTree child);
int nChildren(CSTree t);

// Fonction pour exporter un CSTree vers un StaticTree
StaticTree exportStaticTree(CSTree t);

// Fonctions d'impression d'un arbre statique
void printNicePrefixStaticTree(StaticTree* st);
void printDetailsStaticTree(StaticTree* st);

// Fonction pour rechercher le premier frère de t contenant l'élément e
CSTree siblingLookup(CSTree t, Element e);

// Fonction pour rechercher le premier frère de t contenant e, créer un nouveau noeud s'il est absent
CSTree sortContinue(CSTree* t, Element e);

// Fonction pour rechercher l'élément e parmi les éléments consécutifs de t
int siblingLookupStatic(StaticTree* st, Element e, int from, int len);

// Fonction pour rechercher l'élément e par dichotomie parmi les éléments consécutifs de t
int siblingDichotomyLookupStatic(StaticTree* st, Element e, int from, int len);

#pragma endregion CSTree

#pragma region NewGame
/*
    =======================================

            Prototype des fonctions
                New Game

    =======================================
*/



#pragma endregion  NewGame