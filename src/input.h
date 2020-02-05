
#include <stdio.h>
#include <stdlib.h>


typedef struct _filehuffmanIn{
	int tailletext;
	int taillearbre;
	char * chars;
	char * treestructure;
	char * contentorder;
}HuffmanIn;


char *readFileTXT(const char *filename);
HuffmanIn *readFileHF(const char *filename);
