#include "huffmanout.h"
#include <stdlib.h>

HuffmanOut* createHuffmanOut(char* text) {
    HuffmanOut *h = (HuffmanOut*) malloc(sizeof(HuffmanOut));
    char i = "";
    h->tailleTexte = 0;
    while (i != "\0")
        h->tailleTexte++;
    
    h->tailleArbre = 0;
    h->caracteres = NULL;
    h->arbre = NULL;
    h->texte = NULL;
    return h;
}

unsigned char charToBin(Element e, char* text) {

}
