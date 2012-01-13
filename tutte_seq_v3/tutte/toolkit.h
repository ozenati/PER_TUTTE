#ifndef TOOLKIT_H
#define TOOLKIT_H

#include <iostream>

#include <cmath>

#include <tulip/Graph.h>
#include <tulip/LayoutProperty.h>
#include <tulip/GlyphManager.h>

#include "../structure/MyGraph.h"

using namespace std;
using namespace tlp;

void convertGraph2MyGraph(Graph * graph, MyGraph *my_g);

void tutte(MyGraph *my_g, double eps);

void updateGraphByMyGraph(MyGraph * my_g, Graph * graph);

#endif //TOOLKIT_H
