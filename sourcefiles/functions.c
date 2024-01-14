#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include <wchar.h>
#include <assert.h>
#include "../headers/game.h"


/*
    =======================================

            Prototype des fonctions
            Construction d'un CSTREE

    =======================================
*/

// Q1 Alloue un nouveau noeud pour un CSTree
CSTree newCSTree(Element elem, CSTree firstChild, CSTree nextSibling, int offset){
    CSTree t = malloc(sizeof(Node));
    if (t == NULL)
        exit(EXIT_FAILURE);
    t->elem = elem;
    t->firstChild = firstChild;
    t->nextSibling = nextSibling;
    t->offset = offset;
    return t;
}

// Q4 Compte le nombre de noeuds dans l’arbre t.
int size(CSTree t){
    if (t == NULL)
        return 0;
    return 1 + size(t->firstChild) + size(t->nextSibling);
}

// Q5 Compte le nombre d’enfants du nœud t.
int nSiblings(CSTree child){
    if (child == NULL)
        return 0;
    return nSiblings(child->nextSibling) + 1;
}

int nChildren(CSTree t){
    if (t == NULL || t->firstChild == NULL)
        return 0;
    return nSiblings(t->firstChild);
}

// Q8 on suppose que les frères de *t sont triés par ordre croissant.
//    Renvoie le premier frère de *t contenant e, un nouveau noeud est créé si absent
CSTree sortContinue(CSTree *t, Element e, int offset){
    if (*t != NULL && (*t)->elem < e)
        return sortContinue(&((*t)->nextSibling), e, offset);
    else if (*t != NULL && (*t)->elem == e)
        return *t;
    else
    {
        (*t) = newCSTree(e, NULL, *t, offset);
        return *t;
    }
}

// Q9 Recherche l’élément e parmi les éléments consécutifs de t aux positions from,..., from+len-1,
//     renvoie la position de cet élément s’il existe, NONE sinon.
//     Si len=NONE, parcourir la cellule from et tous ses frères suivants
//     cette fonction peut être itérative
int siblingLookupStatic(StaticTreeWithOffset *st, Element e, int from, int len){
    if (len == NONE){
        len = st->nodeArray[from].nSiblings + 1;
        //printf("Lettre %c nsblings : %d\n", st->nodeArray[from].elem, len);
    }
    for (int i = from; i < from + len; i++){
        //printf("searched : %c = %c ", st->nodeArray[i].elem, e);
        //printf(" equal : %i\n", e == st->nodeArray[i].elem);
        if (st->nodeArray[i].elem == e)
        {
            //printf("Lettre %c enfant : %d\n", st->nodeArray[i].elem, st->nodeArray[i].firstChild);
            return st->nodeArray[i].firstChild;
        }
    }
    return NONE;
}


/*
    =======================================

            Prototype des fonctions
                Lexico

    =======================================
*/

int utf8_char_length(unsigned char first_byte)
{
    if ((first_byte & 0x80) == 0)
    {
        return 1;
    }
    else if ((first_byte & 0xE0) == 0xC0)
    {
        return 2;
    }
    else if ((first_byte & 0xF0) == 0xE0)
    {
        return 3;
    }
    else if ((first_byte & 0xF8) == 0xF0)
    {
        return 4;
    }
    else
    {
        // Invalid UTF-8
        return -1;
    }
}

wchar_t convertUtf8(wchar_t *word, int char_length)
{
    wchar_t combinedWord;
    if (char_length == 1)
    {
        combinedWord = (wchar_t)(*word);
    }
    else if (char_length == 2)
    {
        combinedWord = ((wchar_t)(*word & 0x1F) << 6) | (wchar_t)(*(word + 1) & 0x3F);
    }
    else
    {
        // Gérer les autres longueurs de caractères UTF-8 si nécessaire
        return NULL;
    }
    return combinedWord;
}

