#include <stdio.h>

#include "toolkit.h"

#define max(x, y)   x>y?x:y

vector<MyNode> * convertGraph2Vector(Graph * grille) {
  Graph * graph = grille->getSuperGraph();
  // On récupére la propriété pour les coordonnées (layout) et pour fixer les noeuds
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");
  BooleanProperty * fixed=graph->getProperty<BooleanProperty>("fixed nodes");
  BooleanProperty * bordure=graph->getProperty<BooleanProperty>("viewSelection");

  // Récupérer tous les noeuds du graph dans une map de MyNode
  map<node, int, nidCompare> AllNodes;
  vector<MyNode> * MyNodes= new vector<MyNode>;
  
  Iterator<node> *itN = grille->getNodes();
  int i = 0;
  while(itN->hasNext()) {
    node tmp_n = itN->next();
    AllNodes[tmp_n] = i;

    // On construit chaque élément du vecteur
    // Seul le voisinage n'est pas encore construit
    Coord c = layout->getNodeValue(tmp_n);
    // Un noeud est mobile s'il n'est pas fixe et s'il n'appartient pas à la bordure
    bool res = !(fixed->getNodeValue(tmp_n)) && !(bordure->getNodeValue(tmp_n));
    MyNode n(tmp_n, res, c); 
    
    MyNodes->push_back(n);
    i++;
  } delete itN;

  Iterator <edge> *itE = grille->getEdges();
  while (itE->hasNext()) {
    edge current_edge = itE->next();
    if (bordure->getEdgeValue(current_edge)) {
      pair<node, node> nodes = grille->ends(current_edge);

      int key = AllNodes[nodes.first];
      (* MyNodes)[key].setMobile(false);
	
      key = AllNodes[nodes.second];
      (* MyNodes)[key].setMobile(false);
    }
  }delete itE;

  // Récupérer le voisinage de chaque noeud de la map
  for (unsigned int i = 0; i < MyNodes->size(); i++) {
    Iterator<node> *itN=grille->getInOutNodes((* MyNodes)[i].getNode());
    while(itN->hasNext()) {
      // La map AllNodes sert uniquement à récupérer l'emplacement d'un noeud dans le vecteur MyNodes
      int key = AllNodes[itN->next()];      
      (* MyNodes)[i].getVoisin()->push_back(&(* MyNodes)[key]);
    } delete itN;
  }

  return MyNodes;
}

// On MAJ les coordonnées de chaque noeud de la grille de départ
void convertVector2Graph(vector<MyNode> * MyNodes, Graph * grille) {
  Graph * graph = grille->getSuperGraph();
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");
  
  for(uint i = 0; i < MyNodes->size(); i++) {
    layout->setNodeValue((* MyNodes)[i].getNode(), (* MyNodes)[i].getCoord());
  }
}

void tutte(vector<MyNode> * MyNodes, double eps) { 
  double current_eps = 0;
  uint nbIter = 0;

  do {
    current_eps = 0;
    vector<MyNode *> * current_voisin;
   
    // Pour chaque noeud du graphe
    for(uint i = 0; i < MyNodes->size(); i++) {
      MyNode * current_n = &(* MyNodes)[i];

      // On ne considére que les noeuds mobiles
      if (current_n->getMobile()) {

	// On récupère le voisinage et le position courante en X
	current_voisin = current_n->getVoisin();
	float lastX = current_n->getCoord().getX();
	float lastY = current_n->getCoord().getY();
      
	// On calcul le barycentre de ce voisinage
	// On ne considère pas la troisième coordonnée
	uint degre = current_voisin->size();
	float resX=0, resY=0;
	float x, y, z;
	for(uint j = 0; j < degre; j++) {
	  (*current_voisin)[j]->getCoord().get(x, y, z);
	  resX += x;
	  resY += y;
	}
	// On MAJ les coordonnées du noeud courant
	current_n->setCoord(Coord(resX/degre, resY/degre, 0));
	
	// On MAJ l'epsilon
	current_eps = max(current_eps, sqrt((lastX - resX/degre)*(lastX - resX/degre) 
					    + (lastY - resY/degre)*(lastY - resY/degre)));
      }
    } // fin du for(uint i = 0; i < MyNodes->size(); i++)

    nbIter++;
    // cout << "nbIter : " << nbIter << endl;
    // cout << "epsilon courant : " << current_eps << endl;
  }
  while (current_eps > eps);

  cout << "GLOBAL epsilon : " << current_eps << endl;
  cout << "TOTAL itération : " << nbIter << endl;
  cout << endl;
}
