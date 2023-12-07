#include "stdlib.h"
#include "stdio.h"
#include "assert.h"
#include "string.h"
#include "../headers/game.h"

//minimum de deux entiers
int min(int a, int b) {
    return a < b ? a : b;
}

//initialiser un tableau pour des chaînes d'une taille donnée
LevArray init(int lenS, int lenT) {
    LevArray a;
    a.lenS = lenS;
    a.lenT = lenT;
    a.tab = malloc(lenS * lenT * sizeof(int));
    assert(a.tab != NULL); 
    return a;
}

//set: insérer une valeur dans le tableau
void set(LevArray a, int indexS, int indexT, int val) {
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
double levenshtein(char * S, char * T) {
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

    int max = strlen(S) > strlen(T) ? strlen(S) : strlen(T);
    int distance = (get(a,strlen(S)-1, strlen(T)-1));
    //printf("distance = %d - %d - %f /n", max, distance, ((double)distance/max));
    return (1-((double)distance/max))*100;
}
