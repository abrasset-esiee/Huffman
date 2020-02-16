#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HuffmanOut* createHuffmanOut(char* text) {
    HuffmanOut *h = (HuffmanOut*) malloc(sizeof(HuffmanOut));
    int i = 0;
    char c = text[i];
    h->tailleTexte = 0;
    while (c != '\0') {
        h->tailleTexte++;
        i++;
        c = text[i];
    }
    // APPEL CREATION ARBRE HUFFMAN
    // h->arbre = NULL;
    // APPEL NB FEUILLE ARBRE
    // h->tailleArbre = 0;
    // PARCOURS INFIXE POUR STOCKÉ LES CARACTÈRES DE L'ARBRE
    // h->caracteres = NULL;
    h->texte = text;
    return h;
}

int main(void){
    char *text = (char*) malloc(100*sizeof(char));
    text = "yoann la pute";
    HuffmanOut *h = createHuffmanOut(text);
    // CONTRUIRE LE FICHIER HF
}