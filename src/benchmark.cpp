#include <iostream>
#include <cstdio>

#include <sys/time.h>

#include "myNode.h"
#include "toolkit.h"
#include "tutte.h"

#include <omp.h>

using namespace std;
using namespace tlp;

#define NB_TEST 6

double moyennes[NB_TEST];
double ecarts[NB_TEST]; 

void tutte_seq(Graph * graph, Graph * grille, int nb_exec) {
  (void)graph;
  (void)nb_exec;
  // On récupére les noeuds de la grille dans notre structure de noeud
  vector<MyNode> * MyNodes = convertGraph2Vector(grille);
  vector<MyNode> save(*MyNodes);

  double t_res = 0, t0, t1;
  double t_max = 0, t_min = 10;
  double t_carre = 0;

  for (int i = 0; i < nb_exec; ++i) {
    // On applique tutte sur notre structure de noeud
    t0 = omp_get_wtime();
    tutte(MyNodes, 1e-6, true);
    t1 = omp_get_wtime();
    t_res += t1 - t0;
    t_max = std::max(t_max, t1 - t0);
    t_min = std::min(t_min, t1 - t0);
    t_carre += (t1 - t0) * (t1 - t0);

    *MyNodes = save;
  }

  double moy = t_res/nb_exec;
  double ecart_type = sqrt(fabs((t_carre / nb_exec) - moy * moy));
  moyennes[0] = moy;
  ecarts[0] = ecart_type;
  // cout << "temps d'exécution de Tutte : " << moy << " s" << endl; 
  // cout << "max : " << t_max << " s" << endl;
  // cout << "min : " << t_min << " s" << endl;
  // cout << "ecart type : " << ecart_type << " s" << endl;
  // cout << endl;

  // Libération des ressources enjeux
  delete MyNodes;
}

void tutte_seq_2(Graph * graph, Graph * grille, int nb_exec) {
  (void)graph;

  vector<MyNode_ver2> MyNodes_2 (grille->numberOfNodes());   // contient l'ensemble des noeuds
  vector<int> Neighbourhoods;           // contient l'indice de tous les noeuds du voisinage de chaque noeud
  vector<Vec2f> coords(grille->numberOfNodes());
  
  // On récupére les noeuds de la grille dans nos vecteur
  convertGraph2Vector_ver2(grille, &MyNodes_2, &Neighbourhoods, &coords);

  vector<Vec2f> save(coords);

  double t_res = 0, t0, t1;
  double t_max = 0, t_min = 10;
  double t_carre = 0;

  for (int i = 0; i < nb_exec; ++i) {
    // On applique tutte sur notre structure de noeud
    t0 = omp_get_wtime();
    tutte_2(&MyNodes_2, &Neighbourhoods, &coords, 1e-6, true);
    t1 = omp_get_wtime();
    t_res += t1 - t0;
    t_max = std::max(t_max, t1 - t0);
    t_min = std::min(t_min, t1 - t0);
    t_carre += (t1 - t0) * (t1 - t0);

    //cout << t1 - t0 << endl;
    
    coords = save;
  }

  double moy = t_res/nb_exec;
  double ecart_type = sqrt(fabs((t_carre / nb_exec) - moy * moy));
  moyennes[1] = moy;
  ecarts[1] = ecart_type;
  // cout << "temps d'exécution de Tutte : " << moy << " s" << endl; 
  // cout << "max : " << t_max << " s" << endl;
  // cout << "min : " << t_min << " s" << endl;
  // cout << "ecart type : " << ecart_type << " s" << endl;
  // cout << endl;
}

void tutte_seq_2_bis(Graph * graph, Graph * grille, int nb_exec) {
  (void)graph;
  
  vector<MyNode_ver2> MyNodes_2 (grille->numberOfNodes());   // contient l'ensemble des noeuds
  vector<int> Neighbourhoods;           // contient l'indice de tous les noeuds du voisinage de chaque noeud
  vector<Vec2f> coords(grille->numberOfNodes());

  // On récupére les noeuds de la grille dans nos vecteur
  convertGraph2Vector_ver2(grille, &MyNodes_2, &Neighbourhoods, &coords);

  vector<Vec2f> save(coords);

  double t_res = 0, t0, t1;
  double t_max = 0, t_min = 10;
  double t_carre = 0;

  for (int i = 0; i < nb_exec; ++i) {
    // On applique tutte sur notre structure de noeud
    t0 = omp_get_wtime();
    tutte_2_bis(&MyNodes_2, &Neighbourhoods, &coords, 1e-6, true);
    t1 = omp_get_wtime();
    t_res += t1 - t0;
    t_max = std::max(t_max, t1 - t0);
    t_min = std::min(t_min, t1 - t0);
    t_carre += (t1 - t0) * (t1 - t0);

    coords = save;
  }

  double moy = t_res/nb_exec;
  double ecart_type = sqrt(fabs((t_carre / nb_exec) - moy * moy));
  moyennes[2] = moy;
  ecarts[2] = ecart_type;
  // cout << "temps d'exécution de Tutte : " << moy << " s" << endl; 
  // cout << "max : " << t_max << " s" << endl;
  // cout << "min : " << t_min << " s" << endl;
  // cout << "ecart type : " << ecart_type << " s" << endl;
  // cout << endl;
}

