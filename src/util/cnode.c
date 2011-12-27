#include <stdlib.h>
#include "list.h"
#include "cnode.h"

node_c *create_node(position pos)
{
  node_c *n = malloc(sizeof(node_c));
  n->pos.x = pos.x;
  n->pos.y = pos.y;
  n->neighbor = create_list();
  return n;
}

int add_neighbour(node_c *n1, node_c *n2)
{
  return add_to_list(n1->neighbor,n2);
}

void free_node(node_c *n)
{
  while(!empty_list(n->neighbor))
    remove_from_list(n->neighbor);
  free(n);
}
