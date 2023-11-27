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



#pragma endregion Constantes


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