#include <cstdio>
#include <iostream>
#include <cmath>
#include <tulip/Graph.h>
#include <tulip/Vector.h>

#include "myNode.h"
#include "tutte.h"

#include <omp.h>

#define max(x, y)   x>y?x:y

// TODO 
// Créer une version asynchrone sur la structure de donnée 2

void tutte_parallel_asynchrone(vector<vector<MyNode *> *> *vectors, double eps, bool silent) { 
  double global_eps = 0;
  uint nbIter = 0;
  vector<vector<MyNode *> *>::iterator it;

  do 
    {
      global_eps = 0;
      //cout << "Iteration " << nbIter << endl;
      // Pour toutes les classes de couleurs de noeuds
      for (it=vectors->begin(); it < vectors->end(); it++)
	{
	  // Selection de l'ensemble courant;
	  vector<MyNode *> *MyNodes = (*it);

#pragma omp parallel
	  {
	    double my_eps = global_eps;
#pragma omp for
	    // Pour chaque noeud de l'ensemble courant
	    for(uint i = 0; i < MyNodes->size(); i++) 
	      {
		MyNode * current_n = (*MyNodes)[i];
		vector<MyNode *> * current_voisin;

		// On ne considére que les noeuds mobiles
		if (current_n->getMobile()) 
		  {
		    // On récupère le voisinage et le position courante en X
		    current_voisin = current_n->getVoisin();
		    float lastX = current_n->getCoord().getX();
		    float lastY = current_n->getCoord().getY();
      
		    // On calcul le barycentre de ce voisinage
		    // On ne considère pas la troisième coordonnée
		    uint degre = current_voisin->size();
		    float resX=0, resY=0;
		    float x, y, z;
		    for(uint j = 0; j < degre; j++) 
		      {
			(*current_voisin)[j]->getCoord().get(x, y, z);
			resX += x;
			resY += y;
		      }
		    // On MAJ les coordonnées du noeud courant
		    current_n->setCoord(Coord(resX/degre, resY/degre, 0));
		    //cout << current_n->getNode().id << " " << current_n->getCoord() << endl;
		    // On MAJ l'epsilon
		    my_eps = max(my_eps, sqrt(pow(lastX - resX/degre,2) + pow(lastY - resY/degre,2)));
		  }
	      } // fin de la boucle sur les noeuds de l'ensemble courant
	    if (my_eps>global_eps) 
	      {
#pragma omp critical
		{
		  if(my_eps>global_eps) global_eps = my_eps;
		}
	      }
	  } // fin du bloc parallel
	} // fin de la boucle sur toutes les classes de couleurs
      nbIter++;
    }
  while (global_eps > eps);


  if (!silent) {
    cout << endl;
    cout << "GLOBAL epsilon : " << global_eps << endl;
    cout << "TOTAL itération : " << nbIter << endl;
    cout << endl;
  }
}

