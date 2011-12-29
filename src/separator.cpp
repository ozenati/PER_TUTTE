#include <iostream>
#include <tulip/Graph.h>
#include <tulip/GlyphManager.h>
#include <tulip/LayoutProperty.h>
#include <map>
#include "MyNode.h"

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

  initTulipLib();

  Graph* graph = loadGraph(argv[1]);

  if(graph == NULL)
    {
      cerr << argv[1] << " is not a graph file" << endl;
      exit(-1);
    }

  LayoutProperty *layout = graph->getLocalProperty<LayoutProperty>("viewLayout");
  BooleanProperty *fixed = graph->getProperty<BooleanProperty>("fixed nodes");
  BooleanProperty *bordure = graph->getProperty<BooleanProperty>("viewSelection");

  map<int,MyNode *> all_nodes;
  
  Iterator<node> *itNodes = graph->getNodes();

  //=====================//
  //  Boucle principale  //
  //=====================//

  while(itNodes->hasNext()) 
    {
      node n = itNodes->next();

      if(all_nodes[n.id] == NULL)
	{
	  Coord c = layout->getNodeValue(n);
	  bool res = !(fixed->getNodeValue(n)) && !(bordure->getNodeValue(n));
	  all_nodes[n.id] = new MyNode(n, res, c); 
	}

      MyNode *pn = all_nodes[n.id];


      cout << "node: " <<  n.id << endl;
      cout << " neighborhood: {";
      Iterator<node> *itN = graph->getInOutNodes(n);

      while(itN->hasNext())
	{
	  node n = itN->next();
	  cout << n.id;
	  if (itN->hasNext()) cout << ",";
	  if(all_nodes[n.id] == NULL)
	    {
	      Coord c = layout->getNodeValue(n);
	      bool res = !(fixed->getNodeValue(n)) && !(bordure->getNodeValue(n));
	      all_nodes[n.id] = new MyNode(n, res, c); 
	    }
	  pn->getVoisin()->push_back(all_nodes[n.id]);
	}

      delete itN; //!!!Warning : do not forget to delete iterators (memory leak)
      cout << "}" << endl;
    }

  delete graph;
  return 0;
}
