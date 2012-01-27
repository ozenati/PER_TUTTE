#include <iostream>

#include "myNode.h"

using namespace std;
using namespace tlp;

MyNode::MyNode() {
}

MyNode::MyNode(const node n, const Coord coord):mobile(true), voisin(0) {
  this->n = n;
  this->coord = coord;
}

MyNode::MyNode(const node n, const bool mob, const Coord coord):mobile(true), voisin(0) {
  this->n = n;
  this->mobile = mob;
  this->coord = coord;
}

MyNode::MyNode(const MyNode &n) {
  this->n = n.n;
  this->mobile = n.mobile;
  this->coord = n.coord;
  this->voisin = n.getVoisin();
}

MyNode::~MyNode() {
}

const node MyNode::getNode() const {
  return this->n;
}

bool MyNode::getMobile() const {
  return this->mobile;
}

void MyNode::setMobile(const bool b) {
  this->mobile = b;
}

const Coord MyNode::getCoord() const {
  return this->coord;
}

void MyNode::setCoord(const Coord &c) {
  this->coord = c;
}

vector<MyNode *> * MyNode::getVoisin() {
  return &this->voisin;
}

vector<MyNode *> MyNode::getVoisin() const {
  return this->voisin;
}

std::ostream& operator<<(std::ostream &os, const MyNode &my_n) {
  os << "id : " << my_n.getNode().id 
     << " coord : " << my_n.getCoord() 
     << " size_voisin : " << my_n.getVoisin().size();

  vector<MyNode *> voisin = my_n.getVoisin();
  uint size = voisin.size();

  os << " [";
  for(uint i = 0; i < size; i++) {
    os << voisin[i]->getNode().id;
    
    if (i < size - 1)
      os << ", ";
  }
  os << "]";

  return os;
}
