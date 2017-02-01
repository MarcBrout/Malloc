/*
** myrealloc.c for myrealloc in /home/duhieu_b/SystemeUnix/PSU_2016_malloc
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 17:54:00 2017 Benjamin DUHIEU
** Last update Wed Feb  1 13:16:15 2017 Brout
*/

#include <string.h>
#include <stdint.h>
#include "mymalloc.h"

pthread_mutex_t	mutex;

static void	*change_ptr(t_node *cur, size_t size)
{
  t_node	*getPage;
  t_page	*page;
  void		*val;
  
  getPage = cur;
  while (getPage->prev)
    getPage = getPage->prev;
  page = (t_page*)((uintptr_t)getPage - (sizeof(t_page) - sizeof(t_node)));
  pthread_mutex_lock(&mutex);
  val = replace_node(cur, size, page);
  pthread_mutex_unlock(&mutex);
  return (val);
}

void		*realloc(void *ptr, size_t size)
{
  t_node	*node;
  void		*cpy;

  node = ((t_node*)((uintptr_t)ptr - sizeof(t_node)));
  if (!size)
    {
      if (ptr)
	free(ptr);
      return (NULL);
    }    
  if (ptr && node->size != size)
    {
      if (size < node->size)
	return (change_ptr(node, size));
      else
	{
	  if ((cpy = malloc(size)) == NULL)
	    return (NULL);
	  if (ptr)
	    free (ptr);
	  return (memmove(cpy, ptr, node->size));
	}
    }
  else if (!ptr)
    return (malloc(size));
  return (ptr);
}
