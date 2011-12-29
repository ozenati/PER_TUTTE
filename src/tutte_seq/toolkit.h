#ifndef TOOLKIT_H
#define TOOLKIT_H


#include <iostream>

#include <cmath>

#include <tulip/Graph.h>
//#include <tulip/GraphProperty.h>
#include <tulip/LayoutProperty.h>
#include <tulip/GlyphManager.h>

#include "mynode/MyNode.h"

using namespace std;
using namespace tlp;

vector<MyNode> * convertGraph2Vector(Graph * graph);

void tutte(vector<MyNode> * MyNodes, double eps);

void convertVector2Graph(vector<MyNode> * MyNodes, Graph * graph);

#endif