void tutte_seq_2_openmp(Graph * graph, Graph * grille, int nb_exec) {
  (void)graph;

  vector<MyNode_ver2> MyNodes_2 (grille->numberOfNodes());   // contient l'ensemble des noeuds
  vector<int> Neighbourhoods;           // contient l'indice de tous les noeuds du voisinage de chaque noeud
  vector<Vec2f> coords(grille->numberOfNodes());

  // On récupére les noeuds de la grille dans nos vecteur
  convertGraph2Vector_ver2(grille, &MyNodes_2, &Neighbourhoods, &coords);

  vector<Vec2f> save(coords);

  double t_res = 0, t0, t1;
  double t_max = 0, t_min = 10;
  double t_carre = 0;

  for (int i = 0; i < nb_exec; ++i) {
    // On applique tutte sur notre structure de noeud
    t0 = omp_get_wtime();
    tutte_2_openmp(&MyNodes_2, &Neighbourhoods, &coords, 1e-6, true);
    t1 = omp_get_wtime();
    t_res += t1 - t0;
    t_max = std::max(t_max, t1 - t0);
    t_min = std::min(t_min, t1 - t0);
    t_carre += (t1 - t0) * (t1 - t0);

    //cerr << i << " : " << t1 - t0 << endl;
    
    coords = save;
  }

  double moy = t_res/nb_exec;
  double ecart_type = sqrt(fabs((t_carre / nb_exec) - moy * moy));
  moyennes[3] = moy;
  ecarts[3] = ecart_type;
  // cout << "temps d'exécution de Tutte : " << moy << " s" << endl; 
  // cout << "max : " << t_max << " s" << endl;
  // cout << "min : " << t_min << " s" << endl;
  // cout << "ecart type : " << ecart_type << " s" << endl;
  // cout << endl;
}

/*
 * tutte on the v3 of our data structure
 */
void tutte_seq_3 (Graph * graph, Graph * grille, int nb_exec){
  (void)graph;

  vector <Data> datas;
  vector<vector<int> > matrix(grille->numberOfNodes());

  // On récupére les noeuds de la grille dans nos vecteur
  convertGraph_v3(grille, &datas , &matrix);

  vector<Data> save = datas;

  double t_res = 0, t0, t1;
  double t_max = 0, t_min = 10;
  double t_carre = 0;

  for (int i = 0; i < nb_exec; ++i) {
    // On applique tutte sur notre structure de noeud
    t0 = omp_get_wtime();
    tutte_seq_3(&datas, &matrix, 1e-6, true);
    t1 = omp_get_wtime();
    t_res += t1 - t0;
    t_max = std::max(t_max, t1 - t0);
    t_min = std::min(t_min, t1 - t0);
    t_carre += (t1 - t0) * (t1 - t0);

    //cerr << i << " : " << t1 - t0 << endl;
    
    datas = save;
  }

  double moy = t_res/nb_exec;
  double ecart_type = sqrt(fabs((t_carre / nb_exec) - moy * moy));
  moyennes[4] = moy;
  ecarts[4] = ecart_type;
  // cout << "temps d'exécution de Tutte : " << moy << " s" << endl; 
  // cout << "max : " << t_max << " s" << endl;
  // cout << "min : " << t_min << " s" << endl;
  // cout << "ecart type : " << ecart_type << " s" << endl;
  // cout << endl;
}

static inline
void remise_a_zero(vector<vector<MyNode *> *> *vectors, Coord *coordonnees){
  vector<vector<MyNode *> *>::iterator it;
  for (it=vectors->begin(); it < vectors->end(); it++)
    {
      vector<MyNode *>::iterator it2 = (*it)->begin();
      for (it2=(*it)->begin(); it2 < (*it)->end(); it2++)
	(*it2)->setCoord(coordonnees[(*it2)->getNode().id]);
    }
}

