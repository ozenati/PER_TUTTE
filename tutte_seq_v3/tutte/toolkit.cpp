#include <cstdio>
#include <cstdlib>

#include "toolkit.h"

#define max(x, y)   ((x)>(y))?(x):(y)
//#define abs(x) ((x)>0)?(x):(-(x))
void convertGraph2MyGraph(Graph * grille, MyGraph * my_graph) {
  Graph * graph = grille->getSuperGraph();

  // On récupére la propriété pour les coordonnées (layout) et pour fixer les noeuds
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");
<<<<<<< HEAD
  BooleanProperty * fixed=graph->getProperty<BooleanProperty>("fixed nodes");
  BooleanProperty * bordure=graph->getProperty<BooleanProperty>("viewSelection");
=======
 BooleanProperty * fixed=graph->getProperty<BooleanProperty>("fixed nodes");
 BooleanProperty * bordure=graph->getProperty<BooleanProperty>("viewSelection");
>>>>>>> c1ac84856b5b3264b6a795fb65c98f2e613e40cf

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
    vector<vector<int >*> * matrix = &((*my_g).matrix); 
    uint size = matrix->size();
    vector<Data> datas = (*my_g).datas; 
    cout << "ok ici! do" << endl;
    for(uint i = 0; i < size; i++) {
      Data * current_d = &datas[i];
      vector<int> * voisins;
      // On ne considére que les noeuds mobiles
      if (current_d->mobile) {
	// On récupère le voisinage et le position courante en X
	voisins = ((*matrix)[i]);
	float lastX = current_d->coord.getX();
	float lastY = current_d->coord.getY();
      
	// On calcul le barycentre de ce voisinage
	// On ne considère pas la troisième coordonnée
	uint degre = (*voisins).size();
	float resX=0, resY=0;
	float x, y, z;
	for(uint j = 0; j < degre; j++) {
	  datas[(*voisins)[j]].coord.get(x, y, z);
	  resX += x;
	  resY += y;
	}
	cout << "ok ici yep ! " << size  << endl;
	// On MAJ les coordonnées du noeud courant
	x = resX/degre;
	y = resY/degre;
	current_d->coord = Coord(x, y, 0);
	
	// On MAJ l'epsilon
	x = abs(lastX - x);
	y = abs(lastY - y);
	current_eps = max (current_eps, max(x,y));
      }
    } // fin du for(uint i = 0; i < MyNodes->size(); i++)
    cout << eps << "\t" << current_eps << endl;
    nbIter++;
  }
  while (eps < current_eps);

  cout << "GLOBAL epsilon : " << current_eps << endl;
  cout << "TOTAL itération : " << nbIter << endl;
  cout << endl;
}
