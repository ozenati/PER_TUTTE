#include <stdio.h>

#include <tulip/LayoutProperty.h>

#include "MyNode.h"

using namespace std;
using namespace tlp;

void buildGraph(Graph *graph) {
  //add three nodes
  node n1=graph->addNode();
  node n2=graph->addNode();
  node n3=graph->addNode();
  //add three edges
  graph->addEdge(n2,n3);
  graph->addEdge(n1,n2);
  graph->addEdge(n3,n1);

  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");
  
  Iterator<node> *itN = graph->getNodes();
  while(itN->hasNext()) {
    node tmp_n = itN->next();
    layout->setNodeValue(tmp_n, Coord(0, tmp_n.id, 0));
  } delete itN;
}

void test_getVoisin(Graph * graph)  {
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");

  // Récupérer le noeud 1 et le mettre dans un MyNode  
  node noeud = graph->getOneNode();
  Coord c = layout->getNodeValue(noeud);

  MyNode n(noeud, c);
  cout << n << endl << "\n";

  // On met le voisinage de noeud dans le vector voisin de MyNode
  Iterator<node> *itN=graph->getInOutNodes(noeud);
  vector<MyNode *> * tmp_vec =  n.getVoisin();
  while(itN->hasNext()) {
    node tmp_noeud = itN->next();
    Coord c = layout->getNodeValue(tmp_noeud);    
    MyNode tmp_n(tmp_noeud, c);
    tmp_vec->push_back(&tmp_n);
  } delete itN; //!!!Warning : do not forget to delete iterators (memory leak)

  cout << n << endl;
}

// struct idCompare
// {
//   bool operator()(const int id1, const int id2) const
//   {
//     return id1 < id2;
//   }
// };

void test_getMappedGraph(Graph * graph) {
  // On récupére la propriété viewLayout
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");

  // Récupérer tous les noeuds du graph dans une map de MyNode
  map<node, int, nidCompare> AllNodes;
  vector<MyNode> MyNodes;
  
  Iterator<node> *itN = graph->getNodes();
  int i = 0;
  while(itN->hasNext()) {
    node tmp_n = itN->next();
    AllNodes[tmp_n] = i;

    Coord c = layout->getNodeValue(tmp_n);    
    MyNode n(tmp_n, c);
    
    MyNodes.push_back(n);
    i++;
  } delete itN;

  cout << "Avant MAJ voisin" << endl;
  for (unsigned int i = 0; i < MyNodes.size(); i++) {
    cout << MyNodes[i] << endl;
  }
  cout << endl;

  // Récupérer le voisinage de chaque noeud de la map
  for (unsigned int i = 0; i < MyNodes.size(); i++) {
    Iterator<node> *itN=graph->getInOutNodes(MyNodes[i].getNode());
    while(itN->hasNext()) {
      int key = AllNodes[itN->next()];
      
      MyNodes[i].getVoisin()->push_back(&MyNodes[key]);
    } delete itN;
  }

  // FIN DE L CONSTRUCTION DU VECTOR

  cout << "Après MAJ voisin" << endl;
  for (unsigned int i = 0; i < MyNodes.size(); i++) {
    cout << MyNodes[i] << endl;
  }
  cout << endl;

  // Modifier les coordonnée du premier noeud, et vérifier que cela a bien impacté 
  // le voisinage des noeuds connectés à ce-dernier
  MyNode * node_0 = &MyNodes[0];
  node_0->setCoord(Coord(4, 8, 9));

  vector<MyNode *> * voisin_1 = MyNodes[1].getVoisin();
  // cout << voisin_1->size() << endl;
  // cout << *voisin_1[0][0] << endl;
  // cout << voisin_1[0][0]->getNode().id << endl;
  // cout << voisin_1[0][1]->getNode().id << endl;

  for (unsigned int i = 0; i < voisin_1->size(); i++) {
    // On recherche le noeud 0 dans le voisinage du noeud 1
    if (node_0->getNode().id == (* voisin_1)[i]->getNode().id) {
      cout << "noeud 0 : " << *node_0 << "\n" 
      	   << "voisinage : " << *(* voisin_1)[i] << endl;
    }
  }
}

// TODO
// Créer une classe MyGraph qui prendre un graphe en entrée et resort un vector
// ou qui prendre en entrée un graphe et une propriété pour les sommets fixed et sommets sélectionnés
// Faire attention : initialement, seul les arêtes sont sélections comme fixes (bordure)

int main() {
  //create an empty graph
  Graph *graph=tlp::newGraph();
  //build the graph
  buildGraph(graph);
  
  //test_getVoisin(graph);
  
  test_getMappedGraph(graph);

  delete graph;
  return 1;
}
