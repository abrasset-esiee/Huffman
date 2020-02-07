
#include <stdio.h>
#include <stdlib.h>


typedef struct _filehuffmanIn{
	int tailletext;
	int taillearbre;
	char * chars;
	int sizeTreeStructure;
	int * treestructure;
	int * contentorder;
}HuffmanIn;


char *readFileTXT(const char *filename);
HuffmanIn *readFileHF(const char *filename);