// Modifier la déclaration pour que la fonction renvoie void
CSTree insert(CSTree t, const char *mot, int offset)
{
    CSTree currentNode = t;
    wchar_t wideMot[50];
    mbstowcs(wideMot, mot, 50);
    wchar_t wide; 

    for (int i = 0; wideMot[i] != '\0'; i++)
    {
        int char_length = utf8_char_length(wideMot[i]);
        wide = convertUtf8(&wideMot[i], char_length);

        if (i == 0)
        {
            currentNode = sortContinue(&currentNode, towlower(wide), -1);
        }
        else
        {
            currentNode = sortContinue(&(currentNode->firstChild), towlower(wide), -1);
        }
        i += char_length - 1;
    }

    currentNode->firstChild = sortContinue(&(currentNode->firstChild), '\0', offset);

    return t;
}

// Exportation de l'arbre lexicographique dans un fichier .lex
void fill_array_cells_with_offset(StaticTreeWithOffset *st, CSTree t, int index_for_t, int nSiblings, int *reserved_cells)
{
    if (t == NULL)
        return;

    int firstChildIndex;
    if (t->firstChild != NULL)
        firstChildIndex = *reserved_cells;
    else
        firstChildIndex = NONE;

    st->nodeArray[index_for_t].elem = t->elem;
    st->nodeArray[index_for_t].firstChild = firstChildIndex;
    st->nodeArray[index_for_t].nSiblings = nSiblings;
    st->nodeArray[index_for_t].offset = t->offset;

    *reserved_cells += (t->firstChild != NULL) ? nChildren(t) : 0;

    if (t->firstChild != NULL)
    {
        fill_array_cells_with_offset(st, t->firstChild, firstChildIndex, nChildren(t) - 1, reserved_cells);
    }
    if (t->nextSibling != NULL)
    {
        fill_array_cells_with_offset(st, t->nextSibling, index_for_t + 1, nSiblings - 1, reserved_cells);
    }
}

StaticTreeWithOffset exportStaticTreeWithOffset(CSTree t)
{
    StaticTreeWithOffset st = {NULL, 0};
    int reserved_cells = 0;
    st.nNodes = size(t);
    st.nodeArray = malloc(st.nNodes * sizeof(ArrayCellWithOffset));

    if (st.nodeArray == NULL)
    {
        printf("Erreur lors de l'allocation mémoire pour l'arbre statique.\n");
        exit(ERROR_WRITE_FILE);
    }

    reserved_cells = nSiblings(t);
    fill_array_cells_with_offset(&st, t, 0, reserved_cells - 1, &reserved_cells);

    if (reserved_cells != st.nNodes && t != NULL)
    {
        printf("Erreur lors de la création de l'arbre statique, taille finale incorrecte\n");
        exit(ERROR_WRITE_FILE);
    }

    return st;
}

void exportStaticTreeWithOffsetToFile(StaticTreeWithOffset *st, const char *filename)
{
    FILE *file = fopen(filename, "wb");

    if (file == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(ERROR_WRITE_FILE);
    }

    fwrite(&(st->nNodes), sizeof(int), 1, file);
    fwrite(st->nodeArray, sizeof(ArrayCellWithOffset), st->nNodes, file);
    fclose(file);
}

CSTree buildWord2VecDictionaryFromFile(const char *filename)
{
    CSTree dictionary = newCSTree('@', NULL, NULL, -1);

    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Erreur lors de l'ouverture du fichier Word2Vec");
        printf("%s", filename);
        exit(ERROR_FILE_NOT_FOUND);
    }

    long long words;
    long long max_w = 80;
    int size; // Ajout de la déclaration de size
    float *M;
    char *vocab;

    fscanf(file, "%lld", &words);
    fscanf(file, "%d", &size); // Correction du format de la taille

    vocab = (char *)malloc(words * max_w * sizeof(char));
    M = (float *)malloc(words * size * sizeof(float));

    if (vocab == NULL || M == NULL)
    {
        printf("Erreur lors de l'allocation mémoire pour le dictionnaire Word2Vec\n");
        exit(EXIT_FAILURE);
    }

    for (int b = 0; b < words; b++)
    {
        int a = 0;
        while (1)
        {
            vocab[b * max_w + a] = fgetc(file);
            if (feof(file) || (vocab[b * max_w + a] == ' '))
                break;
            if ((a < max_w) && (vocab[b * max_w + a] != '\n'))
                a++;
        }
        vocab[b * max_w + a] = 0;

        for (a = 0; a < size; a++)
            fread(&M[a + b * size], sizeof(float), 1, file);

        float len = 0;
        for (a = 0; a < size; a++)
            len += M[a + b * size] * M[a + b * size];

        len = sqrt(len);

        for (a = 0; a < size; a++)
            M[a + b * size] /= len;

        // Insertion du mot dans l'arbre
        dictionary = insert(dictionary, vocab + b * max_w, ftell(file));
        //printf("%s %i\n",vocab + b * max_w,ftell(file));
    }
    // printPrefix(dictionary);
    fclose(file);

    free(vocab);
    free(M);

    return dictionary;
}

