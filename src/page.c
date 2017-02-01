/*
** page.c for page in /home/duhieu_b/SystemeUnix/PSU_2016_malloc/src
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 14:26:01 2017 Benjamin DUHIEU
** Last update Wed Feb  1 16:01:30 2017 Brout
*/

#include <stdint.h>
#include <unistd.h>
#include "mymalloc.h"

t_page *root;

static t_page	*create_page(size_t size, size_t pageSize)
{
  t_page	*node;

  if ((node = sbrk(pageSize)) == (void *) -1)
	return (NULL);
  node->next = NULL;
  node->size = pageSize;
  node->size_left = pageSize - size - sizeof(t_page);
  create_node(&node->root, NULL, size, true);
  return (node);
}

void		*set_node_page(size_t size, t_page **node)
{
  size_t	realPageSize;

  realPageSize = getpagesize();
  if (size + sizeof(t_page) >= (size_t) realPageSize)
    realPageSize = size + sizeof(t_page) + realPageSize -
      ((size + sizeof(t_page)) % realPageSize);
  if ((*node = create_page(size, realPageSize)) == NULL)
    return NULL;
  return ((void *)((uintptr_t)(*node) + sizeof(t_page)));
}

static void	*check_last_node(size_t size, t_page *tmp)
{
  void		*pos;
  t_page	*new_page;

  if (tmp->size_left > size)
    {
      if ((pos = add_node(size, tmp)) == NULL)
	{
	  pos = set_node_page(size, &new_page);
	  tmp->next = new_page;
	}
    }
  else
    {
      pos = set_node_page(size, &new_page);
      tmp->next = new_page;
    }
  return (pos);
}

void		*add_page(size_t size)
{
  t_page	*tmp;
  void		*pos;

  tmp = root;
  while (tmp->next)
    {
      if (tmp->size_left > size)
	{
	  if ((pos = add_node(size, tmp)) == NULL)
	    {
	      tmp = tmp->next;
	      continue;
	    }
	  return (pos);
	}
      tmp = tmp->next;
    }
  return (check_last_node(size, tmp));
}
