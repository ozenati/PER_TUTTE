#include <cstdio>

#include "toolkit.h"

#define max(x, y)   x>y?x:y

// TODO
// Réduire la taille de la section critique : regarder le code de Omar (tutte_asynchrone)

// TUTTE VERSION 2 parallèle : à réparer
void tutte_2_openmp(vector<MyNode_ver2> * MyNodes_2, vector<int> * Neighbourhoods, 
		    vector<Vec2f> * coords, double eps) {
  double current_eps = 0;
  uint nbIter = 0, i;
  // int tid;

  // Pour éviter les mauvais comportements, copier les positions du tour précédent pour faire les calculs
  // du tour actuel : comportement synchrone
  
  vector<Vec2f> newCoords (*coords);
  uint size = MyNodes_2->size();
  float tmp_eps;
  (void)tmp_eps;

  do {
    current_eps = 0;
#pragma omp parallel shared(newCoords, coords, current_eps) private(i)
    {
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
	  
	  newCoords[i][0] = resX/current_n->degre;
	  newCoords[i][1] = resY/current_n->degre;
	    
	  // On MAJ l'epsilon par rapport à X et Y
#pragma omp critical
	  {
	  // tmp_eps = abs(lastX - newCoords[i][0]);
	  // current_eps = max(current_eps, tmp_eps);

	  current_eps = max(current_eps, abs(lastX - newCoords[i][0]));
	  
	  // tmp_eps = abs(lastY - newCoords[i][1]);
	  // current_eps = max(current_eps, tmp_eps);

	  current_eps = max(current_eps, abs(lastY - newCoords[i][1]));
	  }
	}
	
      } // fin du for(uint i = 0; i < MyNodes->size(); i++)
      
      newCoords.swap(*coords);
    }
    
    nbIter++;
  }
  while (current_eps > eps);
    
  cout << endl;
  cout << "GLOBAL epsilon : " << current_eps << endl;
  cout << "TOTAL itération : " << nbIter << endl;
  cout << endl;
}
