#include "arbre.h"
#include "liste.h"

typedef struct Huffman {
    int tailleTexte;
	int tailleArbre;
	char* caracteres;
	struct Noeud* arbre;
	char* texte;
} Huffman;

Huffman* createHuffman();

unsigned char charToBin(Liste l, char*);

char* binToChar(Liste l, unsigned char);