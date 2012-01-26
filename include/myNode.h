#ifndef MYNODE_H
#define MYNODE_H

#include <iostream>
#include <sstream>
#include <string>
#include <list>

#include <tulip/Graph.h>
#include <tulip/Coord.h>

using namespace std;
using namespace tlp;

struct nidCompare
{
  bool operator()(const node n1, const node n2) const
  {
    return n1.id < n2.id;
  }
};

class MyNode_ver2 {
 public:
  node n;
  bool mobile;
  int index_neighbourhood;
  int degre;
};

class MyNode {
 private:
  node n;
  bool mobile;
  Coord coord;  
  vector<MyNode *> voisin;

 public:
  MyNode();
  MyNode(const node n, const Coord coord);
  MyNode(const node n, const bool mob, const Coord coord);
  MyNode(const MyNode &n);
  ~MyNode();
  
  const node getNode() const;
  bool getMobile() const;
  void setMobile(const bool b);
  const Coord getCoord() const;
  void setCoord(const Coord &);
  vector<MyNode *> * getVoisin();
  vector<MyNode *> getVoisin() const;
};

std::ostream& operator<<(std::ostream &os, const MyNode &my_n);

/*
 * node data structure for tutte v3 
 */
class Data {
 public:
  node n;
  Coord coord;
  bool mobile;

  Data();
  ~Data();
};
#endif
