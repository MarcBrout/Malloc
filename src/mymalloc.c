/*
** myMalloc.c for  in /home/brout_m/rendu/system/PSU_2016_malloc/src
** 
** Made by Brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Mon Jan 23 15:43:40 2017 Brout
** Last update Fri Jan 27 15:44:31 2017 Brout
*/

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include "mymalloc.h"

static t_node *root = NULL;

t_node		*create_node(t_node *cur, t_node *next,
			     size_t size, bool used)
{
  cur->next = next;
  cur->size = size;
  cur->used = used;
  return (cur);
}

void		*set_new_node(t_node *cur, size_t size)
{
  if ((cur->next =
       create_node((t_node*)((uintptr_t)cur) + sizeof(t_node) + cur->size),
       NULL, size, true)) == NULL)
    return (NULL);
  return ((void*)((uintptr_t) cur->next) + sizeof(t_node));
}

void		*replace_node(t_node *cur, size_t size)
{
  t_node	*new;
  
  cur->used = true;
  if (cur->size > size &&
      cur->size - size > sizeof(t_node) + sizeof(long))
    {
      new =
	create_node((t_node*)(((uintptr_t)cur) + sizeof(t_node) + size),
		    cur->next, cur->size - size - sizeof(t_node), false);
      cur->size = size;
      cur->next = new;
    }
  return ((void*)((uintptr_t) cur) + sizeof(t_node));
}

void		*add_node(t_node *start, size_t size, size_t totalSize)
{
  t_node	*cur;
  size_t	acc;

  cur = start;
  acc = 0;
  while (cur->next && acc < totalSize)
    {
      if (!cur->used && cur->size >= size)
	return (replace_node(cur, size));
      acc += cur->size + sizeof(t_node);
      cur = cur->next;
    }
  if (!cur->used && cur->size >= size)
    return (replace_node(cur, size));
  if (totalSize - acc >= size)
    return (set_new_node(cur, size));
  return (NULL);
}

void *set_root(size_t size)
{
  if ((root = create_node(NULL, size, true)) == NULL)
    return (NULL);
  return ((void*)((uintptr_t)root + sizeof(t_node)));
}

void *malloc(size_t size)
{
  size += size % sizeof(long);
  if (!root)
    return (set_root(size));
  return (add_node(size));
}

bool		free_node(t_node *start, void *ptr)
{
  t_node	*cur;

  cur = start;
  while (cur)
    {
      if ((void*)((uintptr_t)cur + sizeof(t_node)) == ptr)
	{
	  cur->used = false;
	  return (true);
	}
      cur = cur->next;
    }
  return (false);
}

int main()
{
  void *brak = sbrk(0);
  int *test = malloc(sizeof(int));
  *test = 5;
  int *test2 = malloc(sizeof(*test2));
  *test2 = 4;
  int *test3 = malloc(sizeof(*test3) * 2);
  test3[0] = 1;
  test3[1] = 3;
  free(test);
  free(test3);
  free(test2);
  return (0);
}
