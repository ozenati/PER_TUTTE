#include <iostream>
#include <tulip/Graph.h>
#include <tulip/LayoutProperty.h>
#include <map>
#include "Per_node.h"

using namespace std;
using namespace tlp;

int main(int argc, char **argv)
{
  if(argc != 2)
    {
      cerr << "Usage: " << argv[0] << " <graph_file>" << endl;
      exit(-1);
    }

  //==================//
  //  Initialisation  //
  //==================//

  Graph* graph = loadGraph(argv[1]);

  if(graph == NULL)
    {
      cerr << argv[1] << " is not a graph file" << endl;
      exit(-1);
    }

  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");

  map<int,Per_node *> all_nodes;
  
  Iterator<node> *itNodes = graph->getNodes();

  //=====================//
  //  Boucle principale  //
  //=====================//

  while(itNodes->hasNext()) 
    {
      node n = itNodes->next();
      if(all_nodes[n.id] == NULL)
	all_nodes[n.id] = new Per_node(n.id);

      Coord c = layout->getNodeValue(n);

      Per_node *pn = all_nodes[n.id];
      pn->pos.x = c.getX();
      pn->pos.y = c.getY();

      cout << "node: " <<  n.id << endl;
      cout << c << endl;    
      cout << " neighborhood: {";
      Iterator<node> *itN = graph->getInOutNodes(n);

      while(itN->hasNext())
	{
	  node n = itN->next();
	  cout << n.id;
	  if (itN->hasNext()) cout << ",";
	  if(all_nodes[n.id] == NULL)
	    all_nodes[n.id] = new Per_node(n.id);
	  pn->neighbors.push_back(all_nodes[n.id]);
	}

      delete itN; //!!!Warning : do not forget to delete iterators (memory leak)
      cout << "}" << endl;
    }

  delete graph;
  return 0;
}
