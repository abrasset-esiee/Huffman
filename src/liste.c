#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

ListeNoeud* create_liste_noeud(char *text) {
    ListeNoeud *l = (ListeNoeud*) malloc(sizeof(ListeNoeud));
    l->premier = NULL;
    int i = 0;
    while (text[i] != '\0') {
        int trouve = 0;
        ElementNoeud *e = l->premier;
        while (!trouve) {
            if (e == NULL) { // Insertion en debut de liste
                e = (ElementNoeud*) malloc(sizeof(ElementNoeud));
                Caractere *c = (Caractere*) malloc(sizeof(Caractere));
                c->valeur = text[i];
                c->nb_Occurrence = 1;
                c->code = NULL;
                e->noeud = create_noeud(c, NULL, NULL);
                e->suivant = l->premier;
                l->premier = e;
                trouve = 1;
            } else {
                if (e->noeud->caractere->valeur == text[i]) {
                    e->noeud->caractere->nb_Occurrence++;
                    trouve = 1;
                } else {
                    e = e->suivant;
                }
            }
        }
        i++;
    }
    return l;
}

ListeNoeud* sort(ListeNoeud *l) {
    ListeNoeud *listeTri = (ListeNoeud*) malloc(sizeof(ListeNoeud));
    listeTri->premier = NULL;
    ElementNoeud *parcoursSort = l->premier;
    while (parcoursSort != NULL) {

        insert(listeTri, parcoursSort->noeud);
        parcoursSort = parcoursSort->suivant;
    }
    return listeTri;
}

void insert(ListeNoeud *l, Noeud* elem) {
    //Création d'un nouvel ElementNoeud
    ElementNoeud * e = (ElementNoeud *)malloc(sizeof(ElementNoeud));
    e->noeud = elem;
    e->suivant = NULL;
    ElementNoeud *parcours = l->premier;
    if (parcours == NULL) { 
        // Insertion premier element pour liste vide
        l->premier = e;
        e->suivant = NULL;
    } else {
        //Insertion element en début de liste
        if (e->noeud->caractere->nb_Occurrence <= l->premier->noeud->caractere->nb_Occurrence) {
            e->suivant = l->premier;
            l->premier = e;
        } else {
            while (1) {
                if (parcours->suivant != NULL) { // Insertion en milieu de liste
                    if (e->noeud->caractere->nb_Occurrence > parcours->suivant->noeud->caractere->nb_Occurrence) {
                        parcours = parcours->suivant;
                    } else {
                        e->suivant = parcours->suivant;
                        parcours->suivant = e;
                        break;
                    }
                } else { // Insertion en fin de liste
                    parcours->suivant = e;
                    break;
                }
            }
        }
    }
}

void afficheListe(ListeNoeud *l) {
    printf("-------------------\n");
    ElementNoeud *parcours = l->premier;
    while (parcours != NULL) {
        printf(
            "%c %d\n", 
            parcours->noeud->caractere->valeur, 
            parcours->noeud->caractere->nb_Occurrence
        );
        parcours = parcours->suivant;
    }
}

Noeud* build_arbre(ListeNoeud *l) {
    if (l->premier == NULL) {
        exit(EXIT_FAILURE);
    }
    if (l->premier->suivant == NULL) {
        setCodes(l->premier->noeud);
        return l->premier->noeud;
    }
    // Recupération 2 premiers noeuds
    Noeud *n1 = l->premier->noeud;
    Noeud *n2 = l->premier->suivant->noeud;
    // Supprimer les deux premiers elem de la liste
    l->premier = l->premier->suivant->suivant;
    // Fusion 2 premiers noeud : nb_Oc de la racine vaut somme des deux
    Noeud *fusion = (Noeud*) malloc(sizeof(Noeud));
    Caractere *caractere = (Caractere*) malloc(sizeof(Caractere));
    caractere->valeur = 0;
    caractere->nb_Occurrence = n1->caractere->nb_Occurrence + n2->caractere->nb_Occurrence;
    caractere->code = NULL;
    fusion->caractere = caractere;
    fusion->gauche = n1;
    fusion->droite = n2;
    // Insert ordonné dans la liste
    insert(l, fusion);
    return build_arbre(l);
}

