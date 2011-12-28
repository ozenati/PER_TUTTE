#include "Per_node.h"

using namespace std;

Per_node::Per_node()
{
  pos.x = 0;
  pos.y = 0;
  id = 0;
  set = 0;
}

Per_node::Per_node(int id)
{
  pos.x = 0;
  pos.y = 0;
  this->id = id;
  set = 0;
}


Per_node::~Per_node()
{

}

void Per_node::add_neighbor(Per_node *n)
{
  neighbors.push_back(n);
}
