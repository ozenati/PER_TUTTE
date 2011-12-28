#ifndef PER_NODE_H
#define PER_NODE_H

#include <list>

typedef struct
{
  float x;
  float y;
}position;


class Per_node
{
 public:
  position pos;
  int id;
  int set;
  std::list<Per_node *> neighbors;

  Per_node();
  Per_node(int id);
  ~Per_node();
  void add_neighbor(Per_node *n);
};

#endif
