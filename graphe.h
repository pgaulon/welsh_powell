#ifndef GRAPHE_H
#define GRAPHE_H

#include "sommet.h"

struct graphe{
  int nb_couleurs;
  int nb_sommets;
  int** matrice;
  struct sommet** sommets;
};

struct graphe* new_graphe(int);
void free_sommets(struct sommet**, int);
void free_graphe(struct graphe*);
void add_sommet(struct graphe*, struct sommet*);
struct sommet* find_sommet(struct graphe*, char);
int find_position(struct graphe*, struct sommet*);
void add_voisin(struct graphe*, struct sommet*, struct sommet*);
void calculate_degre(struct graphe*);
int is_adjacent(struct graphe*, struct sommet*, struct sommet*);
int is_colore(struct graphe*);
struct sommet** copy_sommets(struct graphe*);
void sort_insertion_deg_decr(struct sommet**, int);
int Welsh_Powell(struct graphe*);

#endif
