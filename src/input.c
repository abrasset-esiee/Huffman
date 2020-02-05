
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

char *readFileHF(const char *filename)
{
    char *fcontent = NULL;
    int fsize = 0;
    FILE *fp;

    fp = fopen(filename, "rb");
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

int main(){
	unsigned char *fcontent = readFileHF("../test/exemple-fourni.txt.hf");
	printf("%0.2x", fcontent[1]);
	printf("%0.2x ", fcontent[0]);
	printf("%0.2x", fcontent[3]);
	printf("%0.2x ", fcontent[2]);
	printf("%0.2x", fcontent[5]);
	printf("%0.2x\n", fcontent[4]);

	
}


