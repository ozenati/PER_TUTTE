#include <stdlib.h>
#include "list.h"

list_c *create_list(void)
{
  list_c *l = malloc(sizeof(list_c));
  l->first = NULL;
  l->last = NULL;
  return l;
}

int empty_list(list_c *l)
{
  return l->first == l->last && l->first == NULL;
}

int add_to_list(list_c *l, void *elt)
{
  pair *p = malloc(sizeof(pair));
  p->elt = elt;
  p->next = l->first;
  l->first = p;
  if(empty_list(l))
    l->last = p;
  return 0;
}

int add_to_end_list(list_c *l, void *elt)
{
  pair *p = malloc(sizeof(pair));
  p->elt = elt;
  p->next = NULL;
  l->last->next = p;
  return 0;
}

void *remove_from_list(list_c *l)
{
  if(empty_list(l))
    return NULL;
  pair *p = l->first;
  l->first = p->next;
  void *ret = p->elt;
  free(p);
  return p;
}
