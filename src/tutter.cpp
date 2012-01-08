#include <iostream>
#include <tulip/Graph.h>
#include <tulip/GlyphManager.h>
#include <tulip/LayoutProperty.h>

#include <sys/time.h>

#include "MyNode.h"
#include "separator.h"
#include <tutte.h>

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

  // Récupérer la grille sur laquelle il faut appliquer l'algo de Tutte
  //tlp::Graph *grille = graph->getSubGraph(2);

  // On récupére les noeuds de la grille dans notre structre de noeud
  //  vector<MyNode> * MyNodes = convertGraph2Vector(graph);

  map<int, MyNode *> *all_nodes = convertGraph2Map(graph);

  vector<vector<MyNode *> *> *vectors = separateMap2Vectors(all_nodes);

  int i;
  vector<vector<MyNode *> *>::iterator it;
  for (it=vectors->begin(), i = 0 ; it < vectors->end(); it++, i++)
    {
      cout << "Ensemble " << i << " contient:" << endl;
      cout << "{";
      vector<MyNode *>::iterator it2 = (*it)->begin();
      for (it2=(*it)->begin(); it2 < (*it)->end(); it2++)
	{
	  MyNode *n = *it2;
	  cout << n->getNode().id << " ";
	}
      cout << "}" << endl; 
    }

  struct timeval timeBegin, timeEnd;
  gettimeofday(&timeBegin, NULL);

  // On applique tutte sur notre structure de noeud
  //  tutte(MyNodes, 1e-6);
  tutte_parallel_asynchrone(vectors, 1e-6);
  gettimeofday(&timeEnd, NULL);
  double res = timeEnd.tv_sec - timeBegin.tv_sec + (double)(timeEnd.tv_usec - timeBegin.tv_usec)/1e6;

  cout << "temps d'exécution de Tutte : " << res << " s" << endl; 

  // On récupére les déplacement dans notre grille
  //convertVector2Graph(MyNodes, graph);
  applyVectors2Graph(vectors, graph);

  // On sauvegarde le graphe complet avec la grille modifiée
  tlp::saveGraph(graph, argv[2]);

  // Libération des ressources enjeux
  delete vectors;
  delete all_nodes;
  delete graph;

  return 0;
}
