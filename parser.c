#include <stdlib.h>
#include <stdio.h>
#include "sommet.h"
#include "graphe.h"
#include "parser.h"

struct graphe* parse_fichier(char* fichier){
  FILE* file = NULL;
  int read, nb_sommets, i;
  char c, separateur;
  struct sommet* new_s;
  struct sommet* voisin;

  file = fopen(fichier, "r");
  if( file == NULL )
    return NULL;
  /*********First line****************/
  read = fscanf(file, "%d\n", &nb_sommets);
  if( read != 1 )
    return NULL;
  struct graphe* new_g = new_graphe(nb_sommets);
  /**************************************/

  /*********Second line****************/
  for(i = 0; i < nb_sommets-1; i++){
    read = fscanf(file, "%c ", &c);
    if( read != 1 ){
      fclose(file);
      return NULL;
    }
    new_s = new_sommet(c);
    add_sommet(new_g, new_s);
  }
  read = fscanf(file, "%c\n", &c);
  if( read != 1 ){
    fclose(file);
    return NULL;
  }
  new_s = new_sommet(c);
  add_sommet(new_g, new_s);
  /**************************************/

  /*********Rest of the lines****************/
  for(i = 0; i < nb_sommets; i++){
    read = fscanf(file, "%c ", &c);
    if( read != 1 ){
      fclose(file);
      return NULL;
    }
    new_s = find_sommet(new_g, c);

    separateur = ' ';
    while( separateur != '\n' ){
      read = fscanf(file, "%c%c", &c, &separateur);
      if( read != 2 ){
        fclose(file);
        return NULL;
      }
      voisin = find_sommet(new_g, c);
      add_voisin(new_g, new_s, voisin);
      if( separateur == '\n' )
        break;
    }
  }
  /**************************************/

  fclose(file);
  return new_g;
}
