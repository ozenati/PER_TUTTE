#include <iostream>

#include <sys/time.h>

#include "toolkit.h"

using namespace std;
using namespace tlp;


int main(int argc, char * argv[])  {
  if (argc != 3) {
    cout << "Usage : "<< argv[0] << " <graphe_file_in> <graphe_filename_out>" << endl;
    exit(1);
  }
  
  // Permet d'utiliser loadGraph méthode
  tlp::initTulipLib();

  // Lecture d'un graphe d'entré
  
  tlp::Graph* graph = tlp::loadGraph(argv[1]);

  struct timeval timeBegin, timeEnd;
  //gettimeofday(&timeBegin, NULL);

  // Récupérer la grille sur laquelle il faut appliquer l'algo de Tutte
  tlp::Graph *grille = graph->getSubGraph(2);
 
  // On récupére les noeuds de la grille dans notre structre de noeud
  MyGraph my_g;
  convertGraph2MyGraph(grille, &my_g);

  gettimeofday(&timeBegin, NULL);

  // On applique tutte sur notre structure de noeud
  tutte(&my_g, 1e-6);

  gettimeofday(&timeEnd, NULL);

  // On récupére les déplacement dans notre grille
  updateGraphByMyGraph(&my_g, grille);

  //  gettimeofday(&timeEnd, NULL);

  double res = timeEnd.tv_sec - timeBegin.tv_sec + (double)(timeEnd.tv_usec - timeBegin.tv_usec)/1e6;  

  cout << "temps d'exécution de Tutte : " << res << " s" << endl; 

  // On sauvegarde le graphe complet avec la grille modifiée
  tlp::saveGraph(graph, argv[2]);

  // Libération des ressources enjeux
  delete graph;

  return 0;
}
