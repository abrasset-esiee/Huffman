#include "arbre.h"

typedef struct ElementNoeud {
    Noeud *noeud;
    struct ElementNoeud *suivant;
} ElementNoeud;

typedef struct ListeNoeud {
    ElementNoeud *premier;
} ListeNoeud;

ListeNoeud* create_liste_noeud(char *text);
ListeNoeud* sort(ListeNoeud *l);
void insert(ListeNoeud *l, Noeud* e);
void afficheListe(ListeNoeud *l);
Noeud* build_arbre(ListeNoeud *l);
int nbElement(ListeNoeud *l);