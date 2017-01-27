/*
** myMalloc.c for  in /home/brout_m/rendu/system/PSU_2016_malloc/src
** 
** Made by Brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Mon Jan 23 15:43:40 2017 Brout
** Last update Fri Jan 27 18:44:10 2017 Brout
*/

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include "mymalloc.h"

extern t_page *root;

t_node		*create_node(t_node *cur, t_node *next,
			     size_t size, bool used)
{
  cur->next = next;
  cur->size = size;
  cur->used = used;
  return (cur);
}

static void	*set_new_node(t_node *cur, size_t size)
{
  if ((cur->next =
       create_node((t_node*)(((uintptr_t)cur) + sizeof(t_node) + cur->size),
       NULL, size, true)) == NULL)
    return (NULL);
  return ((void*)((uintptr_t) cur->next) + sizeof(t_node));
}

static void	*replace_node(t_node *cur, size_t size)
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

void		*malloc(size_t size)
{
  t_page	*tmp;

  size += size % sizeof(long);
  if (!root)
    return (set_node_page(size, &root));
  return (add_page(size)); 
}
