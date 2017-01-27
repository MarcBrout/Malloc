/*
** myMalloc.c for  in /home/brout_m/rendu/system/PSU_2016_malloc/src
** 
** Made by Brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Mon Jan 23 15:43:40 2017 Brout
** Last update Fri Jan 27 23:47:27 2017 Brout
*/

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include "mymalloc.h"

t_page *root = NULL;

t_node		*create_node(t_node *cur, t_node *next,
			     size_t size, bool used)
{
  //  write(1, "AAC\n", 4);
  // putHexa((uintptr_t) &cur->next, "0123456789ABCDEF");
  cur->next = next;
  //  write(1, "AAD\n", 4);
  cur->size = size;
  //  write(1, "AAE\n", 4);
  cur->used = used;
  //  write(1, "AAF\n", 4);
  return (cur);
}

static void	*set_new_node(t_node *cur, size_t size)
{
  //  write(1, "AAA\n", 4);
  cur->next =
    create_node((t_node*)(((uintptr_t)cur) + sizeof(t_node) + cur->size),
		NULL, size, true);
  //  write(1, "AAB\n", 4);
  //  putHexa((uintptr_t)sbrk(0), "0123456789ABCDEF");
  //  write(1, "\n", 1);
  //  putHexa(((uintptr_t) cur->next), "0123456789ABCDEF");
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
  acc = 24;
  while (cur->next && acc < totalSize)
    {
      if (!cur->used && cur->size > size)
	return (replace_node(cur, size));
      acc += cur->size + sizeof(t_node);
      cur = cur->next;
    }
  if (!cur->used && cur->size > size)
    return (replace_node(cur, size));
  //  write(1, "totalSize = ", 12);
  // putHexa(totalSize, "0123456789");
  // write(1, "\n", 1);
  //  write(1, "add_node = ", 11);
  //  putHexa(size, "0123456789");
  //  write(1, "\n", 1);
  //  write(1, "acc = ", 6);
  //  putHexa(acc, "0123456789");
  //  write(1, "\n", 1);
  if (totalSize - acc > size + sizeof(t_node) * 2)
    return (set_new_node(cur, size));
  //  write(1, "NULL\n", 5);
  return (NULL);
}

void		*malloc(size_t size)
{
  show_alloc_mem(); 
  //  putHexa(size, "0123456789");
  //  write(1, "\n", 1);
  size += size % sizeof(long);
  if (!root)
    return (set_node_page(size, &root));
  return (add_page(size)); 
}