void exportTreeToFile(CSTree t, const char *filename)
{
    StaticTreeWithOffset st = exportStaticTreeWithOffset(t);
    exportStaticTreeWithOffsetToFile(&st, filename);
}


StaticTreeWithOffset loadStaticTreeWithOffsetFromFile(FILE *file)
{
    StaticTreeWithOffset st;

    fread(&(st.nNodes), sizeof(int), 1, file);

    st.nodeArray = malloc(st.nNodes * sizeof(ArrayCellWithOffset));
    if (st.nodeArray == NULL)
    {
        perror("Erreur lors de l'allocation mémoire pour l'arbre statique");
        exit(EXIT_FAILURE);
    }

    fread(st.nodeArray, sizeof(ArrayCellWithOffset), st.nNodes, file);

    return st;
}

// Recherche un mot dans le StaticTree
int searchWordInStaticTree(StaticTreeWithOffset *st, const char *word)
{
    int i = 0;
    int from = 1;
    wchar_t wide; 
    do
    {
        mbstowcs(&wide, &word[i], 1);
        from = siblingLookupStatic(st, wide, from, NONE);
        //printf("Debug: i=%d, lowerlettre=%c, from=%d\n", i, wide, from);
        i++;
    } while (word[i] != '\0' && from != NONE);

    //printf("Debug: Final from=%d\n", from);
    //printf("%i", st->nodeArray[from].offset);

    if (from != NONE)
    {
        return st->nodeArray[from].offset;
    }
    else
    {
        return -1;
    }
}

/*
    =======================================

            Prototype des fonctions
            Calculer Similarité

    =======================================
*/

//minimum de deux entiers
int min(int a, int b) {
    return a < b ? a : b;
}

// maximum de deux valeurs en double
double max(double a, double b) {
    return a > b ? a : b;
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
    //printf("distance = %d - %d - %f\n", max, distance, ((double)distance / max));
    return (1.0 - ((double)distance / max));
}


double calculScalaire(int offsetword1,int offsetword2){ 
    FILE *file = fopen("datafiles/word.bin", "rb");
    if (!file)
    {
        perror("Erreur lors de l'ouverture du fichier Word2Vec");
        exit(ERROR_FILE_NOT_FOUND);
    }
    float vecteur1[MAX_SIZE];
    float vecteur2[MAX_SIZE];
    int a;

    //inspiré du code de distance.c
    fseek(file,offsetword1,SEEK_SET);
    for (a = 0; a < MAX_SIZE; a++){
        fread(&vecteur1[a], sizeof(float), 1, file);
    }
    fseek(file,offsetword2,SEEK_SET);
    for (a = 0; a < MAX_SIZE; a++){
        fread(&vecteur2[a], sizeof(float), 1, file);
    }

    double len1 = 0;
    double len2 = 0;
    double produit = 0;

    for (a = 0; a < MAX_SIZE; a++){
        len1 += vecteur1[a] * vecteur1[a];
    } 
    for (a = 0; a < MAX_SIZE; a++){
        len2 += vecteur2[a] * vecteur2[a];
    } 
    
    // Norme vecteurs
    len1 = sqrt(len1); //Norme U
    len2 = sqrt(len2); //Norme V
    for (a = 0; a < MAX_SIZE; a++) produit += vecteur1[a] * vecteur2[a];

    //printf("len1: %f, len2: %f produit: %f\n", len1, len2, produit);
    //printf("score: %0.2f\n", (produit / (len1 * len2)));
    return produit / (len1 * len2);
}

double calculSimilarity(char *word1, char *word2, int offset1, int offset2){
    double score;
    double calcul = max(levenshtein(word1,word2),calculScalaire(offset1,offset2));
    if (calcul >= 0 && calcul <= 1){
        return calcul;
    }
    return score;
}

