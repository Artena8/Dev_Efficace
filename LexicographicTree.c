#include "CSTrees.c"

int main(){
    Node Xleaf={'X', NULL, NULL};
    Node Xroot={'X', &Xleaf, &Xleaf};

    CSTree t1 = newCSTree('G', NULL, newCSTree('O', NULL, NULL));
    if (t1==NULL) {
        t1=&Xroot; //pour avoir un arbre non vide et éviter les seg faults tant que newCSTree n'est pas codé
    }
    printf("Q1 newCSTree %c%c\n", t1->elem, t1->nextSibling->elem);
    CSTree t= example();
    if (t==NULL) {
        t=t1;
    }
    printf("Q2 example %c%c\n", t->elem, t->firstChild->elem);
    printf("Q3 printPrefix: ");
    printPrefix(t);
    printf("\nQ4 size %d\n", size(t));
    printf("Q5 nChildren(B) %d\n", nChildren(t->firstChild));
    printf("Q6 exportStaticTree\n");
    StaticTree st = exportStaticTree(t);
    printDetailsStaticTree(&st);
    printNicePrefixStaticTree(&st);
    printf("Q7 siblingLookup %d %d\n", siblingLookup(t->firstChild, 'D')!=NULL, siblingLookup(t->firstChild, 'F')!=NULL);   
    printf("Q8 sortContinue\n ");
    sortContinue(&(t->firstChild), '0');    
    sortContinue(&t, '@');
    sortContinue(&t, 'Z');
    sortContinue(&t, 'Y');    
    printPrefix(t);
    printf("\nQ9 siblingLookupStatic %d %d\n", siblingLookupStatic(&st, 'D', 1, NONE), siblingLookupStatic(&st, 'F', 1, NONE));
    printf("Q10 siblingDichotomyLookupStatic %d %d\n", siblingDichotomyLookupStatic(&st, 'D', 1, NONE), siblingDichotomyLookupStatic(&st, 'F', 1, NONE));
    
    return 0;
}