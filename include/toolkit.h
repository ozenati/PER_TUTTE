#ifndef TOOLKIT_H
#define TOOLKIT_H

#include <iostream>

#include <cmath>

#include <tulip/Graph.h>
#include <tulip/Vector.h>
#include <tulip/LayoutProperty.h>
#include <tulip/GlyphManager.h>

#include "myNode.h"
#include "separator.h"

using namespace std;
using namespace tlp;

vector<MyNode> * convertGraph2Vector(Graph * graph);

void convertVector2Graph(vector<MyNode> * MyNodes, Graph * graph);

void convertGraph2Vector_ver2(Graph * grille, vector<MyNode_ver2> * MyNodes_2, 
			      vector<int> * Neighbourhoods, vector<Vec2f> * coords);

void convertVector_ver2_2Graph(vector<MyNode_ver2> * MyNodes_2, vector<Vec2f> * coords, Graph * grille);

void convertGraph_v3(Graph * grille, vector<Data>* datas, vector<vector<int> >* matrix);

void updateGraph_v3(Graph * grille, vector<Data>* datas);

#endif
