#include "huffman.h"
#include <stdlib.h>

Huffman* createHuffman() {
    Huffman *h = (Huffman*) malloc(sizeof(Huffman));
    h->tailleTexte = 0;
    h->tailleArbre = 0;
    h->caracteres = NULL;
    h->arbre = NULL;
    h->texte = NULL;
    return h;
}

unsigned char charToBin(Liste l, char*) {

}

char* binToChar(Liste l, unsigned char) {

}