static inline
void sauvegarde(vector<vector<MyNode *> *> *vectors, Coord *coordonnees){
  vector<vector<MyNode *> *>::iterator it;
  for (it=vectors->begin(); it < vectors->end(); it++)
    {
      vector<MyNode *>::iterator it2 = (*it)->begin();
      for (it2=(*it)->begin(); it2 < (*it)->end(); it2++)
	coordonnees[(*it2)->getNode().id] = (*it2)->getCoord();
    }
}

void tutte_parallel_asynchrone(Graph * graph, int nb_exec){
  map<int, MyNode *> *all_nodes = convertGraph2Map(graph);
  Coord coordonnees[all_nodes->size()];
  vector<vector<MyNode *> *> *vectors = separateMap2Vectors(all_nodes);

  sauvegarde(vectors,coordonnees);

  double t_res = 0, t0, t1;
  double t_max = 0, t_min = 10;
  double t_carre = 0;

  for (int i = 0; i < nb_exec; ++i) {
    t0 = omp_get_wtime();
    tutte_parallel_asynchrone(vectors, 1e-6, true);
    t1 = omp_get_wtime();
    t_res += t1 - t0;
    t_max = std::max(t_max, t1 - t0);
    t_min = std::min(t_min, t1 - t0);
    t_carre += (t1 - t0) * (t1 - t0);

    // cerr << i << " : " << t1 - t0 << endl;
    
    remise_a_zero(vectors,coordonnees);
  }

  double moy = t_res/nb_exec;
  double ecart_type = sqrt(fabs((t_carre / nb_exec) - moy * moy));
  moyennes[5] = moy;
  ecarts[5] = ecart_type;
  // cout << "temps d'exécution de Tutte : " << moy << " s" << endl; 
  // cout << "max : " << t_max << " s" << endl;
  // cout << "min : " << t_min << " s" << endl;
  // cout << "ecart type : " << ecart_type << " s" << endl;
  // cout << endl;

  // Libération des ressources enjeux
  delete vectors;
  delete all_nodes;
}

int main(int argc, char * argv[])  {
  if (argc != 3) {
    cout << "Usage : "<< argv[0] << " <graph_path> <nb_exec>" << endl;
    cout << "" << endl;
    cout << "Type \"./benchmark -l\" to view the list of tutte version." <<endl;
    cout << "" << endl;
    exit(1);
  }

  // Permet d'utiliser loadGraph méthode
  tlp::initTulipLib();

  // Lecture d'un graphe d'entré
  tlp::Graph* graph = tlp::loadGraph(argv[1]);
  
  // Récupérer la grille sur laquelle il faut appliquer l'algo de Tutte
  tlp::Graph *grille = graph->getSubGraph(2);

  int nb_exec = atoi(argv[2]);

  cout << "Benchmark on graph : " << argv[1] << endl << endl;

  cout << "Tutte séquentiel asynchrone -> 0" << endl;
  cout << "Tutte séquentiel asynchrone 2 -> 1" << endl;
  cout << "Tutte séquentiel asynchrone 2 (Vec2f) -> 2" << endl;
  cout << "Tutte séquentiel asynchrone 3 -> 3" << endl;
  cout << "Tutte parallèle synchrone -> 4" << endl;
  cout << "Tutte parallèle asynchrone -> 5" << endl;
 
  tutte_seq(graph, grille, nb_exec);
  tutte_seq_2(graph, grille, nb_exec);
  tutte_seq_2_bis(graph, grille, nb_exec);
  tutte_seq_3(graph, grille, nb_exec);
  tutte_seq_2_openmp(graph, grille, nb_exec);
  tutte_parallel_asynchrone(graph, nb_exec);

  cout << "menMeans = (";
  for(int i; i < NB_TEST; i++)
    cout << moyennes[i] << ", ";
  cout << ")" << endl;
  cout << "menStd = (";
  for(int i; i < NB_TEST; i++)
    cout << ecarts[i] << ", ";
  cout << ")" << endl;

  // cout << "Tutte séquentiel asynchrone;" << endl;
  // tutte_seq(graph, grille, nb_exec);
  // cout << "Tutte séquentiel asynchrone 2;" << endl;
  // tutte_seq_2(graph, grille, nb_exec);
  // cout << "Tutte séquentiel asynchrone 2 (Vec2f);" << endl;
  // tutte_seq_2_bis(graph, grille, nb_exec);
  // cout << "Tutte séquentiel asynchrone 3;" << endl;
  // tutte_seq_3(graph, grille, nb_exec);
  // cout << "Tutte parallèle synchrone;" << endl;
  // tutte_seq_2_openmp(graph, grille, nb_exec);
  // cout << "Tutte parallèle asynchrone;" << endl;
  // tutte_parallel_asynchrone(graph, nb_exec);
  
  delete graph;
  
  return 0;
}