int main() {
    /*char *test = "mohamed maachaoui";
    ListeNoeud *l = create_liste_noeud(test);
    l = sort(l);
    Noeud *n = build_arbre(l);
    afficheArbre(n, 0);*/


        HuffmanIn *fcontent = readFileHF("../test/exemple-fourni.txt.hf");

    printf("TAILLE FICHIER : %u\n", fcontent->tailletext);
    printf("NB CARACTERES : %u\n", fcontent->taillearbre);
    int i;
    for(i = 0;i<fcontent->taillearbre;i++){

        printf("%c ", fcontent->chars[i]);
    }
    printf("\n");

    for( i = 0;i<fcontent->sizeTreeStructure;i++){
        printf("%d ", fcontent->treestructure[i]);
    }
    printf("\n");
    for(i = 0;i<fcontent->tailletext;i++){
        printf("%d ", fcontent->contentorder[i]);
    }
        HuffmanOut out = inToOut(fcontent);
    afficheArbre(out.arbre,0);


}


HuffmanOut inToOut(HuffmanIn* file) {
    HuffmanOut out;
    out.tailleArbre = file->taillearbre;
    out.tailleTexte = file->tailletext;
    out.caracteres = file->chars;
    out.arbre = createArbreFromInfix(file);

    return out;
}


Noeud *createArbreFromInfix(HuffmanIn* file){
    Noeud * racine = (Noeud*)malloc(sizeof(Noeud));


    ListeNoeud *pile = (ListeNoeud *)malloc(sizeof(ListeNoeud));
    int count = -1;
    int countFeuille = 0;
    empiler(pile,racine);
    Noeud *noeud = racine;
    noeud->gauche = NULL;
    noeud->droite = NULL;

    while(countFeuille < file->taillearbre){
        count ++;
        printf("%d\n",count);
        if(file->treestructure[count]==0){

            Noeud * n = (Noeud*)malloc(sizeof(Noeud));
            n->gauche = NULL;
            n->droite = NULL;
            Caractere *carac = (Caractere *)malloc(sizeof(Caractere));
            carac->nb_Occurrence = 0;
            carac->code = "";
            carac->valeur = NULL;
            noeud->caractere = carac;
            if(noeud->gauche == NULL){
                printf("gauche\n");
                noeud->gauche = n;
            }else{
                printf("droit\n");
                noeud->droite = n;
            }
            empiler(pile,noeud);
            //printf("n = %p\n",n);
            noeud = n;
        }else{
            if(file->treestructure[count-1] == 0){
                printf("feuille  == [%d]=%c \n",countFeuille,file->chars[countFeuille]);
                Caractere *carac = (Caractere *)malloc(sizeof(Caractere));
                noeud->caractere = carac;
                noeud->caractere->valeur = (char)file->chars[countFeuille];
                countFeuille++;
            }

            noeud = depiler(pile);
        }

    }return racine;
}

void empiler(ListeNoeud * pile, Noeud * n){
   // printf("empiler = %p\n",n->gauche);
    //printf("empiler = %p\n",n->droite);
    ElementNoeud * elem = (ElementNoeud*)malloc(sizeof(ElementNoeud));
    elem->noeud = n;
    elem->suivant = pile->premier;
    pile->premier = elem;
}

Noeud * depiler(ListeNoeud * pile){
    if(pile->premier != NULL){
        ElementNoeud * elem = pile->premier;
        pile->premier = pile->premier->suivant;
        //printf("depiler = %p\n",elem->noeud->gauche);
        return elem->noeud;
    }else{
        printf("pile vide");
        exit(EXIT_FAILURE);
    }
}