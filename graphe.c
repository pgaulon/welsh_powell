#include <stdlib.h>
#include "sommet.h"
#include "graphe.h"

struct graphe* new_graphe(int nb_sommets){
  int i;

  struct graphe* new = malloc(sizeof(struct graphe));
  new->nb_couleurs = 0;
  new->nb_sommets = 0;

  new->matrice = malloc(sizeof(int *) * nb_sommets);
  for(i = 0; i < nb_sommets; i++)
    new->matrice[i] = calloc(sizeof(int) * nb_sommets, sizeof(int));

  new->sommets = malloc(sizeof(struct sommet *) * nb_sommets);
  return new;
}

void free_sommets(struct sommet** tab_sommets, int taille){
  int i;
  for(i = 0; i < taille; i++)
      free_sommet(tab_sommets[i]);
  free(tab_sommets);
}

void free_graphe(struct graphe* graphe){
  if( graphe ){
    int i;
    free_sommets(graphe->sommets, graphe->nb_sommets);
    for(i = 0; i < graphe->nb_sommets; i++)
      free(graphe->matrice[i]);
    free(graphe->matrice);
    free(graphe);
  }
}

void add_sommet(struct graphe* graphe, struct sommet* sommet){
  graphe->sommets[graphe->nb_sommets] = sommet;
  graphe->nb_sommets++;
}

struct sommet* find_sommet(struct graphe* graphe, char label){
  int i;
  for(i = 0; i < graphe->nb_sommets; i++){
    if( graphe->sommets[i]->label == label )
      return graphe->sommets[i];
  }
  return NULL;
}

int find_position(struct graphe* graphe, struct sommet* sommet){
  int i;
  for(i = 0; i < graphe->nb_sommets; i++){
    if( graphe->sommets[i]->label == sommet->label )
      return i;
  }
  return -1;
}

void add_voisin(struct graphe* graphe, struct sommet* sommet, struct sommet* voisin){
  int i = find_position(graphe,sommet);
  int j = find_position(graphe,voisin);
  if( (i >= 0) && (j >= 0) ){
    graphe->matrice[i][j] = 1;
    graphe->matrice[j][i] = 1;
  }
}

void calculate_degre(struct graphe* graphe){
  int i, j;
  for(i = 0; i < graphe->nb_sommets; i++){
    for(j = 0; j < graphe->nb_sommets; j++){
      graphe->sommets[i]->degre += graphe->matrice[i][j];
    }
  }
}

int is_adjacent(struct graphe* graphe, struct sommet* a, struct sommet* b){
  int i = find_position(graphe, a);
  int j = find_position(graphe, b);
  return graphe->matrice[i][j];
}

int is_colore(struct graphe* graphe){
  int i;
  for(i = 0; i < graphe->nb_sommets; i++){
    if( graphe->sommets[i]->couleur == 0 )
      return 0;
  }
  return 1;
}

struct sommet** copy_sommets(struct graphe* graphe){
  int i;
  struct sommet** new = malloc(sizeof(struct sommet*) * graphe->nb_sommets);
  for(i = 0; i < graphe->nb_sommets; i++)
    new[i] = graphe->sommets[i];
  return new;
}

void sort_insertion_deg_decr(struct sommet** tab_sommets, int taille){
  int i, j;
  struct sommet* tmp;
  for(i = 1; i < taille; i++){
    tmp = tab_sommets[i];
    j = i;
    while( (j > 0) && (tab_sommets[j-1]->degre < tmp->degre) ){
      tab_sommets[j] = tab_sommets[j-1];
      j--;
    }
    tab_sommets[j] = tmp;
  }
}

int Welsh_Powell(struct graphe* graphe){
  int i, j;
  struct sommet* courant;

  calculate_degre(graphe);
  struct sommet** copy = copy_sommets(graphe);
  sort_insertion_deg_decr(copy, graphe->nb_sommets);

  while( !is_colore(graphe) ){
    j = 0;
    while( (copy[j]->couleur != 0) && (j < graphe->nb_sommets) ){
      j++;
    }
    if( j == graphe->nb_sommets ){
      break;
    }
    graphe->nb_couleurs++;
    courant = copy[j];
    courant->couleur = graphe->nb_couleurs;
    for(i = j + 1; i < graphe->nb_sommets; i++){
      if( !is_adjacent(graphe, courant, copy[i]) )
        copy[i]->couleur = graphe->nb_couleurs;
    }
  }

  free(copy);
  return graphe->nb_couleurs;
}
