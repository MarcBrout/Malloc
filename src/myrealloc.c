/*
** myrealloc.c for myrealloc in /home/duhieu_b/SystemeUnix/PSU_2016_malloc
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 17:54:00 2017 Benjamin DUHIEU
** Last update Wed Feb  1 16:43:20 2017 Brout
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

  getPage = cur;
  while (getPage->prev)
     getPage = getPage->prev;
  page = (t_page*)((uintptr_t)getPage - (sizeof(t_page) - sizeof(t_node)));
  val = replace_node(cur, size, page);
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

static void	*realloc_node(void *ptr, t_node *node, size_t size)
{
  void		*cpy;
  
  pthread_mutex_lock(&mutex);
  if (size < node->size)
    {
      pthread_mutex_unlock(&mutex);
      return (change_ptr(node, size));
    }
  pthread_mutex_unlock(&mutex);
  if ((cpy = malloc(size)) == NULL)
    return (NULL);
  pthread_mutex_lock(&mutex);
  memmove(cpy, ptr, node->size);
  pthread_mutex_unlock(&mutex);
  if (ptr)
    free(ptr);
  return (cpy);
}

void		*realloc(void *ptr, size_t size)
{
  t_node	*node;

  pthread_mutex_lock(&mutex);
  if (ptr && !check_ptr(ptr))
    {
      pthread_mutex_unlock(&mutex);
      return (ptr);
    }
  node = ((t_node*)((uintptr_t)ptr - sizeof(t_node)));
  if (!size)
    {
      pthread_mutex_unlock(&mutex);
      if (ptr)
	free(ptr);
      return (NULL);
    }
  if (ptr && node->size != size)
    {
      pthread_mutex_unlock(&mutex);
      return (realloc_node(ptr, node, size));
    }
  else if (!ptr)
    {
      pthread_mutex_unlock(&mutex);
      return (malloc(size));
    }
  pthread_mutex_unlock(&mutex);
  return (ptr);
}
