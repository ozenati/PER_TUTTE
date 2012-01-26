#include <stdio.h>

#include "toolkit.h"

using namespace std;
using namespace tlp;

// TUTTE VERSION 1
void tutte(vector<MyNode> * MyNodes, double eps, bool silent) { 
  float current_eps = 0;
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
	resX /= degre;
	resY /= degre;
	current_n->setCoord(Coord(resX, resY, 0));
	
	// On MAJ l'epsilon
	current_eps = std::max(current_eps, abs(lastX - resX));
	current_eps = std::max(current_eps, abs(lastY - resY));
      }
    } // fin du for(uint i = 0; i < MyNodes->size(); i++)

    nbIter++;
  }
  while (current_eps > eps);

  if (!silent) {
    cout << endl;
    cout << "GLOBAL epsilon : " << current_eps << endl;
    cout << "TOTAL itération : " << nbIter << endl;
    cout << endl;
  }
}

// TUTTE VERSION 2 : meilleur structure de donnée
void tutte_2(vector<MyNode_ver2> * MyNodes_2, vector<int> * Neighbourhoods, 
	     vector<Vec2f> * coords, double eps, bool silent) {
  float current_eps = 0;
  uint nbIter = 0, size = MyNodes_2->size();

  do {
    current_eps = 0;
   
    // Pour chaque noeud du graphe
    for(uint i = 0; i < size; ++i) {

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

	(* coords)[i][0] = resX/current_n->degre;
	(* coords)[i][1] = resY/current_n->degre;

	// On MAJ l'epsilon par rapport à X et Y
	current_eps = std::max(current_eps, abs(lastX - (* coords)[i][0]) );
	current_eps = std::max(current_eps, abs(lastY - (* coords)[i][1]) );
      }
    } // fin du for(uint i = 0; i < MyNodes->size(); i++)

    nbIter++;
  }
  while (current_eps > eps);

  if (!silent) {
    cout << endl;
    cout << "GLOBAL epsilon : " << current_eps << endl;
    cout << "TOTAL itération : " << nbIter << endl;
    cout << endl;
  }
}

// TUTTE VERSION 2 BIS : utilisation de Vec2f
void tutte_2_bis(vector<MyNode_ver2> * MyNodes_2, vector<int> * Neighbourhoods, 
		 vector<Vec2f> * coords, double eps, bool silent) {
  float current_eps = 0;
  uint nbIter = 0, size = MyNodes_2->size();

  Vec2f null(0);
  Vec2f res; 

  do {
    current_eps = 0;
   
    // Pour chaque noeud du graphe
    for(uint i = 0; i < size; ++i) {

      MyNode_ver2 * current_n = &(* MyNodes_2)[i];

      // On ne considére que les noeuds mobiles
      if (current_n->mobile) {

	float lastX = (* coords)[i][0];
	float lastY = (* coords)[i][1];

	res = null;
	int index_neigh = 0;
	int * p_neigh = &((* Neighbourhoods)[current_n->index_neighbourhood]);
	int degre = current_n->degre;
	for(int j = 0; j < degre; ++j, ++p_neigh) {
	  index_neigh = *p_neigh;
	  res += (* coords)[index_neigh];
	}

	res /= current_n->degre;
	(* coords)[i] = res;

	// On MAJ l'epsilon par rapport à X et Y
	current_eps = std::max(current_eps, abs(lastX - (* coords)[i][0]) );
	current_eps = std::max(current_eps, abs(lastY - (* coords)[i][1]) );
      }
    } // fin du for(uint i = 0; i < MyNodes->size(); i++)

    nbIter++;
  }
  while (current_eps > eps);

  if (!silent) {
    cout << endl;
    cout << "GLOBAL epsilon : " << current_eps << endl;
    cout << "TOTAL itération : " << nbIter << endl;
    cout << endl;
  }
}

void tutte_seq_3(vector<Data>* datas, vector<vector<int> >* matrix, double eps, bool silent){
  float current_eps = 0;
  uint nbIter = 0;
  uint size = datas->size(); 

  do {
    current_eps = 0;

    // Pour chaque noeud du graphe 
    for(uint i = 0; i < size; ++i) {
      // On ne considére que les noeuds mobiles
      if (((*datas)[i]).mobile) {
	// On récupère le voisinage et le position courante en X
	float lastX = ((*datas)[i]).coord.getX();
	float lastY = ((*datas)[i]).coord.getY();
      
	// On calcul le barycentre de ce voisinage
	// On ne considère pas la troisième coordonnée
	uint degre = ((*matrix)[i]).size();
	float resX=0, resY=0;
	float x, y, z;
	for(uint j = 0; j < degre; j++) {
	  ((*datas)[(*matrix)[i][j]]).coord.get(x, y, z);
	  resX += x;
	  resY += y;
	}
	// On MAJ les coordonnées du noeud courant
	x = resX/degre;
	y = resY/degre;
	((*datas)[i]).coord = Coord(x, y, 0);

	// On MAJ l'epsilon
	x = abs(lastX - x);
	y = abs(lastY - y);
	current_eps = std::max (current_eps, std::max(x,y));
      }
    } // fin du for(uint i = 0; i < MyNodes->size(); i++)
    nbIter++;
  }
  while (eps < current_eps);

  if (!silent) {
    cout << endl;
    cout << "GLOBAL epsilon : " << current_eps << endl;
    cout << "TOTAL itération : " << nbIter << endl;
    cout << endl;
  }
}
