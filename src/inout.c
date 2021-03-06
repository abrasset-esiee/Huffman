#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inout.h"

int ind = 0;
int indexParcours = 0;

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
    // APPEL NB FEUILLE ARBRE
    h->tailleArbre = nbElement(l);
    l = sort(l);
    ListeCaractere *lc = create_liste_caracteres(l);
    h->arbre = build_arbre(l);
    printf("Affichage codage des caractères :\n");
    afficheListeCaracteres(lc);
    h->texte = generateEncodeText(text, lc);
    h->caracteres = (char*) malloc(sizeof(char) * h->tailleArbre);
    h->parcours = (int*) malloc(sizeof(int));
    getCaracteres(h->arbre, h->caracteres, h->parcours);
    return h;
}

void getCaracteres(Noeud *n, char *c, int *parcours) {
    if (n != NULL) {
        if (n->gauche != NULL) {
            parcours[indexParcours++] = 0;
            parcours = realloc(parcours, sizeof(int) * (indexParcours + 1));
            getCaracteres(n->gauche, c, parcours);
        }
        if (n->gauche == NULL && n->droite == NULL) {
            c[ind] = n->caractere->valeur;
            ind++;
        }
        if (n->droite != NULL) {
            parcours[indexParcours++] = 0;
            parcours = realloc(parcours, sizeof(int) * (indexParcours + 1));
            getCaracteres(n->droite, c, parcours);
        }
    }
    parcours[indexParcours++] = 1;
    parcours = realloc(parcours, sizeof(int) * (indexParcours + 1));
}

char* generateEncodeText(char* text, ListeCaractere *l) {
    char* encodeText = (char*) malloc(sizeof(char));
    int i = 0;
    char c = text[i];
    while (c != '\0') {
        ElementCaractere *e = l->premier;
        while (e != NULL) {
            if (c == e->caractere->valeur) {
                encodeText = realloc(encodeText, sizeof(char) * (strlen(encodeText) + strlen(e->caractere->code)));
                strcat(encodeText, e->caractere->code);
                break;
            }
            e = e->suivant;
        }
        i++;
        c = text[i];
    }
    return encodeText;
}

void compress(HuffmanOut *h) {
    FILE *file = fopen("test.txt.hf", "wb");
    fwrite(&(h->tailleTexte), 4, 1, file);
    fwrite(&(h->tailleArbre), 1, 1, file);
    for (int i = 0; i < h->tailleArbre; i++) {
        fwrite(&(h->caracteres[i]), 1, 1, file);
    }
    unsigned char code;
    int old = 0;
    int cpt = 0;
    int i;
    for (i = 0; i < indexParcours; i++) {
        if (old == 0 && h->parcours[i] == 1) {
            cpt++;
        }
        code = (code << 1) | h->parcours[i];
        if (cpt == h->tailleArbre - 1) {
            break;
        }
        old = h->parcours[i];
    }
    int nbOctet = i / 8;
    if (i % 8 != 0) {
        nbOctet++;
    }
    fwrite(&code, nbOctet, 1, file);
    unsigned char code2;
    for (int i = 0; i < strlen(h->texte); i++) {
        code2 = (code2 << 1) | ((int) h->texte[i] - 48);
    }
    nbOctet = (int) strlen(h->texte) / 8;
    if ((int) strlen(h->texte) % 8 != 0) {
        nbOctet++;
    }
    fwrite(&code2, nbOctet, 1, file);
    fclose(file);
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



char *getTextFrom(HuffmanIn *file) {

    return createMot(file->contentorder,file->tailletext,createArbreFromInfix(file));
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