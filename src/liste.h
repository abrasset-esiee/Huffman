#include "arbre.h"

typedef struct ListeNoeud {
    ElementNoeud *premier;
} ListeNoeud;

typedef struct ElementNoeud {
    Noeud *noeud;
    ElementNoeud *suivant;
} ElementNoeud;

ListeNoeud* create_liste_noeud(char *text);