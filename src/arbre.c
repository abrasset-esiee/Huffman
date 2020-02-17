#include "arbre.h"

Noeud* create_noeud(Caractere *c, Noeud *g, Noeud *d) {
    Noeud *noeud = (Noeud*) malloc(sizeof(Noeud));
    noeud->caractere = c;
    noeud->gauche = g;
    noeud->droite = d;
    return noeud;
}

void afficheArbre(Noeud *arbre, int nbTab) {
    if (arbre != NULL) {
        for (int i = 0; i < nbTab; i++) {
            printf("\t");
        }
        printf("(%d)  %c\n", arbre->caractere->nb_Occurrence, arbre->caractere->valeur);
        if (arbre->gauche != NULL) {
            for (int i = 0; i < nbTab; i++) {
                printf("\t");
            }
            printf("  \\--0--\n");
        }
        afficheArbre(arbre->gauche, nbTab + 1);
        if (arbre->droite != NULL) {
            for (int i = 0; i < nbTab; i++) {
                printf("\t");
            }
            printf("  \\--1--\n");
        }
        afficheArbre(arbre->droite, nbTab + 1);
    }
}

void setCodes(Noeud *n) {
    if (n != NULL) {
        if (n->caractere->code == NULL) {
            n->gauche->caractere->code = "0";
            n->droite->caractere->code = "1";
        } else {
            if (n->gauche != NULL) {
                n->gauche->caractere->code = (char*) malloc(sizeof(char) * (strlen(n->caractere->code) + 1));
                strcat(strcat(n->gauche->caractere->code,n->caractere->code), "0");
            }
            if (n->droite != NULL) {
                n->droite->caractere->code = (char*) malloc(sizeof(char) * (strlen(n->caractere->code) + 1));
                strcat(strcat(n->droite->caractere->code,n->caractere->code), "1");
            }
        }
        setCodes(n->gauche);
        setCodes(n->droite);
    }
}


