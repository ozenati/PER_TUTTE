#ifndef TOOLKIT_H
#define TOOLKIT_H


#include <iostream>

#include <cmath>

#include <tulip/Graph.h>
#include <tulip/Vector.h>
#include <tulip/LayoutProperty.h>
#include <tulip/GlyphManager.h>

#include "MyNode.h"

using namespace std;
using namespace tlp;

// Hack 
class MyNode_ver2 {
 public:
  node n;
  bool mobile;
  int index_neighbourhood;
  int degre;
};

vector<MyNode> * convertGraph2Vector(Graph * graph);

void tutte(vector<MyNode> * MyNodes, double eps);

void tutte_2(vector<MyNode_ver2> * MyNodes_2, vector<int> * Neighbourhoods,
	     vector<Vec2f> * coords, double eps);

void convertVector2Graph(vector<MyNode> * MyNodes, Graph * graph);

void convertGraph2Vector_ver2(Graph * grille, vector<MyNode_ver2> * MyNodes_2, 
			      vector<int> * Neighbourhoods, vector<Vec2f> * coords);

void convertVector_ver2_2Graph(vector<MyNode_ver2> * MyNodes_2, vector<Vec2f> * coords, Graph * grille);

#endif
