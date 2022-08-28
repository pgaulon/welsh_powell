#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "sommet.h"
#include "graphe.h"
#include "parser.h"

int main(int argc, char* argv[]){
  if( argc != 2 )
    printf("Usage : %s <file_name>.\n", argv[0]);
  else{
    int coloration;
    if( access(argv[1], F_OK) != 0 ){
      printf("No such file\n");
      return -1;
    }
    struct graphe* new_graphe = parse_fichier(argv[1]);
    coloration = Welsh_Powell(new_graphe);
    free_graphe(new_graphe);
    printf("%d colors needed.\n", coloration);
  }
  return EXIT_SUCCESS;
}
