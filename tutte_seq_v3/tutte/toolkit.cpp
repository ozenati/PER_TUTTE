#include <cstdio>
#include <cstdlib>

#include "toolkit.h"

#define max(x, y)   ((x)>(y))?(x):(y)
//#define abs(x) ((x)>0)?(x):(-(x))
void convertGraph2MyGraph(Graph * grille, MyGraph * my_graph) {
  Graph * graph = grille->getSuperGraph();

  // On récupére la propriété pour les coordonnées (layout) et pour fixer les noeuds
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");

  BooleanProperty * fixed=graph->getProperty<BooleanProperty>("fixed nodes");
  BooleanProperty * bordure=graph->getProperty<BooleanProperty>("viewSelection");

  // Récupérer tous les noeuds du graph dans une map de MyNode
  map<node, int> AllNodes;
  Iterator<node> *itN = graph->getNodes();
  int i = 0;
  while(itN->hasNext()) {
    Data d;
    d.n = itN->next();
    AllNodes[d.n] = i;
    d.coord = layout->getNodeValue(d.n);
    d.mobile = (fixed->getNodeValue(d.n)) || (bordure->getNodeValue(d.n));
    (*my_graph).datas.push_back(d);
    i++;
  } delete itN;

// Récupérer le voisinage de chaque noeud de la map
  for (unsigned int i = 0; i < (*my_graph).datas.size(); i++) {
    Iterator<node> *itN=graph->getInOutNodes((*my_graph).datas[i].n);
    vector<int>* voisin = new vector<int>;
    while(itN->hasNext()) {
      int id = AllNodes[itN->next()];
      voisin->push_back(id);
    } delete itN;
    (*my_graph).matrix.push_back(voisin);
  }
}

// On MAJ les coordonnées de chaque noeud de la grille de départ
void updateGraphByMyGraph(MyGraph * my_g, Graph * grille){
  Graph * graph = grille->getSuperGraph();
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");
  
  for(uint i = 0; i < (*my_g).datas.size(); i++) {
    layout->setNodeValue((*my_g).datas[i].n, (*my_g).datas[i].coord);
  }
}

void tutte(MyGraph *my_g, double eps){
  double current_eps = 0;
  uint nbIter = 0;

  do {
    current_eps = 0;

    // Pour chaque noeud du graphe 
    uint size = (*my_g).matrix.size(); 
    for(uint i = 0; i < size; ++i) {
      // On ne considére que les noeuds mobiles
      if ((*my_g).datas[i].mobile) {
	// On récupère le voisinage et le position courante en X
	float lastX = (*my_g).datas[i].coord.getX();
	float lastY = (*my_g).datas[i].coord.getY();
      
	// On calcul le barycentre de ce voisinage
	// On ne considère pas la troisième coordonnée
	uint degre = (*((*my_g).matrix)[i]).size();
	float resX=0, resY=0;
	float x, y, z;
	for(uint j = 0; j < degre; j++) {
	  (*my_g).datas[(*(my_g->matrix[i]))[j]].coord.get(x, y, z);
	  resX += x;
	  resY += y;
	}
	// On MAJ les coordonnées du noeud courant
	x = resX/degre;
	y = resY/degre;
	(*my_g).datas[i].coord = Coord(x, y, 0);

	// On MAJ l'epsilon
	x = abs(lastX - x);
	y = abs(lastY - y);
	current_eps = max (current_eps, max(x,y));
      }
    } // fin du for(uint i = 0; i < MyNodes->size(); i++)
    nbIter++;
  }
  while (eps < current_eps);

  cout << "GLOBAL epsilon : " << current_eps << endl;
  cout << "TOTAL itération : " << nbIter << endl;
  cout << endl;
}
