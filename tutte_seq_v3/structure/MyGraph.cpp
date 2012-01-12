#include <iostream>

#include "MyGraph.h"

using namespace std;
using namespace tlp;

MyGraph::MyGraph() {
}

MyGraph::~MyGraph() {
  for(uint i = 0; i < MyGraph::matrix.size(); i++) {
    delete matrix[i];
  }
}

Data::Data() {
}

Data::~Data() {
}

std::ostream& operator<<(std::ostream &os, const MyGraph &my_g) {
  

  vector <Data> datas = my_g.datas;
  vector <vector<int>*> matrix = my_g.matrix; 
  uint size = matrix.size();
  uint size_d = datas.size();

  os << endl << "Datas -> size = " << size_d << endl;
  for(uint i = 0; i < size_d; i++) {
    Data d = datas[i];
    os << "id : " << d.id 
       << " node : " << d.n 
       << " coord : " << d.coord << endl;
  }

  os << endl << "Matrix ->" << "size = " << size << endl;
  for(uint i = 0; i < size; i++) {
    vector<int> voisin =*(matrix[i]);
    uint size_v = voisin.size();
  
    os << "id : " << i << " "; 
    os << " voisins [";
    for(uint j = 0; j < size_v; j++) {
      os << voisin[j] << " ";
    }
    os << "]" << endl; 
  }
  return os;
}
