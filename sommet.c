#include <stdlib.h>
#include "sommet.h"

struct sommet* new_sommet(char label){
  struct sommet* new = malloc(sizeof(struct sommet));
  new->couleur = 0;
  new->label = label;
  new->degre = 0;
  return new;
}

void free_sommet(struct sommet* sommet){
  if( sommet )
    free(sommet);
}
