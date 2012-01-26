#include <iostream>

#include <sys/time.h>

#include "myNode.h"
#include "toolkit.h"
#include "tutte.h"

#include <omp.h>

using namespace std;
using namespace tlp;

void tutte_seq(Graph * graph, Graph * grille, int nb_exec) {
  (void)graph;
  (void)nb_exec;
  // On récupére les noeuds de la grille dans notre structure de noeud
  vector<MyNode> * MyNodes = convertGraph2Vector(grille);
  vector<MyNode> save(*MyNodes);

  double t0 = omp_get_wtime();

  for (int i = 0; i < nb_exec; ++i) {
    // On applique tutte sur notre structure de noeud
    tutte(MyNodes, 1e-6, true);
    *MyNodes = save;
  }

  double t1 = omp_get_wtime();
  double res = (t1 - t0)/nb_exec;

  // On récupére les déplacement dans notre grille
  convertVector2Graph(MyNodes, grille);

  cout << "temps d'exécution de Tutte : " << res << " s" << endl; 

  // Libération des ressources enjeux
  delete MyNodes;
}

void tutte_seq_2(Graph * graph, Graph * grille) {
  (void)graph;
  
  vector<MyNode_ver2> MyNodes_2 (grille->numberOfNodes());   // contient l'ensemble des noeuds
  vector<int> Neighbourhoods;           // contient l'indice de tous les noeuds du voisinage de chaque noeud
  vector<Vec2f> * coords = new vector<Vec2f>(grille->numberOfNodes());                      // contient les coordonnées de chaque noeud

  struct timeval timeBegin, timeEnd;
  gettimeofday(&timeBegin, NULL);

  // On récupére les noeuds de la grille dans nos vecteur
  convertGraph2Vector_ver2(grille, &MyNodes_2, &Neighbourhoods, coords);

  // On applique tutte sur notre structure de noeud
  tutte_2(&MyNodes_2, &Neighbourhoods, coords, 1e-6, true);

  // On récupére les déplacement dans notre grille
  convertVector_ver2_2Graph(&MyNodes_2, coords, grille);

  gettimeofday(&timeEnd, NULL);
  double res = timeEnd.tv_sec - timeBegin.tv_sec + (double)(timeEnd.tv_usec - timeBegin.tv_usec)/1e6;

  cout << "temps d'exécution de Tutte : " << res << " s" << endl; 

  free(coords);
}

void tutte_seq_2_bis(Graph * graph, Graph * grille) {
  (void)graph;
  
  vector<MyNode_ver2> MyNodes_2 (grille->numberOfNodes());   // contient l'ensemble des noeuds
  vector<int> Neighbourhoods;           // contient l'indice de tous les noeuds du voisinage de chaque noeud
  vector<Vec2f> * coords = new vector<Vec2f>(grille->numberOfNodes());                      // contient les coordonnées de chaque noeud

  struct timeval timeBegin, timeEnd;
  gettimeofday(&timeBegin, NULL);

  // On récupére les noeuds de la grille dans nos vecteur
  convertGraph2Vector_ver2(grille, &MyNodes_2, &Neighbourhoods, coords);

  // On applique tutte sur notre structure de noeud
  tutte_2_bis(&MyNodes_2, &Neighbourhoods, coords, 1e-6, true);

  // On récupére les déplacement dans notre grille
  convertVector_ver2_2Graph(&MyNodes_2, coords, grille);

  gettimeofday(&timeEnd, NULL);
  double res = timeEnd.tv_sec - timeBegin.tv_sec + (double)(timeEnd.tv_usec - timeBegin.tv_usec)/1e6;

  cout << "temps d'exécution de Tutte : " << res << " s" << endl; 

  free(coords);
}

void tutte_seq_2_openmp(Graph * graph, Graph * grille) {
  (void)graph;
  
  vector<MyNode_ver2> MyNodes_2 (grille->numberOfNodes());   // contient l'ensemble des noeuds
  vector<int> Neighbourhoods;           // contient l'indice de tous les noeuds du voisinage de chaque noeud
  vector<Vec2f> * coords = new vector<Vec2f>(grille->numberOfNodes());                      // contient les coordonnées de chaque noeud

  struct timeval timeBegin, timeEnd;
  gettimeofday(&timeBegin, NULL);

  // On récupére les noeuds de la grille dans nos vecteur
  convertGraph2Vector_ver2(grille, &MyNodes_2, &Neighbourhoods, coords);

  // On applique tutte sur notre structure de noeud
  tutte_2_openmp(&MyNodes_2, &Neighbourhoods, coords, 1e-6, true);

  // On récupére les déplacement dans notre grille
  convertVector_ver2_2Graph(&MyNodes_2, coords, grille);

  gettimeofday(&timeEnd, NULL);
  double res = timeEnd.tv_sec - timeBegin.tv_sec + (double)(timeEnd.tv_usec - timeBegin.tv_usec)/1e6;

  cout << "temps d'exécution de Tutte : " << res << " s" << endl; 

  free(coords);
}

/*
 * tutte on the v3 of our data structure
 */
