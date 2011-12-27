#ifndef CNODE_H
#define CNODE_H

typedef struct
{
  float x;
  float y;
}position;

typedef struct
{
  position pos;
  int id;
  int set;
  list_c *neighbor;
}node_c;

node_c *create_node(position pos);
int add_neighbour(node_c *n1, node_c *n2);
void free_node(node_c *n);

#endif
