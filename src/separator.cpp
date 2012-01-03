#include <iostream>
#include <tulip/Graph.h>
#include <tulip/GlyphManager.h>
#include <tulip/LayoutProperty.h>
#include <map>
#include "MyNode.h"

using namespace std;
using namespace tlp;

void copy(map<int, MyNode *> *dest,map<int, MyNode *> *src)
{
  map<int, MyNode *>::iterator elt;
  // while(elt->hasNext()){
  //   MyNode * tmp = elt->next();
  //   (*dest)[tmp->getNode().id] = tmp;
  // }
    
  // map<string,int>::iterator iter;   
  // for( iter = stringCounts.begin(); iter != stringCounts.end(); iter++ ) {
  //   cout << "word: " << iter->first << ", count: " << iter->second << endl;
  // }

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
      cout << z_nodes.size() << endl;
      //map<int, MyNode *> *z_nodes(all_nodes);
      cout << "Z=Y" << endl;
      vector<MyNode *> *v = new vector<MyNode *>;
      while(!z_nodes.empty())
	{
	  map<int, MyNode *>::iterator elt;
	  elt = all_nodes->begin();
	  MyNode *n = elt->second;
	  cout << n->getNode().id << " premier element de Z" << endl;
	  v->push_back(n);
	  all_nodes->erase(n->getNode().id);
	  cout << " Y - " << n->getNode().id << endl;
	  z_nodes.erase(n->getNode().id);
	  cout << " Z - " << n->getNode().id << " - voisins de " << n->getNode().id << " (";
	  vector<MyNode *> *nv = n->getVoisin();
	  vector<MyNode *>::iterator it;
	  for ( it=nv->begin() ; it < nv->end(); it++ )
	    {
	      MyNode *nvm = *it;
	      if(z_nodes[nvm->getNode().id] != NULL)
		{
		  z_nodes.erase(nvm->getNode().id);
		  cout << nvm->getNode().id << " ";
		}
	    }
	  cout << ")" << endl;
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

  map<int, MyNode *> *all_nodes = convertGraph2Map(graph);

  vector<vector<MyNode *> *> *vectors = separateMap2Vectors(all_nodes);

  cout << graph << endl;

  int i;
  vector<vector<MyNode *> *>::iterator it;
  for (it=vectors->begin(), i = 0 ; it < vectors->end(); it++, i++)
    {
      cout << "Ensemble " << i << " contient:" << endl;
      cout << "{";
      vector<MyNode *>::iterator it2 = (*it)->begin();
      for (it2=(*it)->begin(); it2 < (*it)->end(); it2++)
	{
	  MyNode *n = *it2;
	  cout << n->getNode().id << " ";
	}
      cout << "}" << endl; 
    }
  delete all_nodes;
  delete graph;
  return 0;
}

