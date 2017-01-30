/*
** page.c for page in /home/duhieu_b/SystemeUnix/PSU_2016_malloc/src
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 14:26:01 2017 Benjamin DUHIEU
** Last update Sun Jan 29 13:40:35 2017 marc brout
*/

#include <stdint.h>
#include <unistd.h>
#include "mymalloc.h"

t_page *root;

static t_page	*create_page(t_page *next, int size, int size_left)
{
  t_page	*node;

  if ((node = sbrk(size)) == (void *) -1)
	return (NULL);
  node->next = next;
  node->size = size;
  node->size_left = size_left;
  create_node(&node->root, NULL, size - size_left, true);
  return (node);
}

static t_page	*create_big_page(t_page *next, int size, int size_left)
{
  t_page	*node;

  if ((node = sbrk(size)) == (void *) -1)
	return (NULL);
  node->next = next;
  node->size = size;
  node->size_left = size_left;
  create_node(&node->root, NULL, size - sizeof(t_page), true);
  return (node);
}

void		*set_node_page(size_t size, t_page **node)
{
  if (size + sizeof(t_page) > (size_t) getpagesize())
    {
      if ((*node = create_big_page(NULL, size + sizeof(t_page), 0)) == NULL)
	return NULL;
    }
  else
    {
      if ((*node = create_page(NULL, getpagesize(), getpagesize() - size - sizeof(t_page))) == NULL)
	return NULL;
    }
  return ((void *)((uintptr_t)(*node) + sizeof(t_page)));
}
 
void		*add_page(size_t size)
{
  t_page	*tmp;
  t_page	*new_page;
  void		*pos;
  
  tmp = root;
  write(1, "sbrk(0) = ", 10);
  putHexa((uintptr_t)(sbrk(0)), "0123456789ABCDEF");
  write(1, "\n", 1);

  while (tmp->next)
    {
      if (tmp->size_left > size)
	{
	  write(1, "size = ", 7);
	  putHexa(size, "0123456789");
	  write(1, " ", 1);
	  write(1, "size_left = ", 12);
	  putHexa(tmp->size_left, "0123456789");
	  write(1, "\n", 1);	  
	  if ((pos = add_node(&tmp->root, size, tmp)) == NULL)
	    {
	      tmp = tmp->next;
	      continue;
	    }
	  write(1, "pos = ", 6);
	  putHexa((uintptr_t)pos, "0123456789ABCDEF");
	  write(1, "\n", 1);
	  write(1, "pos->next = ", 12);
	  putHexa((uintptr_t)((t_node*)((uintptr_t)pos + size))->next, "0123456789ABCDEF");
	  write(1, "\n", 1);
	  return pos;
	}
      tmp = tmp->next;
    }
  if (tmp->size_left > size)
    {
      write(1, "size = ", 7);
      putHexa(size, "0123456789");
      write(1, " ", 1);
      write(1, "size_left = ", 12);
      putHexa(tmp->size_left, "0123456789");
      write(1, "\n", 1);	  
      if ((pos = add_node(&tmp->root, size, tmp)) == NULL)
	{
	  write(1, "COUCOU2\n", 8);
	  pos = set_node_page(size, &new_page);
	  tmp->next = new_page;
	}
      write(1, "pos2 = ", 7);
      putHexa((uintptr_t)pos, "0123456789ABCDEF");
      write(1, "\n", 1);
      write(1, "pos2->next = ", 13);
      putHexa((uintptr_t)((t_node*)((uintptr_t)pos + size))->next, "0123456789ABCDEF");
      write(1, "\n", 1);
    }
  else
    {
      pos = set_node_page(size, &new_page);
      tmp->next = new_page;
      write(1, "pos3 = ", 7);
      putHexa((uintptr_t)pos, "0123456789ABCDEF");
      write(1, "\n", 1);
      write(1, "pos3->next = ", 13);
      putHexa((uintptr_t)((t_node*)((uintptr_t)pos + size))->next, "0123456789ABCDEF");
      write(1, "\n", 1);
    }
  return (pos);
}
