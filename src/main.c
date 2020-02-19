#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inout.h"

int main(void){
    char *text = (char*) malloc(100*sizeof(char));
    text = "mohamed maachaoui";
    printf("Texte à compressé : %s\n", text);
    HuffmanOut *h = createHuffmanOut(text);
    printf("Affichage de l'arbre de Huffman :\n");
    afficheArbre(h->arbre, 0);
    compress(h);
    HuffmanIn *fcontent = readFileHF("test.txt.hf");
    char *text2 = getTextFrom(fcontent);
    printf("Texte compressé : %s\n", text2);
    fcontent = readFileHF("exemple-fourni.txt.hf");
    char *text3 = getTextFrom(fcontent);
    printf("Texte VALIDE compressé :\n%s\n", text3);
}