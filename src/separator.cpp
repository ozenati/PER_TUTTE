#include <iostream>
#include <tulip/Graph.h>
#include <tulip/GlyphManager.h>
#include <tulip/LayoutProperty.h>
#include <tulip/ColorProperty.h>
#include <tulip/Color.h>
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
	  all_nodes->erase(n->getNode().id);
	  z_nodes.erase(n->getNode().id);
	  if(n->getMobile()==false)
	    continue;
	  v->push_back(n);
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
  // Information 
  cout << vectors->size() << " ensembles generé" << endl;
  vector<vector<MyNode *> *>::iterator it;
  int i;
  for (it=vectors->begin(), i = 0 ; it < vectors->end(); it++, i++)
    {
      cout << "Ensemble " << i << " contient " << (*it)->size()  << " elements" << endl;
    }
  return vectors;
}

// vector<vector<MyNode_ver2> *> *
// separateMap2Vectors_ver2(vector<MyNode_ver2> * allNodes, 
// 			 vector<int> * Neighbourhoods, vector<Vec2f> * coords)
// {
//   vector<vector<MyNode *> *> *vectors = new vector<vector<MyNode *> *>;
//   vector<MyNode_ver2> * all_nodes = new vector<MyNode_ver2>(*allNodes);
//   while(!all_nodes->empty())
//     {
//       // map<int, MyNode *> z_nodes;// = *all_nodes;
//       // copy(&z_nodes,all_nodes);
//       vector<MyNode_ver2> z_nodes = *all_nodes:
// 	vector<MyNode_ver2> *v = new vector<MyNode_ver2>;
//       while(!z_nodes.empty())
// 	{
// 	  // map<int, MyNode *>::iterator elt;
// 	  // elt = z_nodes.begin();
// 	  // MyNode *n = elt->second;
// 	  MyNode_ver2 n = *(z_nodes.begin());
// 	  v->push_back(n);
// 	  all_nodes->erase(z_nodes.begin());
// 	  z_nodes.erase(z_nodes.begin());
// 	  // vector<MyNode *> *nv = n->getVoisin();
// 	  // vector<MyNode *>::iterator it;
// 	  // for ( it=nv->begin() ; it < nv->end(); it++ )
// 	  int i;
// 	  for(i = 0; i < n.degree; i++)
// 	    {
// 	      // MyNode *nvm = *it;
// 	      if()
// 	      z_nodes.erase(nvm->getNode().id);
// 	    }
// 	}
//       vectors->push_back(v);
//     }
//   return vectors;
// }


map<int, MyNode *> *
convertGraph2Map(Graph *graph)
{
  Graph *grille = graph->getSubGraph(2);
  if(!grille)
    grille = graph;
  LayoutProperty *layout = graph->getLocalProperty<LayoutProperty>("viewLayout");
  BooleanProperty *fixed = graph->getProperty<BooleanProperty>("fixed nodes");
  BooleanProperty *bordure = graph->getProperty<BooleanProperty>("viewSelection");

  map<int,MyNode *> all_nodes;

  // Boucle sur tous les noeuds
  Iterator<node> *itNodes = grille->getNodes();
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
      Iterator<node> *itN = grille->getInOutNodes(n);
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

  Iterator <edge> *itE = grille->getEdges();
  while (itE->hasNext()) 
    {
      edge current_edge = itE->next();
      if (bordure->getEdgeValue(current_edge)) 
	{
	  pair<node, node> nodes = grille->ends(current_edge);
	  all_nodes[nodes.first.id]->setMobile(false);
	  all_nodes[nodes.second.id]->setMobile(false);  
	}
    }
  delete itE;

  return new map<int, MyNode *>(all_nodes);
}

void applyVectors2Graph(vector<vector<MyNode *> *> *vectors, Graph * graph) {
  LayoutProperty *layout=graph->getLocalProperty<LayoutProperty>("viewLayout");
  ColorProperty *color=graph->getLocalProperty<ColorProperty>("viewColor");  
  vector<vector<MyNode *> *>::iterator it;
  Color couleurs[6];
  couleurs[0] = Color(0,0,255,255);
  couleurs[1] = Color(0,255,0,255);
  couleurs[2] = Color(0,255,255,255);
  couleurs[3] = Color(255,255,0,255);
  couleurs[4] = Color(255,0,255,255);
  couleurs[5] = Color(120,120,120,255);

  int c;
  for (it=vectors->begin(),c = 0; it < vectors->end(); it++,c++)
    {
      // Selection de l'ensemble courant;
      vector<MyNode *> *MyNodes = (*it);
      for(uint i = 0; i < MyNodes->size(); i++) 
	{
	  layout->setNodeValue((* MyNodes)[i]->getNode(), (* MyNodes)[i]->getCoord());
	  color->setNodeValue((* MyNodes)[i]->getNode(), couleurs[c]);
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