void tutte_seq_3 (Graph * graph, Graph * grille){
  (void)graph;
  vector <Data> datas;
  vector<vector<int> > matrix(grille->numberOfNodes());

  struct timeval timeBegin, timeEnd;
  gettimeofday(&timeBegin, NULL);

  // On récupére les noeuds de la grille dans nos vecteur
  convertGraph_v3(grille, &datas , &matrix);

  // On applique tutte sur notre structure de noeud
  tutte_seq_3(&datas, &matrix, 1e-6, true);

  // On récupére les déplacement dans notre grille
  updateGraph_v3(grille, &datas);

  gettimeofday(&timeEnd, NULL);
  double res = timeEnd.tv_sec - timeBegin.tv_sec + (double)(timeEnd.tv_usec - timeBegin.tv_usec)/1e6;

  cout << "temps d'exécution de Tutte : " << res << " s" << endl; 
}

/*
 * tutte on the v3 of our data structure
 */
void tutte_parallel_asynchrone(Graph * graph, Graph * grille){
  (void)graph;
  vector <Data> datas;
  vector<vector<int> > matrix(grille->numberOfNodes());

  struct timeval timeBegin, timeEnd;
  gettimeofday(&timeBegin, NULL);

  // On récupére les noeuds de la grille dans nos vecteur
  convertGraph_v3(grille, &datas , &matrix);

  // On applique tutte sur notre structure de noeud
  tutte_seq_3(&datas, &matrix, 1e-6, true);

  // On récupére les déplacement dans notre grille
  updateGraph_v3(grille, &datas);

  gettimeofday(&timeEnd, NULL);
  double res = timeEnd.tv_sec - timeBegin.tv_sec + (double)(timeEnd.tv_usec - timeBegin.tv_usec)/1e6;

  cout << "temps d'exécution de Tutte : " << res << " s" << endl; 
}


int main(int argc, char * argv[])  {
  if (argc != 2) {
    if ((1 < argc) && (strcmp(argv[1], "-l") == 0)) {
      cout << "" << endl;
      cout << "  ==  Tutte versions   ==  " << endl;
      cout << "0 : sequential tutte" << endl;
      cout << "1 : sequential tutte version 2" << endl;
      cout << "2 : sequential tutte version 2 bis (Vec2f)" << endl;
      cout << "3 : sequential tutte version 3" << endl;
      cout << "4 : openMP tutte" << endl;
      cout << "" << endl;
      exit(EXIT_SUCCESS);
    }

    cout << "Usage : "<< argv[0] << " <nb_exec>" << endl;
    cout << "" << endl;
    cout << "Type \"./benchmark -l\" to view the list of tutte version." <<endl;
    cout << "" << endl;
    exit(1);
  }

  // Permet d'utiliser loadGraph méthode
  tlp::initTulipLib();

  // Lecture d'un graphe d'entré
  //tlp::Graph* graph = tlp::loadGraph(argv[1]);
  tlp::Graph* graph = tlp::loadGraph("../graphes/imdb.tlp.gz");
  
  // Récupérer la grille sur laquelle il faut appliquer l'algo de Tutte
  // Il faut que la grille sur laquelle on doit appliquer l'algorithme ait l'indentifiant 2
  tlp::Graph *grille = graph->getSubGraph(2);

  //int tutte_version = atoi(argv[2]);
  int nb_exec = atoi(argv[1]);

  cout << "Tutte séquentiel asynchrone;" << endl;
  tutte_seq(graph, grille, nb_exec);
  // cout << "Tutte séquentiel asynchrone 2;" << endl;
  // tutte_seq_2(graph, grille, nb_exec);
  // cout << "Tutte séquentiel asynchrone 2 (Vec2f);" << endl;
  // tutte_seq_2_bis(graph, grille, nb_exec);
  // cout << "Tutte séquentiel asynchrone 3;" << endl;
  // tutte_seq_3(graph, grille, nb_exec);
  // cout << "Tutte parallèle synchrone;" << endl;
  // tutte_seq_2_openmp(graph, grille, nb_exec);

  //char * filename_output = argv[3];
  // switch(tutte_version) {
  // case 0:
  //   cout << "Tutte séquentiel asynchrone;" << endl;
  //   tutte_seq(graph, grille);
  //   break;
  // case 1:
  //   cout << "Tutte séquentiel asynchrone 2;" << endl;
  //   tutte_seq_2(graph, grille);
  //   break;
  // case 2:
  //   cout << "Tutte séquentiel asynchrone 2 (Vec2f);" << endl;
  //   tutte_seq_2_bis(graph, grille);
  //   break;
  // case 3:
  //   cout << "Tutte séquentiel asynchrone 3;" << endl;
  //   tutte_seq_3(graph, grille);
  //   break;
  // case 4:
  //   cout << "Tutte parallèle synchrone;" << endl;
  //   tutte_seq_2_openmp(graph, grille);
  //   break;
  // default:
  //   cout << "The tutte_version must in 0..4;" << endl;
  // }
  
  delete graph;

  return 0;
}