#include <stdio.h>

#include <tulip/LayoutProperty.h>

#include "MyGraph.h"

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

void test_getMappedGraph(Graph * graph) {
  // On récupére la propriété viewLayout
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");

  // Récupérer tous les noeuds du graph dans MyGraph
  map<node, int> AllNodes;
  MyGraph my_graph;
  
  Iterator<node> *itN = graph->getNodes();
  int i = 0;
  while(itN->hasNext()) {
    Data d;
    d.n = itN->next();
    AllNodes[d.n] = i;
    d.coord = layout->getNodeValue(d.n);
    my_graph.datas.push_back(d);
    i++;
  } delete itN;

  cout << "Avant MAJ voisin" << endl; 
  cout << my_graph << endl;

  // Récupérer le voisinage de chaque noeud de la map
  for (unsigned int i = 0; i < my_graph.datas.size(); i++) {
    Iterator<node> *itN=graph->getInOutNodes(my_graph.datas[i].n);
    vector<int>* voisin = new vector<int>;
    while(itN->hasNext()) {
      int id = AllNodes[itN->next()];
      voisin->push_back(id);
    } delete itN;
    my_graph.matrix.push_back(voisin);
  }

  // FIN DE L CONSTRUCTION DU VECTOR
  
  cout << "Après MAJ voisin" << endl;
  cout << my_graph << endl;
  
  // Modifier les coordonnée du premier noeud, et vérifier que cela a bien impacté 
  for (uint i = 0; i < my_graph.datas.size(); i++) {
    my_graph.datas[i].coord = Coord(4, 8, 9);
  }
  cout << "Après Modification des coordonnées" << endl;
  cout << my_graph << endl;
}

int main() {
  //create an empty graph
  Graph *graph=tlp::newGraph();
  //build the graph
  buildGraph(graph);
  
  //teste de notre graphe
  test_getMappedGraph(graph);

  delete graph;
  return 1;
}
