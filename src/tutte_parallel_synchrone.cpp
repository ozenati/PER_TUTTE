#include "toolkit.h"

// TUTTE VERSION 2 parallèle
void tutte_2_openmp(vector<MyNode_ver2> * MyNodes_2, 
		    vector<int> * Neighbourhoods, 
		    vector<Vec2f> * coords, 
		    double eps, bool silent) {
  float local_eps = 0, global_eps = 0;
  uint nbIter = 0, i;

  vector<Vec2f> newCoords (*coords);
  uint size = MyNodes_2->size();

  do {
    global_eps = 0;
#pragma omp parallel shared(newCoords, coords, global_eps) private(i, local_eps)
    {
      local_eps = global_eps;
#pragma omp for schedule(static)
      // Pour chaque noeud du graphe
      for(i = 0; i < size; ++i) {
	MyNode_ver2 * current_n = &(* MyNodes_2)[i];
	  
	// On ne considére que les noeuds mobiles
	if (current_n->mobile) {
	  // on sauvegade la position courante
	  float lastX = (* coords)[i][0];
	  float lastY = (* coords)[i][1];
	  
	  // On fait le calcul du barycentre
	  float resX=0, resY=0;
	  int index_neigh = 0;
	  int * p_neigh = &((* Neighbourhoods)[current_n->index_neighbourhood]);
	  int degre = current_n->degre;
	  for(int j = 0; j < degre; ++j, ++p_neigh) {
	    index_neigh = *p_neigh;
	    resX += (* coords)[index_neigh][0];
	    resY += (* coords)[index_neigh][1];
	  }

	  // On sauvegarde les coordonnées calculées dans un nouveau tableau
	  newCoords[i][0] = resX/current_n->degre;
	  newCoords[i][1] = resY/current_n->degre;

	  // On MAJ l'epsilon par rapport à X et Y
	  local_eps = max(local_eps, abs(lastX - newCoords[i][0]));
	  local_eps = max(local_eps, abs(lastY - newCoords[i][1]));
	}
      } // fin du #pragma omp for schedule(static)

#pragma omp critical
      {
	global_eps = std::max(local_eps, global_eps);
      }

    }  // fin de la région parallèle
    
    newCoords.swap(*coords);
    
    nbIter++;
  }  // fin de la boucle sur l'ensemble des itértions
  while (global_eps > eps);
    
  if (!silent) {
    cout << endl;
    cout << "GLOBAL epsilon : " << global_eps << endl;
    cout << "TOTAL itération : " << nbIter << endl;
    cout << endl;
  }
}
