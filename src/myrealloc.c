/*
** myrealloc.c for myrealloc in /home/duhieu_b/SystemeUnix/PSU_2016_malloc
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 17:54:00 2017 Benjamin DUHIEU
** Last update Wed Feb  1 11:49:03 2017 Benjamin DUHIEU
*/

#include <string.h>
#include <stdint.h>
#include "mymalloc.h"

static void	*change_ptr(t_node *cur, size_t size)
{
  t_node	*getPage;
  t_page	*page;

  getPage = cur;
  while (getPage->prev)
    getPage = getPage->prev;
  page = (t_page*)((uintptr_t)getPage - (sizeof(t_page) - sizeof(t_node)));
  return (replace_node(cur, size, page));
}

void		*realloc(void *ptr, size_t size)
{
  t_node	*node;
  void		*cpy;

  node = ((t_node*)((uintptr_t)ptr - sizeof(t_node)));
  if (ptr && node->size != size)
  {
    if (!size)
      {
	free(ptr);
	return (NULL);
      }
    if (size < node->size)
      {
	return (change_ptr(node, size));
      }
    else
      {
	cpy = malloc(size);
	if (!cpy)
	  return (NULL);
	if (ptr)
	  free (ptr);
	return (memcpy(cpy, ptr, node->size));
      }
  }
  else if (size)
    return (malloc(size));
  return (ptr);
}
