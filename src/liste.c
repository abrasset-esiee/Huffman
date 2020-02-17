#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

ListeNoeud *create_liste_noeud(const char *text) {
    ListeNoeud *l = (ListeNoeud *) malloc(sizeof(ListeNoeud));
    l->premier = NULL;
    int i = 0;
    while (text[i] != '\0') {
        int trouve = 0;
        ElementNoeud *e = l->premier;
        while (!trouve) {
            if (e == NULL) { // Insertion en debut de liste
                e = (ElementNoeud *) malloc(sizeof(ElementNoeud));
                Caractere *c = (Caractere *) malloc(sizeof(Caractere));
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

ListeNoeud *sort(ListeNoeud *l) {
    ListeNoeud *listeTri = (ListeNoeud *) malloc(sizeof(ListeNoeud));
    listeTri->premier = NULL;
    ElementNoeud *parcoursSort = l->premier;
    while (parcoursSort != NULL) {

        insert(listeTri, parcoursSort->noeud);
        parcoursSort = parcoursSort->suivant;
    }
    return listeTri;
}

void insert(ListeNoeud *l, Noeud *elem) {
    //Création d'un nouvel ElementNoeud
    ElementNoeud *e = (ElementNoeud *) malloc(sizeof(ElementNoeud));
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

Noeud *build_arbre(ListeNoeud *l) {
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
    Noeud *fusion = (Noeud *) malloc(sizeof(Noeud));
    Caractere *caractere = (Caractere *) malloc(sizeof(Caractere));
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
int nbElement(ListeNoeud *l) {
    ElementNoeud *e = l->premier;
    int cpt = 0;
    while (e != NULL) {
        cpt++;
        e = e->suivant;
    }
    return cpt;
}

void empiler(ListeNoeud *pile, Noeud *n) {
    ElementNoeud *elem = (ElementNoeud *) malloc(sizeof(ElementNoeud));
    elem->noeud = n;
    elem->suivant = pile->premier;
    pile->premier = elem;
}

Noeud *depiler(ListeNoeud *pile) {
    if (pile->premier != NULL) {
        ElementNoeud *elem = pile->premier;
        pile->premier = pile->premier->suivant;
        return elem->noeud;
    } else {
        printf("pile vide");
        exit(EXIT_FAILURE);
    }
}
