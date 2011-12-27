#ifndef LIST_H
#define LIST_H

struct pair_s
{
  void *elt;
  struct pair_s *next;
};

typedef struct pair_s pair;

typedef struct
{
  pair *first;
  pair *last;
}list_c;

list_c *create_list(void);
int empty_list(list_c *l);
int add_to_list(list_c *l, void *elt);
int add_to_end_list(list_c *l, void *elt);
void *remove_from_list(list_c x*l);

#endif	/* LIST_H */
