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
    return 0;
}

//Q4 Fonction récursive auxiliaire pour exportStaticTree
// paramètres:
//  *st : un static tree partiellement rempli
//  t  : un noeud du CSTree original
//  index_for_t : la position à laquelle t doit être enregistré
//  nSiblings : le nombre de frères du noeud courant
//  *reserved_cells : le nombre de cellules "réservées" à cet état du parcours (passée par pointeur)
//  NB : au moment d'entrer dans la fonction, les cellules pour ce noeud et ses frères sont déjà réservervées, mais pas pour leurs enfants
void fill_array_cells(StaticTree* st, CSTree t, int index_for_t, int nSiblings, int* reserved_cells){
}
//Crée un arbre statique avec le même contenu que t.
StaticTree exportStaticTree(CSTree t){
    StaticTree st;
    //à compléter
    fill_array_cells(&st, t, 0, reserved_cells-1,  &reserved_cells);
    if (reserved_cells != st.nNodes || t!=NULL)
        exit(EXIT_FAILURE);
    return st;   
}



void printPrefixStaticTree_aux(StaticTree* st, int index, int depth){
    if (index==NONE)
        return;
    for (int i=0; i<depth; i++)
        printf("    ");
    printf("%c\n", st->nodeArray[index].elem);
    printPrefixStaticTree_aux(st, st->nodeArray[index].firstChild, depth+1);
    if (st->nodeArray[index].nSiblings>0)
        printPrefixStaticTree_aux(st, index+1, depth);    

}

void printPrefixStaticTree(StaticTree* st){
    printPrefixStaticTree_aux(st, 0, 0);

}

int main(){

    CSTree t=example();
    
    printf("Q1: ");
    printPrefix(t);
    printf("\n");
    printf("Q2: %d\n", size(t));
    printf("\n");
    printf("Q3: %d\n", nChildren(t));
    printf("\n");
    return 0;


}