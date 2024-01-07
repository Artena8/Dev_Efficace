#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include <wchar.h>
#include "../headers/game.h"

// Q1 Alloue un nouveau noeud pour un CSTree
CSTree newCSTree(Element elem, CSTree firstChild, CSTree nextSibling, int offset)
{
    CSTree t = malloc(sizeof(Node));
    if (t == NULL)
        exit(EXIT_FAILURE);
    t->elem = elem;
    t->firstChild = firstChild;
    t->nextSibling = nextSibling;
    t->offset = offset;
    return t;
}

// Q3 Imprime t en ordre préfixe
void printPrefix(CSTree t)
{
    if (t == NULL)
        return;
    printf("%c ", t->elem);
    printPrefix(t->firstChild);
    printPrefix(t->nextSibling);
}

// Q4 Compte le nombre de noeuds dans l’arbre t.
int size(CSTree t)
{
    if (t == NULL)
        return 0;
    return 1 + size(t->firstChild) + size(t->nextSibling);
}

// Q5 Compte le nombre d’enfants du nœud t.
int nSiblings(CSTree child)
{
    if (child == NULL)
        return 0;
    return nSiblings(child->nextSibling) + 1;
}

int nChildren(CSTree t)
{
    if (t == NULL || t->firstChild == NULL)
        return 0;
    return nSiblings(t->firstChild);
}

// Q7 Renvoie le premier frère de t contenant l’élément e (ou t lui-même), NULL si aucun n’existe.
CSTree siblingLookup(CSTree t, Element e)
{
    if (t == NULL || t->elem > e)
        return NULL;
    if (t->elem == e)
        return t;
    return siblingLookup(t->nextSibling, e);
}

// Q8 on suppose que les frères de *t sont triés par ordre croissant.
//    Renvoie le premier frère de *t contenant e, un nouveau noeud est créé si absent
CSTree sortContinue(CSTree *t, Element e, int offset)
{
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
int siblingLookupStatic(StaticTreeWithOffset *st, Element e, int from, int len)
{
    if (len == NONE)
    {
        len = st->nodeArray[from].nSiblings + 1;
        //printf("Lettre %c nsblings : %d\n", st->nodeArray[from].elem, len);
    }

    for (int i = from; i < from + len; i++)
    {
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


// Q10 Comme siblingLookupStatic, mais par dichotomie
//     cette fonction peut être itérative
int siblingDichotomyLookupStatic(StaticTreeWithOffset *st, Element e, int from, int len)
{
    if (len == NONE)
    {
        len = st->nodeArray[from].nSiblings + 1;
        printf("Lettre %c nsblings : %d\n", st->nodeArray[from].elem, len);
    }

    while (len > 0)
    {
        int mid = from + len / 2;
        printf("searched : %c\n", st->nodeArray[from].elem);
        printf("searched : %i\n", e == st->nodeArray[mid].elem);
        if (e == st->nodeArray[mid].elem)
        {
            printf("Lettre %c enfant : %d\n", st->nodeArray[mid].elem, st->nodeArray[mid].firstChild);
            return st->nodeArray[mid].firstChild;
        }
        if (e > st->nodeArray[mid].elem)
        {
            // Update len and from for the right half
            from = mid + 1;
            len = len - (mid - from);
        }
        else
        {
            // Update len and from for the left half
            len = mid - from;
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

void convertUtf8ToWideChar(const char *utf8Str, wchar_t *wideCharStr)
{
    int i = 0;
    int j = 0;
    char tempcarac[4] = {0};

    while (utf8Str[i] != '\0')
    {
        if ((utf8Str[i] & 0xC0) == 0xC0)
        {
            int k;
            for (k = 0; (utf8Str[i] & (0x80 >> k)) != 0; k++)
            {
                tempcarac[k] = utf8Str[i + k];
            }
            tempcarac[k] = '\0';
            i += k - 1;
            mbstate_t state = {0};
            wchar_t wc;
            mbrtowc(&wc, tempcarac, k, &state);
            wideCharStr[j++] = wc;
        }
        else
        {
            wideCharStr[j++] = utf8Str[i];
        }
        i++;
    }

    wideCharStr[j] = L'\0';
    wprintf(L"%ls\n", wideCharStr);
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
        // printf("%s %i\n",vocab + b * max_w,ftell(file));
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

void printNicePrefixStaticTree_aux(StaticTreeWithOffset *st, int index, int depth)
{
    if (index == NONE)
        return;
    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("%c\n", st->nodeArray[index].elem);
    printNicePrefixStaticTree_aux(st, st->nodeArray[index].firstChild, depth + 1);
    if (st->nodeArray[index].nSiblings > 0)
        printNicePrefixStaticTree_aux(st, index + 1, depth);
}

void printNicePrefixStaticTree(StaticTreeWithOffset *st)
{
    if (st->nNodes > 0)
        printNicePrefixStaticTree_aux(st, 0, 0);
}

void printDetailsStaticTree(StaticTreeWithOffset *st)
{
    int i;
    printf("elem     \t");
    for (i = 0; i < st->nNodes; i++)
        printf("%c\t", st->nodeArray[i].elem);
    printf("\n");
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
