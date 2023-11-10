#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// Définition du type child Sibling Tree (CSTree)

typedef char Element;

typedef struct node{
    Element elem;
    struct node* firstChild;
    struct node* nextSibling;
} Node;
typedef Node* CSTree;


typedef struct {
    Element elem;
    unsigned int firstChild;
    unsigned int nSiblings;
} ArrayCell;
typedef struct {
    ArrayCell* nodeArray;
    unsigned int nNodes;
} StaticTree;

//constante pour firstChild si aucun enfant
#define NONE -1 

//Q1 Alloue un nouveau noeud pour un CSTree
CSTree newCSTree(Element elem, CSTree firstChild, CSTree nextSibling) {
    CSTree t = malloc(sizeof(Node));
    if (t == NULL) 
        exit(EXIT_FAILURE);
    t->elem = elem;
    t->firstChild = firstChild;
    t->nextSibling = nextSibling;
    return t;
}

//Q2 Construit l’arbre de l’exemple (A(B,C,D(F,G),E))
CSTree example(){
    CSTree g = newCSTree('G', NULL, NULL);
    CSTree f = newCSTree('F', NULL, g);
    CSTree e = newCSTree('E', NULL, NULL);
    CSTree d = newCSTree('D', f, e);
    CSTree c = newCSTree('C', NULL, d);
    CSTree b = newCSTree('B', NULL, c);
    CSTree a = newCSTree('A', b , NULL);
    return a;
};

//Q1 Imprime t en ordre préfixe 
void printPrefix(CSTree t){
    if (t == NULL) return;
    printf("%c ", t->elem);
    printPrefix(t->firstChild);
    printPrefix(t->nextSibling);
}

//Q2 Compte le nombre de noeuds dans l’arbre t.
int size(CSTree t){
    if (t == NULL) return 0;
    return 1 + size(t->firstChild) + size(t->nextSibling);
}

//Q3 Compte le nombre d’enfants du nœud t.
int nChildren(CSTree t) {
    if (t == NULL || t->firstChild == NULL) return 0;
    return nSiblingsFunction(t->firstChild);
}

// Fonction auxilliaire pour parcourir les gamins
int nSiblingsFunction(CSTree t){
    if (t == NULL) return 0;
    return 1 + nSiblingsFunction(t->nextSibling);
}

// Renvoie le premier frere de t contenant l’element e
CSTree siblingLookup(CSTree t, Element e){
    if (t == NULL) return NULL;
    if (t->elem == e){
        return t;
    }
    return siblingLookup(t->nextSibling, e);
}

//Insere un noeud contenant e dans la liste de freres de t, et renvoie le noeud correspondant
CSTree sortInsertSibling(CSTree* t, Element e){
    return t;
}

//Renvoie le premier frere de *t contenant e, le noeud est cree si absent.
CSTree sortContinue(CSTree* t, Element e){
    if (t == NULL) return NULL;
    siblingLookup(t, e);
}

/**
 * Q4 : Fonction récursive auxiliaire pour exportStaticTree
 * @param st : un arbre statique partiellement rempli
 * @param t : un nœud de l'arbre CSTree original
 * @param index_for_t : la position à laquelle t doit être enregistré
 * @param nSiblings : le nombre de frères du nœud courant
 * @param reserved_cells : le nombre de cellules "réservées" à cet état du parcours (passé par pointeur)
 * NB : au moment d'entrer dans la fonction, les cellules pour ce nœud et ses frères sont déjà réservées, mais pas pour leurs enfants
 */
void fill_array_cells(StaticTree* st, CSTree t, int index_for_t, int nSiblings, unsigned int* reserved_cells) {
    if (t == NULL) return;
    
    st->nodeArray[index_for_t].elem = t->elem;
    if (t->firstChild != NULL) {
        st->nodeArray[index_for_t].firstChild = *reserved_cells - 1;
        printCellArray(st, index_for_t);
        *reserved_cells = *reserved_cells - 1;
        fill_array_cells(st, t->firstChild, index_for_t + 1  , nSiblingsFunction(t->firstChild), reserved_cells);
    } else {
        st->nodeArray[index_for_t].firstChild = NONE;
    }

    if (nSiblings > 0) {
        printCellArray(st, index_for_t);
        fill_array_cells(st, t->nextSibling, index_for_t + 1, nSiblings - 1, reserved_cells);
    }
}

StaticTree exportStaticTree(CSTree t) {
    StaticTree st;
    st.nNodes = size(t);
    st.nodeArray = (ArrayCell *)malloc(st.nNodes * sizeof(ArrayCell));
    unsigned int reserved_cells = st.nNodes;
    fill_array_cells(&st, t, 0, nSiblingsFunction(t), &reserved_cells);
    if (reserved_cells != 0 || t != NULL)
        exit(EXIT_FAILURE);
    return st;
}

void printCellArray(StaticTree* st, int index) {
    if (index == NONE || index < 0 || index >= st->nNodes) {
        printf("Invalid index or NONE.\n");
        return;
    }
    printf("Index: %i,Element: %c, First Child Index: %d, Number of Siblings: %d\n",
            index,
           st->nodeArray[index].elem,
           st->nodeArray[index].firstChild,
           st->nodeArray[index].nSiblings);
}

void printPrefixStaticTree_aux(StaticTree* st, int index, int depth) {
    if (index == NONE)
        return;
    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("%c\n", st->nodeArray[index].elem);
    printPrefixStaticTree_aux(st, st->nodeArray[index].firstChild, depth + 1);
    if (st->nodeArray[index].nSiblings > 0)
        printPrefixStaticTree_aux(st, index + 1, depth);
}

void printPrefixStaticTree(StaticTree* st) {
    printPrefixStaticTree_aux(st, 0, 0);
}

//Recherche l’element e parmi les elements consecutifs de t a
int siblingLookupStatic(StaticTree t, Element e, int from, int len){
    return 0;
}

//Comme siblingLookupStatic, en supposant que les freres sont tries par ordre croissant d’element.
int siblingDichotomyLookupStatic(StaticTree t, Element e, int from, int len){
    return 0;
}


int main(){

    CSTree t=example();
    
    printf("Q1: ");
    printPrefix(t); // A B C D F G E
    printf("\n \n");
    printf("Q2: %d\n", size(t)); // 7
    printf("\n");
    printf("Q3: %d\n", nChildren(t)); // 4
    printf("Q3: %d\n", nSiblingsFunction(t->firstChild->nextSibling->nextSibling)); // 2
    printf("\n");
    printf("QBonus: \n");
    printPrefix(siblingLookup(t->firstChild,'D'));
    printf("\n");


    printf("Q4:");
    //StaticTree st = exportStaticTree(t);
    //printPrefixStaticTree(&st);
    printf("\n");
    return 0;


}