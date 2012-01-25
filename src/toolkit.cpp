#include <cstdio>

#include "toolkit.h"

#define max(x, y)   (x)>(y)?(x):(y)

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

void convertGraph2Vector_ver2(Graph * grille, vector<MyNode_ver2> * MyNodes_2, 
			      vector<int> * Neighbourhoods, vector<Vec2f> * coords) {
  Graph * graph = grille->getSuperGraph();
  // On récupére la propriété pour les coordonnées (layout) et pour fixer les noeuds
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");
  BooleanProperty * fixed=graph->getProperty<BooleanProperty>("fixed nodes");
  BooleanProperty * bordure=graph->getProperty<BooleanProperty>("viewSelection");

  // Récupérer tous les noeuds du graph dans une map de MyNode
  map<node, int, nidCompare> AllNodes;
  
  Iterator<node> *itN = grille->getNodes();
  int index_current_node = 0;
  int index_neigh = 0;
    
  // boucle principale : pour tout les noeuds du graphe, faire
  while(itN->hasNext()) {
    node tmp_n = itN->next();
    
    // Si le noeud n'a pas été ajouté au vecteur de MyNodes_ver2
    if (AllNodes.count(tmp_n) == 0) {
      AllNodes[tmp_n] = index_current_node;

      // On construit chaque élément du vecteur
      // Seul le voisinage n'est pas encore construit
      Coord c = layout->getNodeValue(tmp_n);
      // Un noeud est mobile s'il n'est pas fixe et s'il n'appartient pas à la bordure
      bool res = !(fixed->getNodeValue(tmp_n)) && !(bordure->getNodeValue(tmp_n));

      MyNode_ver2 N;
      N.n = tmp_n;
      N.mobile = res;
      N.index_neighbourhood = index_neigh;
      N.degre = grille->deg(tmp_n);
      
      // MAJ index_neigh
      index_neigh += N.degre;
      
      (* MyNodes_2)[index_current_node] = N;

      Vec2f v;
      v[0] = c.getX();
      v[1] = c.getY();
      (* coords)[index_current_node] = v;

      index_current_node++;
    }  // fin de if (AllNodes.count(tmp_n) == 0)

    // Si le noeud est déjà connu
    else {
      // MAJ de l'index voisinage du noeud déjà dans la map
      MyNode_ver2 * N = &(* MyNodes_2)[AllNodes[tmp_n]];
      N->index_neighbourhood = index_neigh;
      
      // MAJ index_neigh
      index_neigh += N->degre;
    }

    // Pour chaque noeud du voisinage
    Iterator<node> *itN2=grille->getInOutNodes(tmp_n);
    while(itN2->hasNext()) {
      node tmp_n2 = itN2->next();

      // Si le noeud n'a pas été ajouté
      if (AllNodes.count(tmp_n2) == 0) {
	AllNodes[tmp_n2] = index_current_node;
		
	bool res = !(fixed->getNodeValue(tmp_n2)) && !(bordure->getNodeValue(tmp_n2));
	
	// index_neighbourhood n'est pas mis à jour
	MyNode_ver2 N2;
	N2.n = tmp_n2;
	N2.mobile = res;
	N2.degre = grille->deg(tmp_n2);
	
	//MyNodes_2->push_back(N2);
	(* MyNodes_2)[index_current_node] = N2;
	
	Coord c = layout->getNodeValue(tmp_n2);
	Vec2f v;
	v[0] = c.getX();
	v[1] = c.getY();
	(* coords)[index_current_node] = v;

	index_current_node++;
      } // fin du if (AllNodes.count(tmp_n) == 0)

      // On l'ajout dans le voisinage du noeud d'avant
      Neighbourhoods->push_back(AllNodes[tmp_n2]);
      
    } delete itN2; // fin de la boucle sur le voisinage

    // if (i < 2) {
    //   cout << "tmp_n.id : " << tmp_n.id << endl;
    //   cout << "neighbourhood->size() : " << Neighbourhoods->size() << endl;
    //   cout << "MyNodes_2->size() : " << MyNodes_2->size() << endl;
    //   cout << endl;
    //   cout   << "id : " << AllNodes[tmp_n]
    // 	     << " id_reel : " << tmp_n
    // 	     << "  <" << (* coords)[AllNodes[tmp_n]][0] << ", " << (* coords)[AllNodes[tmp_n]][1] << ">" << endl;
    // }
    
    // i++;
  } delete itN; // fin de la boucle principale
  
  //cout << "coords->size() : " << coords->size() << endl;

  // FAIRE UNE BOUCLE SUR LES ARÊTES POUR DETECTER LES ARÊTES FIXES ET METTRE A JOUR LA MOBILITE DES NOEUDS
  Iterator <edge> *itE = grille->getEdges();
  while (itE->hasNext()) {
    edge current_edge = itE->next();
    if (bordure->getEdgeValue(current_edge)) {
      pair<node, node> nodes = grille->ends(current_edge);

      int key = AllNodes[nodes.first];
      (* MyNodes_2)[key].mobile = false;
	
      key = AllNodes[nodes.second];
      (* MyNodes_2)[key].mobile = false;
    }
  }delete itE;

  // On regarde le voisinage du troisième noeud
//   cout << "id_print : " << id_toprint << endl;
//   cout << "id_reel : " << (* MyNodes_2)[id_toprint].n.id << endl;
//   cout << "degre : " << (* MyNodes_2)[id_toprint].degre << endl;
//   cout << "index_neighbourhood : " << (* MyNodes_2)[id_toprint].index_neighbourhood << endl;
//   for(int i = 0; i < (* MyNodes_2)[id_toprint].degre; i++) {
//     cout << (* MyNodes_2)[(* Neighbourhoods)[(* MyNodes_2)[id_toprint].index_neighbourhood + i]].n.id << ", ";
//     //cout << (* Neighbourhoods)[(* MyNodes_2)[id_toprint].index_neighbourhood + i] << ", ";
//   }
//   cout << endl;
}

