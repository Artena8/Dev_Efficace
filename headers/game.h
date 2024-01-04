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
#define NONE -1

// Codes Erreurs
#define ERROR_FILE_NOT_FOUND 111
#define ERROR_INVALID_INPUT 222
#define ERROR_WRITE_FILE 123


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
typedef wchar_t Element;

typedef struct node {
    Element elem;
    struct node* firstChild;
    struct node* nextSibling;
    int offset;
} Node;

typedef Node* CSTree;

typedef struct {
    Element elem;
    unsigned int firstChild;
    unsigned int nSiblings;
    unsigned int offset;
} ArrayCellWithOffset;

typedef struct {
    ArrayCellWithOffset* nodeArray;
    unsigned int nNodes;
} StaticTreeWithOffset;

// Fonction pour imprimer l'arbre en ordre préfixe
void printPrefix(CSTree t);

// Fonction pour compter le nombre de noeuds dans l'arbre t
int size(CSTree t);

// Fonctions pour compter le nombre d'enfants d'un nœud
int nSiblings(CSTree child);
int nChildren(CSTree t);

// Fonction pour rechercher le premier frère de t contenant l'élément e
CSTree siblingLookup(CSTree t, Element e);

// Fonction pour rechercher le premier frère de t contenant e, créer un nouveau noeud s'il est absent
CSTree sortContinue(CSTree* t, Element e, int offset);

// Fonction pour rechercher l'élément e parmi les éléments consécutifs de t
int siblingLookupStatic(StaticTreeWithOffset* st, Element e, int from, int len);

// Fonction pour rechercher l'élément e par dichotomie parmi les éléments consécutifs de t
int siblingDichotomyLookupStatic(StaticTreeWithOffset* st, Element e, int from, int len);

#pragma endregion CSTree

#pragma region Lexico
/*
    =======================================

            Prototype des fonctions
                Lexico 

    =======================================
*/

struct vocab_word {
  long long cn;
  int *point;
  char *word, *code, codelen;
};

CSTree insert(CSTree t, const char* mot, int offset);

void convertUtf8ToWideChar(const char* utf8Str, wchar_t* wideCharStr);

void fill_array_cells_with_offset(StaticTreeWithOffset* st, CSTree t, int index_for_t, int nSiblings, int* reserved_cells) ;

CSTree buildWord2VecDictionaryFromFile(const char *filename);

StaticTreeWithOffset exportStaticTreeWithOffset(CSTree t);

void exportTreeToFile(CSTree t, const char *filename);

void exportStaticTreeWithOffsetToFile(StaticTreeWithOffset* st, const char* filename);

void printNicePrefixStaticTree(StaticTreeWithOffset* st);

void printNicePrefixStaticTree_aux(StaticTreeWithOffset* st, int index, int depth);

void printDetailsStaticTree(StaticTreeWithOffset* st);

StaticTreeWithOffset loadStaticTreeWithOffsetFromFile(FILE* file);

int searchWordInStaticTree(StaticTreeWithOffset* st, const char* word);

#pragma endregion Lexico

#pragma region NewGame
/*
    =======================================

            Prototype des fonctions
                New Game

    =======================================
*/



#pragma endregion  NewGame
