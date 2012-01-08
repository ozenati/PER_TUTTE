#include <iostream>

#include <sys/time.h>

#include "MyNode.h"
#include "toolkit.h"
#include <cstdio>

using namespace std;
using namespace tlp;

void tutte_seq(Graph * graph, Graph * grille, char * filename_out) {
  // On récupére les noeuds de la grille dans notre structure de noeud
  vector<MyNode> * MyNodes = convertGraph2Vector(grille);

  struct timeval timeBegin, timeEnd;
  gettimeofday(&timeBegin, NULL);

  // On applique tutte sur notre structure de noeud
  tutte(MyNodes, 1e-6);

  // On récupére les déplacement dans notre grille
  convertVector2Graph(MyNodes, grille);
  
  gettimeofday(&timeEnd, NULL);
  double res = timeEnd.tv_sec - timeBegin.tv_sec + (double)(timeEnd.tv_usec - timeBegin.tv_usec)/1e6;

  cout << "temps d'exécution de Tutte : " << res << " s" << endl; 

  // On sauvegarde le graphe complet avec la grille modifiée
  tlp::saveGraph(graph, filename_out);

  // Libération des ressources enjeux
  delete MyNodes;
}

void tutte_seq_2(Graph * graph, Graph * grille, char * filename_out) {
  (void)graph;
  (void)filename_out;
  
  vector<MyNode_ver2> MyNodes_2;   // contient l'ensemble des noeuds
  vector<int> Neighbourhoods;           // contient l'indice de tous les noeuds du voisinage de chaque noeud
  vector<Vec2f> coords;                      // contient les coordonnées de chaque noeud

  // On récupére les noeuds de la grille dans nos vecteur
  convertGraph2Vector_ver2(grille, &MyNodes_2, &Neighbourhoods, &coords);

  struct timeval timeBegin, timeEnd;
  gettimeofday(&timeBegin, NULL);

  // On applique tutte sur notre structure de noeud
  tutte_2(&MyNodes_2, &Neighbourhoods, &coords, 1e-6);

  // On récupére les déplacement dans notre grille
  convertVector_ver2_2Graph(&MyNodes_2, &coords, grille);

  gettimeofday(&timeEnd, NULL);
  double res = timeEnd.tv_sec - timeBegin.tv_sec + (double)(timeEnd.tv_usec - timeBegin.tv_usec)/1e6;

  cout << "temps d'exécution de Tutte : " << res << " s" << endl; 

 // On sauvegarde le graphe complet avec la grille modifiée
  tlp::saveGraph(graph, filename_out);
}

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

  //tutte_seq(graph, grille, argv[2]);
  tutte_seq_2(graph, grille, argv[2]);
  
  delete graph;

  return 0;
}
