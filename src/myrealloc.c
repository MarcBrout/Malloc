/*
** myrealloc.c for myrealloc in /home/duhieu_b/SystemeUnix/PSU_2016_malloc
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 17:54:00 2017 Benjamin DUHIEU
** Last update Wed Feb  1 14:41:35 2017 Brout
*/

#include <string.h>
#include <stdint.h>
#include "mymalloc.h"

pthread_mutex_t	mutex;
t_page		*root;

static void	*change_ptr(t_node *cur, size_t size)
{
  t_node	*getPage;
  t_page	*page;
  void		*val;

  pthread_mutex_lock(&mutex);
  getPage = cur;
  while (getPage->prev)
    getPage = getPage->prev;
  page = (t_page*)((uintptr_t)getPage - (sizeof(t_page) - sizeof(t_node)));
  val = replace_node(cur, size, page);
  pthread_mutex_unlock(&mutex);
  return (val);
}

static bool	check_ptr(t_node *cur)
{
  t_page	*page;
  t_node	*tmp;
  
  page = root;
  while (page)
    {
      tmp = &page->root;
      while (tmp)
	{
	  if ((uintptr_t)tmp + sizeof(t_node) == (uintptr_t)cur)
	    return (true);
	  tmp = tmp->next;
	}
      page = page->next;
    }
  return (false);
}

void		*realloc(void *ptr, size_t size)
{
  t_node	*node;
  void		*cpy;

  if (ptr && size && !check_ptr(ptr))
    return (ptr);
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
	  pthread_mutex_lock(&mutex);
	  memmove(cpy, ptr, node->size);
	  pthread_mutex_unlock(&mutex);
	  if (ptr)
	    free (ptr);
	  return (cpy);
	}
    }
  else if (!ptr)
    return (malloc(size));
  return (ptr);
}
