
#include <stdio.h>
#include <stdlib.h>
#include "input.h"
char *readFileTXT(const char *filename)
{
    char *fcontent = NULL;
    int fsize = 0;
    FILE *fp;

    fp = fopen(filename, "r");
    if(fp) {
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        rewind(fp);

        fcontent = (char*) malloc(sizeof(char) * fsize);
        fread(fcontent, 1, fsize, fp);

        fclose(fp);
    }
    return fcontent;

}

HuffmanIn *readFileHF(const char *filename)
{
    HuffmanIn *fcontent = NULL;
    int fsize = 0;
    FILE *fp;

    fp = fopen(filename, "rb");
    if(fp) {
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        rewind(fp);


        fcontent = (HuffmanIn*) malloc(sizeof(HuffmanIn));
        fread(&(fcontent->tailletext), 4, 1, fp);
	fread(&(fcontent->taillearbre), 1, 1, fp);
	fcontent->chars = (char*) malloc(sizeof(char)*fcontent->taillearbre);
	for(int i = 0;i<fcontent->taillearbre;i++){
		fread(&(fcontent->chars[i]), 1, 1, fp);
	}
	


        fclose(fp);
    }

    return fcontent;

}

int main(){
	HuffmanIn *fcontent = readFileHF("../test/exemple-fourni.txt.hf");

	printf("%u\n", fcontent->tailletext);
	printf("%u\n", fcontent->taillearbre);
	for(int i = 0;i<fcontent->taillearbre;i++){
		
		printf("%c ", fcontent->chars[i]);
	}
	

	
}