/*
    =======================================

            Prototype des fonctions
            FICHIERS DE PARTIE

    =======================================
*/


void writeToFileBeginGame(char *filename, char *word1, char *word2, int offset1, int offset2) {
    FILE *file = fopen(filename, "w");
    
    fprintf(file, "%s;%s", word1,word2);
    fprintf(file, "\n\n");
    fprintf(file, "%s:%i;%s:%i", word1, offset1,word2,offset2);
    fprintf(file, "\n");
    fprintf(file, "%s,%s,%0.2f;", word1, word2, calculSimilarity(word1,word2,offset1,offset2));

    fclose(file);
}

void addWordToFile(char *filename, char *word1, int offset1) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char line1[MAX_LINE_LENGTH];
    char line2[MAX_LINE_LENGTH];
    char line3[MAX_LINE_LENGTH];
    char line4[MAX_LINE_LENGTH];

    // Lecture des lignes existantes
    if (fgets(line1, sizeof(line1), file) == NULL ||
        fgets(line2, sizeof(line2), file) == NULL ||
        fgets(line3, sizeof(line3), file) == NULL ||
        fgets(line4, sizeof(line4), file) == NULL) {
        fclose(file);
        perror("Erreur lors de la lecture du fichier");
        exit(EXIT_FAILURE);
    }

    // Retour au début du fichier pour réécrire
    fseek(file, 0, SEEK_SET);

    // Écriture de la première ligne inchangée
    fputs(line1,file);
    //On raccourci sans \n pour line 4
    size_t len1 = strlen(line1);
    if (len1 > 0 && line1[len1 - 1] == '\n') {
        line1[len1 - 1] = '\0';
    }
    
    // Écriture du mot ajouté sur la deuxième ligne
    // On enleve le \n de line2
    size_t len2 = strlen(line2);
    if (len2 > 0 && line2[len2 - 1] == '\n') {
        line2[len2 - 1] = '\0';
    }
    // On ecrit tout
    if (strlen(line2) == 0 || line2[0] == '\n') {
        fprintf(file, "%s", word1);
    } else {
        fprintf(file, "%s;%s", line2, word1);
    }
    fprintf(file, "\n");

    // Écriture du mot ajouté avec son offset sur la troisième ligne
    // On enleve le \n de line3
    size_t len3 = strlen(line3);
    if (len3 > 0 && line3[len3 - 1] == '\n') {
        line3[len3 - 1] = '\0';
    }
    // On ecrit tout
    fprintf(file, "%s;%s:%i\n", line3, word1, offset1);

    // Écriture du mot ajouté avec son score de similarite pour chaque mot precedent sur la quatrieme ligne
    size_t len4 = strlen(line4);
    if (len4 > 0 && line4[len4 - 1] == '\n') {
        line4[len4 - 1] = '\0';
    }

    fputs(line4,file); // on ecrit line4 SANS \n pour rajouter apres
    
    // Extraction des mots de line1 et line2 pour iterer
    char *listemots[500];
    char *token;
    int i = 0;
    // Ici on split les mots de la ligne 1 pour les mettre dans une liste
    token = strtok(line1, ";");
    while(token != NULL){
        listemots[i] = token;
        i++;
        token = strtok(NULL, ";");
    }

    token = strtok(line2, ";");
    while(token != NULL){
        listemots[i] = token;
        i++;
        token = strtok(NULL, ";");
    }

    FILE* dictionnary = fopen("./datafiles/dic.lex", "rb");
    if (!dictionnary) {
        perror("Erreur lors de l'ouverture du dictionnaire");
        exit(EXIT_FAILURE);
    }

    StaticTreeWithOffset st = loadStaticTreeWithOffsetFromFile(dictionnary);

    // iteration sur les mots davant et word1
    for (int j = 0; j < i; j++) {
        if (strcmp(listemots[j], word1) != 0) {
            int offsetWord = searchWordInStaticTree(&st, listemots[j]);
            fprintf(file, "%s,%s,%0.2f;", word1, listemots[j], calculSimilarity(listemots[j], word1,offset1,offsetWord));
        }
    }

    fclose(file); 
}