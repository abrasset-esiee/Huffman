#include "liste.h"

typedef struct HuffmanIn{
    unsigned char tailletext;
	unsigned char taillearbre;
	unsigned char * chars;
	int sizeTreeStructure;
	int * treestructure;
    int * contentorder;
} HuffmanIn;

typedef struct HuffmanOut {
    int tailleTexte;
	int tailleArbre;
	char* caracteres;
	struct Noeud* arbre;
	char* texte;
} HuffmanOut;

HuffmanOut* createHuffmanOut(char* text);
char *readFileTXT(const char *filename);
HuffmanIn *readFileHF(const char *filename);
Noeud * createArbreFromInfix(HuffmanIn* file);
HuffmanOut inToOut(HuffmanIn* file);
char *createMot(int *bin_text, int taille_text, Noeud *racine);