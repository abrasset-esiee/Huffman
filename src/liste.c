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
            if (e == NULL) {
                e = (ElementNoeud*) malloc(sizeof(ElementNoeud));
                Caractere *c = (Caractere*) malloc(sizeof(Caractere));
                c->valeur = text[i];
                c->nb_Occurence = 1;
                c->code = NULL;
                e->noeud = create_noeud(c, NULL, NULL);
                e->suivant = l->premier;
                l->premier = e;
                trouve = 1;
            } else {
                if (e->noeud->caractere->valeur == text[i]) {
                    e->noeud->caractere->nb_Occurence++;
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
    ElementNoeud *parcours = l->premier;
    while (parcours != NULL) {
        insert(listeTri, parcours);
        parcours = parcours->suivant;
    }
    return listeTri;    
}

void insert(ListeNoeud *l, ElementNoeud *e) {
    ElementNoeud *parcours = (ElementNoeud*) malloc(sizeof(ElementNoeud));
    parcours->noeud = NULL;
    parcours->suivant = l->premier;
    while (parcours->suivant != NULL) {
        if (e->noeud->caractere->nb_Occurence > parcours->noeud->caractere->nb_Occurence) {
            parcours = parcours->suivant;
        }
        else {
            e->suivant = parcours->suivant;
            parcours->suivant = e;
            break;
        }
    }
}

Noeud* build_arbre(ListeNoeud *l) {
    return NULL;
}

int main(void) {
    char *test = "mohamed maachaoui";
    ListeNoeud *l = create_liste_noeud(test);
    l = sort(l);
    ElementNoeud *e = l->premier;
    while (e != NULL) {
        affiche_arbre(e->noeud);
        e = e->suivant;
    }
}