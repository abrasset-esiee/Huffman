#include "arbre.h"
#include "element.h"

typedef struct HuffmanOut {
    int tailleTexte;
	int tailleArbre;
	char* caracteres;
	struct Noeud* arbre;
	char* texte;
} HuffmanOut;

HuffmanOut* createHuffmanOut(char* text);

unsigned char charToBin(Element e, char* text);