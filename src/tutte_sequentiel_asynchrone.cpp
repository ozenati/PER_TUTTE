// #include <iostream>

// #include <sys/time.h>

// #include "myNode.h"
// #include "toolkit.h"
// #include <cstdio>

// #include <omp.h>

#include <stdio.h>

#include "toolkit.h"

#define max(x, y)   ((x)>(y))?(x):(y)

using namespace std;
using namespace tlp;

// TUTTE VERSION 2 : meilleur structure de donnée
void tutte_2(vector<MyNode_ver2> * MyNodes_2, vector<int> * Neighbourhoods, 
	     vector<Vec2f> * coords, double eps) {
  double current_eps = 0;
  uint nbIter = 0, size = MyNodes_2->size();

  // Vec2f null(0);
  // Vec2f res; 

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
	// res = null;
	int index_neigh = 0;
	int * p_neigh = &((* Neighbourhoods)[current_n->index_neighbourhood]);
	int degre = current_n->degre;
	for(int j = 0; j < degre; ++j, ++p_neigh) {
	  index_neigh = *p_neigh;

	  resX += (* coords)[index_neigh][0];
	  resY += (* coords)[index_neigh][1];

	  // res += (* coords)[index_neigh];
	}

	// res /= current_n->degre;
	// (* coords)[i] = res;

	(* coords)[i][0] = resX/current_n->degre;
	(* coords)[i][1] = resY/current_n->degre;

	// On MAJ l'epsilon par rapport à X et Y
	current_eps = max(current_eps, abs(lastX - (* coords)[i][0]) );
	current_eps = max(current_eps, abs(lastY - (* coords)[i][1]) );
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

// TUTTE VERSION 2 BIS : utilisation de Vec2f
void tutte_2_bis(vector<MyNode_ver2> * MyNodes_2, vector<int> * Neighbourhoods, 
	     vector<Vec2f> * coords, double eps) {
  double current_eps = 0;
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
	current_eps = max(current_eps, abs(lastX - (* coords)[i][0]) );
	current_eps = max(current_eps, abs(lastY - (* coords)[i][1]) );
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
