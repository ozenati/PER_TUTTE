#include <iostream>
#include <tulip/Graph.h>
#include <cstdlib>
#include "list.h"
#include "cnode.h"

using namespace std;
using namespace tlp;

int main(int argc, char **argv)
{
  if(argc != 2)
    {
      cerr << "Usage: " << argv[0] << " <graph_file>" << endl;
      exit(-1);
    }
  
  Graph* graph = loadGraph(argv[1]);

  if(graph == NULL)
    {
      cerr << argv[1] << " is not a graph file" << endl;
      exit(-1);
    }

  list_c *list_of_nodes = create_list();
  
  Iterator<node> *itNodes = graph->getNodes();

  while(itNodes->hasNext()) {
    node n = itNodes->next();
    cout << "node: " <<  n.id << endl;
    
    cout << " neighborhood: {";
    Iterator<node> *itN = graph->getInOutNodes(n);

    while(itN->hasNext()) {
      cout << itN->next().id;

      if (itN->hasNext()) cout << ",";
    }

    delete itN; //!!!Warning : do not forget to delete iterators (memory leak)
    cout << "}" << endl;
  }

  return 0;
}
