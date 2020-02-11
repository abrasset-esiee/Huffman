typedef struct Liste {
    Element *premier;
} Liste;

typedef struct Element {
    void *courant;
    Element *suivant;
} Element;

Liste* create_liste(char *text);