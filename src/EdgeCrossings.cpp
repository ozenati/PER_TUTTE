#include <iostream>
#include "EdgeCrossings.h"


using namespace std;
using namespace tlp;

bool smaller(Coord& c, Coord& c2){
    bool res;
    if(c[0] < c2[0])
      res = true;
    else if(fabs(c[0]-c2[0]) < 1E-4){
      if(c[1] < c2[1])
	res = true;
      else 
	res = false;
    }
    else 
      res = false;
    return res;

}

float perp(Coord u, Coord v){
  return  u[0]* v[1]- u[1]*v[0];
}

bool cross(Edge& e1, Edge& e2){
  if(e1.n_src == e2.n_tgt || e1.n_src == e2.n_src || 
     e1.n_tgt == e2.n_src || e1.n_tgt == e2.n_tgt)
    return false;

  Coord v1=e1.src;
  Coord v2=e2.src;
  Coord dir1 = e1.tgt - e1.src;
  Coord dir2 = e2.tgt - e2.src;
  Coord intersection;
  if(fabs((dir1^dir2)[2]) < 1E-4){
    return false;
  }
  

  if(fabs(dir1[0]) < 1E-4){
    double a2 = dir2[1] / dir2[0];
    double b2 = v2[1] - a2 * v2[0];
    intersection[0] = v1[0];
    intersection[1] = a2 * intersection[0] + b2;
  }
  else if(fabs(dir2[0]) < 1E-4){
    double a1 = dir1[1] / dir1[0];
    double b1 = v1[1] - a1 * v1[0];
    intersection[0] = v2[0];
    intersection[1] = a1 * intersection[0] + b1;
  }
  else if (fabs(dir1[1]) < 1E-4){
    double a2 = dir2[1] / dir2[0];
    double b2 = v2[1] - a2 * v2[0];
    intersection[0] = (v1[1] - b2) / a2;
    intersection[1] = v1[1];
  }
  else if (fabs(dir2[1]) < 1E-4){
    double a1 = dir1[1] / dir1[0];
    double b1 = v1[1] - a1 * v1[0];
    intersection[0] = (v2[1] - b1) / a1;
    intersection[1] = v2[1];
  }
  else {
    double a1 = dir1[1] / dir1[0];
    double a2 = dir2[1] / dir2[0];
    double b1 = v1[1] - a1 * v1[0];
    double b2 = v2[1] - a2 * v2[0];
    intersection[0] = (b2 - b1) / (a1 - a2);
    intersection[1] = intersection[0] * a2 + b2;
  }
  intersection[2] = 0.;

  for(unsigned int i = 0; i < 2 ; ++i){
    if(fabs(intersection[i]) < 1E-4)
      intersection[i] = 0.;
    else if(fabs(intersection[i] - v1[i]) < 1E-4)
      intersection[i] = v1[i];
    else if(fabs(intersection[i] - v2[i]) < 1E-4)
      intersection[i] = v2[i];
  }
  
  if(dir1.dotProduct(intersection-v1) > 0. || v1 == intersection){
    // return true;
    double dist1_src = (intersection - v1).norm();
    double dist1_tgt = (intersection - e1.tgt).norm();
    double dist1 = (e1.src - e1.tgt).norm();
    double dist2_src = (intersection - v2).norm();
    double dist2_tgt = (intersection - e2.tgt).norm();
    double dist2 = (e2.src - e2.tgt).norm();
    return (dist1 > dist1_src && dist1_tgt < dist1) && (dist2 > dist2_src && dist2_tgt < dist2);
  }
  return false;
}

int computeNbCrossings(Graph *graph, LayoutProperty * layout){
  vector<Edge> edges(graph->numberOfEdges());
  int i = 0;
  edge e;
  forEach(e, graph->getEdges()){
    Edge E;
    node src = graph->source(e);
    node tgt = graph->target(e);
    E.n_src = src;
    E.n_tgt = tgt;
    Coord c = layout->getNodeValue(src);
    Coord c2 = layout->getNodeValue(tgt);
    
    E.e = e;
    if(c[0] < c2[0]){
      E.src = c;
      E.tgt = c2;
      E.n_src = src;
      E.n_tgt = tgt;
    }
    else if(fabs(c[0]-c2[0]) < 1E-4){
      if(c[1] < c2[1]){
	E.src = c;
	E.tgt = c2;
      }
      else {
	E.src = c2;
	E.tgt = c;
      }
    }
    else {
      E.src = c2;
      E.tgt = c;
    }
    edges[i]= E;
    ++i;
  }
  CompEdges2 cmp;
  sort(edges.begin(),edges.end(),cmp);
  return computeNbCrossings(edges);
}

int computeNbCrossings(vector<Edge> &edges){
  unsigned int cpt=0;
  int nbCrossings = 0;
  for(unsigned int i = 0; i+1 < edges.size(); ++i){
    Edge e1 = edges[i];
    unsigned int j = i+1; 
    while(j < edges.size()){
      ++cpt;
      Edge e2 = edges[j];
      if(smaller(e1.tgt, e2.src)){
	break;
      }
      if(cross(e1,e2)){
	++nbCrossings;
      }
      ++j;
    }
  }
  cout << "NB TEST = " << cpt << endl;
  return nbCrossings;
}

