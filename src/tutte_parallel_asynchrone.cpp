#include <stdio.h>
#include <iostream>
#include <cmath>
#include <tulip/Graph.h>
#include <tulip/Vector.h>
#include "MyNode.h"
#include "tutte.h"

#include "omp.h"

#define max(x, y)   x>y?x:y

void tutte_parallel_asynchrone(vector<vector<MyNode *> *> *vectors, double eps) { 
  double current_eps = 0;
  uint nbIter = 0;

  do {
    current_eps = 0;
    vector<MyNode *> * current_voisin;
    cout << "Iteration " << nbIter << endl;
    // Pour tout ensemble de noeuds
    vector<vector<MyNode *> *>::iterator it;
    for (it=vectors->begin(); it < vectors->end(); it++)
      {
	// Selection de l'ensemble courant;
	vector<MyNode *> *MyNodes = (*it);
	// Faire en parallele
	// Pour chaque noeud de l'ensemble courant
#pragma omp parallel for reduction(max,current_eps)
	for(uint i = 0; i < MyNodes->size(); i++) {
	  MyNode * current_n = (*MyNodes)[i];

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
	    cout << current_n->getNode().id << " " << current_n->getCoord() << endl;
	    // On MAJ l'epsilon
	    current_eps = max(current_eps, sqrt(pow(lastX - resX/degre,2) + pow(lastY - resY/degre,2)));
	  }
	} // fin de la boucle sur les noeuds de l'ensemble courant

      } // fin de la boucle sur les ensembles
    nbIter++;
    // cout << "nbIter : " << nbIter << endl;
    // cout << "epsilon courant : " << current_eps << endl;
  }
  while (current_eps > eps);

  cout << "GLOBAL epsilon : " << current_eps << endl;
  cout << "TOTAL itération : " << nbIter << endl;
  cout << endl;
}

