#include <iostream>

#include <sys/time.h>

#include "mynode/MyNode.h"
#include "toolkit.h"

using namespace std;
using namespace tlp;

typedef struct my_node_ {
  node n;
  Coord coord;  
  vector<struct my_node_> v_voisin;
} my_node;

int main(int argc, char * argv[])  {
  if (argc != 3) {
    cout << "Usage : "<< argv[0] << " <graphe_file_in> <graphe_filename_out>" << endl;
    exit(1);
  }

  // Permet d'utiliser loadGraph méthode
  tlp::initTulipLib();

  // Lecture d'un graphe d'entré
  tlp::Graph* graph = tlp::loadGraph(argv[1]);

  // Récupérer la grille sur laquelle il faut appliquer l'algo de Tutte
  tlp::Graph *grille = graph->getSubGraph(2);

  // On récupére les noeuds de la grille dans notre structre de noeud
  vector<MyNode> * MyNodes = convertGraph2Vector(grille);

  struct timeval timeBegin, timeEnd;
  gettimeofday(&timeBegin, NULL);

  // On applique tutte sur notre structure de noeud
  tutte(MyNodes, 1e-6);

  gettimeofday(&timeEnd, NULL);
  double res = timeEnd.tv_sec - timeBegin.tv_sec + (double)(timeEnd.tv_usec - timeBegin.tv_usec)/1e6;

  cout << "temps d'exécution de Tutte : " << res << " s" << endl; 

  // On récupére les déplacement dans notre grille
  convertVector2Graph(MyNodes, grille);
  
  // On sauvegarde le graphe complet avec la grille modifiée
  tlp::saveGraph(graph, argv[2]);

  // Libération des ressources enjeux
  delete MyNodes;
  delete graph;

  return 0;
}