// On MAJ les coordonnées de chaque noeud de la grille de départ
void convertVector2Graph(vector<MyNode> * MyNodes, Graph * grille) {
  Graph * graph = grille->getSuperGraph();
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");
  
  for(uint i = 0; i < MyNodes->size(); i++) {
    layout->setNodeValue((* MyNodes)[i].getNode(), (* MyNodes)[i].getCoord());
  }
}

void convertVector_ver2_2Graph(vector<MyNode_ver2> * MyNodes_2, vector<Vec2f> * coords, 
			       Graph * grille) {
  Graph * graph = grille->getSuperGraph();
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");
  
  for(uint i = 0; i < MyNodes_2->size(); i++) {
    layout->setNodeValue((* MyNodes_2)[i].n, Coord((* coords)[i][0], (* coords)[i][1], 0));
  }
}


/*
 * toolkit part for tutte on V3 of our structure
 */

void convertGraph_v3(Graph * grille, vector<Data>* datas, vector<vector<int> >* matrix) {
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
    datas->push_back(d);
    i++;
  } delete itN;

// Récupérer le voisinage de chaque noeud de la map
  uint size = datas->size();
  for (unsigned int i = 0; i < size; i++) {
    Iterator<node> *itN=graph->getInOutNodes(((*datas)[i]).n);
    while(itN->hasNext()) {
      int id = AllNodes[itN->next()];
      (*matrix)[i].push_back(id);
    } delete itN;
  }
}
// On MAJ les coordonnées de chaque noeud de la grille de départ
void updateGraph_v3(Graph * grille, vector<Data>* datas){
  Graph * graph = grille->getSuperGraph();
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");
  uint size = datas->size();
  for(uint i = 0; i < size; i++) {
    layout->setNodeValue(((*datas)[i]).n, ((*datas)[i]).coord);
  }
}
