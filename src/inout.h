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
	ListeCaractere *caracteres;
	struct Noeud* arbre;
	char* texte;
} HuffmanOut;

HuffmanOut* createHuffmanOut(char* text);
ListeCaractere* getCaracteres(Noeud *n);
char *readFileTXT(const char *filename);
HuffmanIn *readFileHF(const char *filename);
Noeud * createArbreFromInfix(HuffmanIn* file);
char* getTextFrom(HuffmanIn *file);
char *createMot(int *bin_text, int taille_text, Noeud *racine);