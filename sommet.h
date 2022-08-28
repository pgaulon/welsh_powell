#ifndef SOMMET_H
#define SOMMET_H

struct sommet{
  int couleur;
  char label;
  int degre;
};

struct sommet* new_sommet(char);
void free_sommet(struct sommet*);

#endif
