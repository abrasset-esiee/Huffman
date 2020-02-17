#include "liste.h"

typedef struct HuffmanOut {
    int tailleTexte;
	int tailleArbre;
	char* caracteres;
	struct Noeud* arbre;
	char* texte;
} HuffmanOut;

HuffmanOut* createHuffmanOut(char* text);