/*
** page.c for page in /home/duhieu_b/SystemeUnix/PSU_2016_malloc/src
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 14:26:01 2017 Benjamin DUHIEU
** Last update Fri Jan 27 16:00:50 2017 Benjamin DUHIEU
*/

#include "mymalloc.h"
#include <stdint.h>
#include <unistd.h>

static t_page *root = NULL;

t_page *create_page(t_page *next, int size, int size_left)
{
  t_page *node;

  if ((node = sbrk(size)) == (void *) -1)
	return (NULL);
  node->next = next;
  node->size = size;
  node->size_left = size_left;
  create_node(&node->root, NULL, size - size_left, true);
  return (node);
}

t_page *create_big_page(t_page *next, int size, int size_left)
{
  t_page *node;

  if ((node = sbrk(size)) == (void *) -1)
	return (NULL);
  node->next = next;
  node->size = size;
  node->size_left = size_left;
  create_node(&node->root, NULL, size - sizeof(t_page), true);
  return (node);
}

void *set_root_page(size_t size, t_page *node)
{
  if (size + sizeof(t_page) > getpagesize())
    {
      if ((node = create_big_page(NULL, size + sizeof(t_page), 0)) == NULL)
	return NULL;
    }
  else
    {
      if ((node = create_page(NULL, getpagesize(), getpagesize() - size)) == NULL)
	return NULL;
    }
  return ((void *)((uintptr_t)node + sizeof(t_page)));
}

void *add_page(size_t size)
{
  t_page *tmp;
  t_page *new_page;
  void *pos;

  tmp = root;
  while (tmp->next)
    {
      if (tmp->size_left > size)
	{
	  if ((pos = add_node(tmp->root, size, tmp->size)) == NULL)
	    {
	      tmp = tmp->next;
	      continue;
	    }
	  return pos;
	}
      tmp = tmp->next;
    }
  if (tmp->size_left > size)
    {
      if ((pos = add_node(tmp->root, size, tmp->size)) == NULL)
	{
	  pos = set_node_page(size, new_node);
	  tmp->next = new_node;
	}
      else
	return pos;
    }
}

void *malloc(size_t size)
{
  t_page *tmp;

  size += size % sizeof(long);
  if (!root)
    return (set_node_page(size, root));
  return (add_page(size));
}

void free(void *ptr)
{
  t_page *tmp;

  tmp = root;
  while (tmp && !free_node(tmp->root, ptr))
    {
      tmp = tmp->next;
    }
}
