
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
	//Recupere la longueur de la chaine de chararcteres
        fcontent = (HuffmanIn*) malloc(sizeof(HuffmanIn));
        fread(&(fcontent->tailletext), 4, 1, fp);

	//Recupere le nombre de characteres presents
	fread(&(fcontent->taillearbre), 1, 1, fp);

	//Recupere les caracteres en ASCII
	fcontent->chars = (char*) malloc(sizeof(char)*fcontent->taillearbre);
	fread(fcontent->chars, fcontent->taillearbre, 1, fp);

	//Recupere les données de la structure de l'arbre
	int total = 0;
	int old,new;
	int pos = 0;
	int nbOctet = 1;
	fcontent->treestructure = (char*) malloc(sizeof(char));
	while(total < fcontent->taillearbre){
		
		int oct ;
		fread(&oct, 1, 1, fp);
		fcontent->treestructure = (char*)realloc(fcontent->treestructure,sizeof(char)*8*nbOctet);
		
		for(int j = 7; j>=0;j--){
			new = (oct>>j)&0x1;	
			if(new== 1 && old == 0){
				total++;
			}
			old = new;
			fcontent->treestructure[pos] = new;
			pos++;
		}
		nbOctet++;		

	}printf("\n");
	//fcontent->treestructure = (char*)realloc(fcontent->treestructure,sizeof(char)*8*nbOctet + 1);
	//fcontent->treestructure[pos+1] = '\0';
	fcontent->sizeTreeStructure = pos;

	//Recupere l'odre des caracteres avec leur code
	/*int total = 0;
	int old,new;
	int pos = 0;
	
	fcontent->treestructure = (int*) malloc(sizeof(int));
	while(total < fcontent->taillearbre){
		
		int oct ;
		fread(&oct, 1, 1, fp);
		fcontent->treestructure = (int*)realloc(fcontent->treestructure,sizeof(int)*8*nbOctet);
		
		for(int j = 7; j>=0;j--){
			new = (oct>>j)&0x1;	
			if(new== 1 && old == 0){
				total++;
			}
			old = new;
			fcontent->treestructure[pos] = new;
			pos++;
		}
		nbOctet++;		

	}printf("\n");
	fcontent->sizeTreeStructure = pos;*/
	/*fcontent->treestructure = (int*) malloc(sizeof(int)*fcontent->taillearbre/8+1);
	fread(fcontent->treestructure, fcontent->taillearbre/8+1, 1, fp);*/


        fclose(fp);
    }

    return fcontent;

}

int main(){
	HuffmanIn *fcontent = readFileHF("../test/exemple-fourni.txt.hf");

	printf("%u\n", fcontent->tailletext);
	printf("%u\n", fcontent->taillearbre);
	for(int i = 0;i<fcontent->taillearbre;i++){
		
		printf("%d ", fcontent->chars[i]);
	}
	printf("\n");
	for(int i = 0;i<fcontent->sizeTreeStructure+1;i++){
	
			printf("%d ", fcontent->treestructure[i]);


	}
	//printf("%s", *fcontent->treestructure);
	

	
}


