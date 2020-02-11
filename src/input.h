
#include <stdio.h>
#include <stdlib.h>


typedef struct _filehuffmanIn{
    unsigned char tailletext;
	unsigned char taillearbre;
	unsigned char * chars;
	int sizeTreeStructure;
	int * treestructure;
    int * contentorder;
}HuffmanIn;


char *readFileTXT(const char *filename);
HuffmanIn *readFileHF(const char *filename);
