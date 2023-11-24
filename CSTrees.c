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
    unsigned int offset;
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
    return newCSTree('A', newCSTree('B', NULL, newCSTree('C', NULL, newCSTree('D', newCSTree('F', NULL, newCSTree('G', NULL, NULL)), newCSTree('E', NULL, NULL)))), NULL);
};

//Q3 Imprime t en ordre préfixe 
void printPrefix(CSTree t){
    if (t == NULL) return;
    printf("%c ", t->elem);
    printPrefix(t->firstChild);
    printPrefix(t->nextSibling);
}

//Q4 Compte le nombre de noeuds dans l’arbre t.
int size(CSTree t){
    if (t == NULL) return 0;
    return 1 + size(t->firstChild) + size(t->nextSibling);
}

//Q5 Compte le nombre d’enfants du nœud t.
int nSiblings(CSTree child) {
    if (child == NULL) return 0;
    return nSiblings(child->nextSibling) + 1;
}

int nChildren(CSTree t) {
    if (t == NULL || t->firstChild == NULL) return 0;
    return nSiblings(t->firstChild);
}

//Q6 Fonction récursive auxiliaire pour exportStaticTree
// paramètres:
//  *st : un static tree partiellement rempli
//  t  : un noeud du CSTree original
//  index_for_t : la position à laquelle t doit être enregistré
//  nSiblings : le nombre de frères du noeud courant
//  *reserved_cells : le nombre de cellules "réservées" à cet état du parcours (passée par pointeur)
//  NB : au moment d'entrer dans la fonction, les cellules pour ce noeud et ses frères sont déjà réservervées, mais pas pour leurs enfants
void fill_array_cells(StaticTree* st, CSTree t, int index_for_t, int nSiblings, int* reserved_cells){
    if (t == NULL) return;

    int firstChildIndex;
    if (t->firstChild != NULL) firstChildIndex = *reserved_cells;
    else firstChildIndex = NONE;

    st->nodeArray[index_for_t].elem = t->elem;
    st->nodeArray[index_for_t].firstChild = firstChildIndex;
    st->nodeArray[index_for_t].nSiblings = nSiblings;
    
    *reserved_cells += nChildren(t);

    if (t->firstChild != NULL) {
        fill_array_cells(st, t->firstChild, firstChildIndex, nChildren(t)-1, reserved_cells);
    }
    if (t->nextSibling != NULL) {
        fill_array_cells(st, t->nextSibling, index_for_t + 1, nSiblings-1, reserved_cells);
    }
    printf("inserting node %c at position %d (%d siblings, %d reserved cells)\n", t->elem, index_for_t, nSiblings, *reserved_cells );
}
//Crée un arbre statique avec le même contenu que t.
StaticTree exportStaticTree(CSTree t){
    StaticTree st={NULL, 0};
    int reserved_cells=0;
    st.nNodes = size(t);
    st.nodeArray = malloc(st.nNodes * sizeof(ArrayCell));

    if (st.nodeArray == NULL) {
        printf("Erreur lors de l'allocation mémoire pour l'arbre statique.\n");
        exit(EXIT_FAILURE);
    }

    reserved_cells = nSiblings(t);
    fill_array_cells(&st, t, 0, reserved_cells-1,  &reserved_cells);
    if (reserved_cells != st.nNodes && t!=NULL){
        printf("erreur lors de la création de l'arbre statique, taille finale incorrecte\n");
        exit(EXIT_FAILURE);
    }
    return st;   
}

//Fonctions d'impression d'un arbre statique:
// * version "jolie" avec un noeud par ligne, chaque noeud indenté sous son parent 
void printNicePrefixStaticTree_aux(StaticTree* st, int index, int depth){
    if (index==NONE)
        return;
    for (int i=0; i<depth; i++)
        printf("    ");
    printf("%c\n", st->nodeArray[index].elem);
    printNicePrefixStaticTree_aux(st, st->nodeArray[index].firstChild, depth+1);
    if (st->nodeArray[index].nSiblings>0)
        printNicePrefixStaticTree_aux(st, index+1, depth);    
}

void printNicePrefixStaticTree(StaticTree* st){
    if (st->nNodes>0) 
        printNicePrefixStaticTree_aux(st, 0, 0);

}
// *version "brute": imprime le contenu du tableau, dans l'ordre des cellules
void printDetailsStaticTree(StaticTree* st){
    int i;
    printf("elem     \t");
    for (i=0; i< st->nNodes; i++) 
        printf("%c\t", st->nodeArray[i].elem);
    printf("\nfirstChild\t");
    for (i=0; i< st->nNodes; i++) 
        printf("%d\t", st->nodeArray[i].firstChild);
    printf("\nnSiblings\t");
    for (i=0; i< st->nNodes; i++) 
        printf("%d\t", st->nodeArray[i].nSiblings);
    printf("\n");
}

//Q7 Renvoie le premier frère de t contenant l’élément e (ou t lui-même), NULL si aucun n’existe.
CSTree siblingLookup(CSTree t, Element e){
    if (t == NULL || t->elem > e) return NULL;
    if (t->elem == e) return t;
    return siblingLookup(t->nextSibling, e);
}

//Q8 on suppose que les frères de *t sont triés par ordre croissant.
//   Renvoie le premier frère de *t contenant e, un nouveau noeud est créé si absent
CSTree sortContinue(CSTree* t, Element e){
    if (*t != NULL && (*t)->elem < e) return sortContinue(&((*t)->nextSibling), e);
    else if (*t != NULL && (*t)->elem == e) return *t;
    else {
        (*t) = newCSTree(e,NULL, *t);
        return *t;
    }
}

//Q9 Recherche l’élément e parmi les éléments consécutifs de t aux positions from,..., from+len-1, 
//    renvoie la position de cet élément s’il existe, NONE sinon.
//    Si len=NONE, parcourir la cellule from et tous ses frères suivants 
//    cette fonction peut être itérative
int siblingLookupStatic(StaticTree* st, Element e, int from, int len){
    if (len==NONE) {
        len = st->nodeArray[from].nSiblings+1;
    }

    for (int i = from; i < from + len; i++) {
        if (st->nodeArray[i].elem == e) return i;
    }

    return NONE;
}

//Q10 Comme siblingLookupStatic, mais par dichotomie
//    cette fonction peut être itérative
int siblingDichotomyLookupStatic(StaticTree* st, Element e, int from, int len){
    if (len==NONE) {
        len = st->nodeArray[from].nSiblings+1;
    }

    while (len > 0) {
        int mid = from + len / 2;
        if (e == st->nodeArray[mid].elem) {
            return mid;
        }
        if (e > st->nodeArray[mid].elem) {
            len = (from + len) - (mid + 1);
            from = mid + 1;
        } else {
            len = mid - from;
        }
    }

    return NONE;
}

/* sortie attendue

Q1 newCSTree GO
Q2 example AB
Q3 printPrefix: A B C D F G E 
Q4 size 7
Q5 nChildren(B) 0
Q6 exportStaticTree
elem     	A	B	C	D	E	F	G	
firstChild	1	-1	-1	5	-1	-1	-1	
nSiblings	0	3	2	1	0	1	0	
A
    B
    C
    D
        F
        G
    E
Q7 siblingLookup 1 0
Q8 sortContinue
 @ A 0 B C D F G E Y Z 
Q9 siblingLookupStatic 3 -1
Q10 siblingDichotomyLookupStatic 3 -1


*/