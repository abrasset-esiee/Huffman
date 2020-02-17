#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inout.h"

HuffmanOut* createHuffmanOut(char* text) {
    HuffmanOut *h = (HuffmanOut*) malloc(sizeof(HuffmanOut));
    int i = 0;
    char c = text[i];
    h->tailleTexte = 0;
    while (c != '\0') {
        h->tailleTexte++;
        i++;
        c = text[i];
    }
    // APPEL CREATION ARBRE HUFFMAN
    ListeNoeud *l = create_liste_noeud(text);
    l = sort(l);
    h->arbre = build_arbre(l);
    // APPEL NB FEUILLE ARBRE
    h->tailleArbre = nbElement(l);
    // PARCOURS INFIXE POUR STOCKER LES CARACTÈRES DE L'ARBRE
    // char caracteres[h->tailleArbre];
    // h->caracteres = getCaracteres(h->arbre, caracteres, 0);
    h->texte = text;
    return h;
}

int main(void){
    char *text = (char*) malloc(100*sizeof(char));
    text = "mohamed maachaoui";
    HuffmanOut *h = createHuffmanOut(text);
    // afficheArbre(h->arbre, 0);
    for (int i = 0; i < h->tailleArbre; i++) {
        printf("%c\n", h->caracteres[i]);
    }
    // CONTRUIRE LE FICHIER HF
}

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
        int old = 0,new;
        int pos = 0;
        int nbOctet = 1;
        fcontent->treestructure = (int*) malloc(sizeof(int));
        while(total < fcontent->taillearbre){

            int oct ;
            fread(&oct, 1, 1, fp);
            fcontent->treestructure = (int*)realloc(fcontent->treestructure,sizeof(int)*8*nbOctet);
            int j;
            for(j = 7; j>=0;j--){
                new = oct >> j & 0x1;
                if(new== 1 && old == 0){
                    total++;
                }
                old = new;
                fcontent->treestructure[pos] = new;
                pos++;
            }
            nbOctet++;
	    }
        fcontent->sizeTreeStructure = pos;

        //Recupere l'odre de la chaine caracteres avec leur code
        fcontent->contentorder = (int*) malloc(sizeof(int));

        int oct ;
        nbOctet = 1;
        pos = 0;
        while(!feof(fp)){
            fcontent->contentorder = (int*)realloc(fcontent->contentorder,sizeof(int)*8*nbOctet++);
            int j;
            if(fread(&oct, 1, 1, fp)==1){
                for( j = 7; j>=0;j--){

                    fcontent->contentorder[pos] = (int)(oct >> j & 0x1);
                    pos++;
                }
            }
        }
            fclose(fp);
    }
    return fcontent;
}

HuffmanOut inToOut(HuffmanIn *file) {
    HuffmanOut out;
    out.tailleArbre = file->taillearbre;
    out.tailleTexte = file->tailletext;
    out.caracteres = (char *) file->chars;
    out.arbre = createArbreFromInfix(file);
    out.texte = createMot(file->contentorder,out.tailleTexte,out.arbre);
    return out;
}

Noeud *createArbreFromInfix(HuffmanIn *file) {
    Noeud *racine = (Noeud *) malloc(sizeof(Noeud));


    ListeNoeud *pile = (ListeNoeud *) malloc(sizeof(ListeNoeud));
    int count = -1;
    int countFeuille = 0;
    empiler(pile, racine);
    Noeud *noeud = racine;
    noeud->gauche = NULL;
    noeud->droite = NULL;

    while (countFeuille < file->taillearbre) {
        count++;
        if (file->treestructure[count] == 0) {

            Noeud *n = (Noeud *) malloc(sizeof(Noeud));
            n->gauche = NULL;
            n->droite = NULL;
            Caractere *carac = (Caractere *) malloc(sizeof(Caractere));
            carac->nb_Occurrence = 0;
            carac->code = "";
            carac->valeur = 0;
            noeud->caractere = carac;
            if (noeud->gauche == NULL) {
                noeud->gauche = n;
            } else {
                noeud->droite = n;
            }
            empiler(pile, noeud);
            noeud = n;
        } else {
            if (file->treestructure[count - 1] == 0) {
                Caractere *carac = (Caractere *) malloc(sizeof(Caractere));
                noeud->caractere = carac;
                noeud->caractere->valeur = (char) file->chars[countFeuille];
                countFeuille++;
            }

            noeud = depiler(pile);
        }

    }
    return racine;
}

char *createMot(int *bin_text, int taille_text, Noeud *racine) {
    char * mot = (char *)malloc(taille_text + 1);
    int count = 0;

    int i = 0;
    while (count < taille_text) {
        Noeud *current = racine;
        while (current->caractere->valeur == 0) {
            if (bin_text[i]==0) {
                current = current->gauche;
            } else {
                current = current->droite;
            }

            i++;
        }
        mot[count] = current->caractere->valeur;

        count++;
    }

    mot[taille_text] = '\0';
    return mot;

}

// int main(void) {
//     HuffmanIn *fcontent = readFileHF("test/exemple-fourni.txt.hf");
//     HuffmanOut out = inToOut(fcontent);
//     // afficheArbre(out.arbre, 0);
//     printf("%s",out.texte);
// }
