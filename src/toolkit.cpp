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

  // int id_toprint = 1;
  // int i = 0;
  
  // boucle principale : pour tout les noeuds du graphe, faire
  while(itN->hasNext()) {
    node tmp_n = itN->next();
    
    // Si le noeud n'a pas été ajouté au vecteur de MyNodes_ver2
    if (AllNodes.count(tmp_n) == 0) {
      AllNodes[tmp_n] = index_current_node++;

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
      
      MyNodes_2->push_back(N);

      Vec2f v;
      v[0] = c.getX();
      v[1] = c.getY();
      coords->push_back(v);
    }  // fin de if (AllNodes.count(tmp_n) == 0)

    // Si le noeud est déjà connu
    else {
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
	AllNodes[tmp_n2] = index_current_node++;
	
	bool res = !(fixed->getNodeValue(tmp_n2)) && !(bordure->getNodeValue(tmp_n2));
	
	// index_neighbourhood n'est pas mis à jour
	MyNode_ver2 N2;
	N2.n = tmp_n2;
	N2.mobile = res;
	N2.degre = grille->deg(tmp_n2);
	
	MyNodes_2->push_back(N2);
	
	Coord c = layout->getNodeValue(tmp_n2);
	Vec2f v;
	v[0] = c.getX();
	v[1] = c.getY();
	coords->push_back(v);
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

// TUTTE VERSION 1
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

  cout << endl;
  cout << "GLOBAL epsilon : " << current_eps << endl;
  cout << "TOTAL itération : " << nbIter << endl;
  cout << endl;
}

// TUTTE VERSION 2 parallèle : à réparer
void tutte_2_openmpDirty(vector<MyNode_ver2> * MyNodes_2, vector<int> * Neighbourhoods, 
		    vector<Vec2f> * coords, double eps) {
  double current_eps = 0;
  uint nbIter = 0, i;
  // int tid;

  // Pour éviter les mauvais comportements, copier les positions du tour précédent pour faire les calculs
  // du tour actuel : comportement synchrone
  
  vector<Vec2f> newCoords (*coords);
  uint size = MyNodes_2->size();

  do {
    current_eps = 0;
#pragma omp parallel shared(newCoords, coords, current_eps) private(i)
    {
      //tid = omp_get_thread_num();
      // if (tid == 0) {
      //   cout << "tid : " << tid << " nbIter : " << nbIter << " current_eps : " << current_eps << endl; 
      // }
#pragma omp for schedule(static)
      // Pour chaque noeud du graphe
      for(i = 0; i < size; ++i) {
	//cout << "Number of threads = " << omp_get_num_threads() << endl;
	  
	MyNode_ver2 * current_n = &(* MyNodes_2)[i];
	  
	// On ne considére que les noeuds mobiles
	if (current_n->mobile) {

	  float lastX = (* coords)[i][0];
	  float lastY = (* coords)[i][1];
	    
	  float resX=0, resY=0;
	  int index_neigh = 0;
	  int * p_neigh = &((* Neighbourhoods)[current_n->index_neighbourhood]);
	  int degre = current_n->degre;
	  for(int j = 0; j < degre; ++j, ++p_neigh) {
	    index_neigh = *p_neigh;
	    resX += (* coords)[index_neigh][0];
	    resY += (* coords)[index_neigh][1];
	  }
	  
	  // (* coords)[i][0] = resX/current_n->degre;
	  // (* coords)[i][1] = resY/current_n->degre;	  

	  // cout << "resX   : " << resX/current_n->degre 
	  //      << "\nres[0] : " << res[0] 
	  //      << "\n(* coords)[i][0] : " << (* coords)[i][0]
	  //      << endl;

	  newCoords[i][0] = resX/current_n->degre;
	  newCoords[i][1] = resY/current_n->degre;
	    
	  // On MAJ l'epsilon par rapport à X et Y
#pragma omp critical
	  {
	    // current_eps = max(current_eps, abs(lastX - (* coords)[i][0]) );
	    // current_eps = max(current_eps, abs(lastY - (* coords)[i][1]) );
	    current_eps = max(current_eps, abs(lastX - newCoords[i][0]) );
	    current_eps = max(current_eps, abs(lastY - newCoords[i][1]) );
	  }
	}

      } // fin du for(uint i = 0; i < MyNodes->size(); i++)

      newCoords.swap(*coords);
    }
    //#pragma omp atomic
    nbIter++;
  }
  while (current_eps > eps);
    
  cout << endl;
  cout << "GLOBAL epsilon : " << current_eps << endl;
  cout << "TOTAL itération : " << nbIter << endl;
  cout << endl;
}

