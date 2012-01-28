#ifndef EDGECROSSINGS
#define EDGECROSSINGS

#include <tulip/Graph.h>
#include <tulip/LayoutProperty.h>
#include <tulip/Coord.h>
#include <tulip/ForEach.h>

using namespace tlp;
struct Edge{
  edge e;
  node n_src;
  node n_tgt;
  Coord src;
  Coord tgt;
};

class CompEdges2 {
public :
  CompEdges2(){}
  bool operator()(const Edge e1,const Edge e2){
    bool res;
    if(e1.src[0] < e2.src[0])
      res = true;
    else if(fabs(e1.src[0]-e2.src[0]) < 1E-4){
      if(e1.src[1] < e2.src[1])
	res = true;
      else 
	res = false;
    }
    else 
      res = false;
    return res;
  }
};

int computeNbCrossings(std::vector<Edge> &edges);
int computeNbCrossings(Graph *graph, LayoutProperty * layout);

#endif

