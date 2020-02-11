#include <stdlib.h>
#include "liste.h"
#include "arbre.h"

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
            } else {
                if (e->noeud->caractere->valeur == text[i]) {
                    e->noeud->caractere->nb_Occurence++;
                    trouve = 1;
                } else {
                    e = e->suivant;
                }
            }
        }
    }
    return l;
}