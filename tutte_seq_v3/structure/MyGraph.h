#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <iostream>
#include <sstream>
#include <string>
#include <list>

#include <tulip/Graph.h>
#include <tulip/Coord.h>

using namespace std;
using namespace tlp;

class Data {
 public:
  node n;
  Coord coord;
  bool mobile;

  Data();
  ~Data();
};

class MyGraph {
 public:
  vector <Data> datas;
  vector <vector<int>*> matrix;

  MyGraph();
  ~MyGraph();
};

std::ostream& operator<<(std::ostream &os, const MyGraph &my_g);
#endif //MyGRAPH_H
