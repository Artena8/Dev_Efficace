#include "stdlib.h"
#include "stdio.h"
#include "assert.h"
#include "string.h"

//structure de tableau à deux dimensions, dédié à l'algorithme de Levenshtein
typedef struct {
    int lenS;
    int lenT;
    int * tab;
}
LevArray;

//minimum de deux entiers
int min(int a, int b) {
    return a < b ? a : b;
}

//initialiser un tableau pour des chaînes d'une taille donnée
LevArray init(int lenS, int lenT) {
    LevArray a;
    //on stocke les dimensions
    a.lenS = lenS;
    a.lenT = lenT;
    //allocation d'un tableau (1D) de lenS*lenT entiers
    a.tab = malloc(lenS * lenT * sizeof(int));
    //on vérifie que l'allocation s'est bien passée
    assert(a.tab != NULL); 
    return a;

}

//set: insérer une valeur dans le tableau
void set(LevArray a, int indexS, int indexT, int val) {
    //vérification des indices
    assert(indexS >= 0 && indexS < a.lenS && indexT >= 0 && indexT < a.lenT);
    assert(a.tab!=NULL); 
    a.tab[indexT * a.lenS + indexS] = val;
}

//Q1 get: renvoie la valeur correspondant à des indices donnés
//   i+1 pour les requêtes du type get(a, -1, i) ou get (a, i, -1)
int get(LevArray a, int indexS, int indexT) {
    if (indexS == -1) {
        return indexT + 1;
    }
    else if (indexT == -1) {
        return indexS + 1;
    }
    else {
        return a.tab[indexT * a.lenS + indexS];
    }
}

//Q2 levenshtein: calcule la distance de levenshtein de deux chaînes
int levenshtein(char * S, char * T) {
    LevArray a = init(strlen(S), strlen(T));
    
    for (int i=0;i<a.lenS;i++) {
        for (int j=0;j<a.lenT;j++) {
            int p;
            if(S[i]==T[j])  {
                p=get(a,i-1,j-1);
            }
            else {
                p=get(a,i-1,j-1)+1;
            }  
            set(a, i, j, min(min(p,get(a,i-1,j)+1),get(a,i,j-1)+1));
        }
    }

    return get(a,strlen(S)-1, strlen(T)-1);
}

int main(int argc, char * arv[]) {
    printf("Q1 - get: \n");
    LevArray a = init(3, 3);
    set(a, 1, 1, 42);
    set(a, 1, 2, 99); 
    printf("get(1,1) = %d\n", get(a, 1, 1));
    printf("get(1,2) = %d\n", get(a, 1, 2));
    printf("get(-1,2) = %d\n", get(a, -1, 2));
    printf("get(-1,-1) = %d\n", get(a, -1, -1));
    free(a.tab);


    printf("Q2 - levenshtein: \n");
    char S[] = "BANANE";
    char T[] = "ANANAS";
    printf("distance %s-%s : %d \n", S, T, levenshtein(S, T));
    return 0;
}
/* sortie attendue: 

Q1 - get: 
get(1,1) = 42
get(1,2) = 99
get(-1,2) = 3
get(-1,-1) = 0
Q2 - levenshtein: 
distance BANANE-ANANAS : 3 


*/