#include <iostream>
#include <tulip/Graph.h>
#include <tulip/GlyphManager.h>
#include <tulip/LayoutProperty.h>
#include <map>

#include "myNode.h"
#include "separator.h"

using namespace std;
using namespace tlp;

void copy(map<int, MyNode *> *dest,map<int, MyNode *> *src)
{
  map<int, MyNode *>::iterator elt;
  for(elt = src->begin(); elt != src->end(); elt++)
    (*dest)[elt->first] = elt->second;
} 

vector<vector<MyNode *> *> *
separateMap2Vectors(map<int, MyNode *> *all_nodes)
{
  vector<vector<MyNode *> *> *vectors = new vector<vector<MyNode *> *>;
  
  while(!all_nodes->empty())
    {
      map<int, MyNode *> z_nodes;// = *all_nodes;
      copy(&z_nodes,all_nodes);
      vector<MyNode *> *v = new vector<MyNode *>;
      while(!z_nodes.empty())
	{
	  map<int, MyNode *>::iterator elt;
	  elt = z_nodes.begin();
	  MyNode *n = elt->second;
	  v->push_back(n);
	  all_nodes->erase(n->getNode().id);
	  z_nodes.erase(n->getNode().id);
	  vector<MyNode *> *nv = n->getVoisin();
	  vector<MyNode *>::iterator it;
	  for ( it=nv->begin() ; it < nv->end(); it++ )
	    {
	      MyNode *nvm = *it;
	      z_nodes.erase(nvm->getNode().id);
	    }
	}
      vectors->push_back(v);
    }
  return vectors;
}


map<int, MyNode *> *
convertGraph2Map(Graph *graph)
{
  LayoutProperty *layout = graph->getLocalProperty<LayoutProperty>("viewLayout");
  BooleanProperty *fixed = graph->getProperty<BooleanProperty>("fixed nodes");
  BooleanProperty *bordure = graph->getProperty<BooleanProperty>("viewSelection");

  map<int,MyNode *> all_nodes;

  // Boucle sur tous les noeuds
  Iterator<node> *itNodes = graph->getNodes();
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

      // Boucle sur tous les voisins du noeud courant
      Iterator<node> *itN = graph->getInOutNodes(n);
      while(itN->hasNext())
	{
	  node n = itN->next();
	  if(all_nodes[n.id] == NULL)
	    {
	      Coord c = layout->getNodeValue(n);
	      bool res = !(fixed->getNodeValue(n)) && !(bordure->getNodeValue(n));
	      all_nodes[n.id] = new MyNode(n, res, c); 
	    }
	  pn->getVoisin()->push_back(all_nodes[n.id]);
	}
      delete itN;
    }
  delete itNodes;
  return new map<int, MyNode *>(all_nodes);
}

void applyVectors2Graph(vector<vector<MyNode *> *> *vectors, Graph * graph) {
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");
  
  vector<vector<MyNode *> *>::iterator it;
  for (it=vectors->begin(); it < vectors->end(); it++)
    {
      // Selection de l'ensemble courant;
      vector<MyNode *> *MyNodes = (*it);
      
      for(uint i = 0; i < MyNodes->size(); i++) {
	layout->setNodeValue((* MyNodes)[i]->getNode(), (* MyNodes)[i]->getCoord());
      }
    }
}


// int main(int argc, char **argv)
// {
//   if(argc != 2)
//     {
//       cerr << "Usage: " << argv[0] << " <graph_file>" << endl;
//       exit(-1);
//     }

//   //==================//
//   //  Initialisation  //
//   //==================//

//   initTulipLib();

//   Graph* graph = loadGraph(argv[1]);

//   if(graph == NULL)
//     {
//       cerr << argv[1] << " is not a graph file" << endl;
//       exit(-1);
//     }

//   map<int, MyNode *> *all_nodes = convertGraph2Map(graph);

//   vector<vector<MyNode *> *> *vectors = separateMap2Vectors(all_nodes);

//   int i;
//   vector<vector<MyNode *> *>::iterator it;
//   for (it=vectors->begin(), i = 0 ; it < vectors->end(); it++, i++)
//     {
//       cout << "Ensemble " << i << " contient:" << endl;
//       cout << "{";
//       vector<MyNode *>::iterator it2 = (*it)->begin();
//       for (it2=(*it)->begin(); it2 < (*it)->end(); it2++)
// 	{
// 	  MyNode *n = *it2;
// 	  cout << n->getNode().id << " ";
// 	}
//       cout << "}" << endl; 
//     }
//   delete all_nodes;
//   delete graph;
//   return 0;
// }

