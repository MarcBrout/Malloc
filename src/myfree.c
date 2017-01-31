/*
** myfree.c for free in /home/duhieu_b/SystemeUnix/PSU_2016_malloc
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 18:02:44 2017 Benjamin DUHIEU
** Last update Tue Jan 31 10:46:27 2017 marc brout
*/

#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include "mymalloc.h"

t_page			*root;
pthread_mutex_t		mutex;

static bool	page_is_free(t_page *toFree)
{
  t_node	*cur;

  cur = &toFree->root;
  while (cur)
    {
      if (cur->used)
	return false;
      cur = cur->next;
    }
  return true;
}

static void	node_fuse(t_page *start, t_node *cur)
{
  cur->used = false;
  start->size_left += cur->size;
  if (cur->prev && !cur->prev->used)
    {
      cur->prev->size += cur->size + sizeof(t_node);
      cur->prev->next = cur->next;
      if (cur->next)
	cur->next->prev = cur->prev;
      cur = cur->prev;
      start->size_left += sizeof(t_node);
    }
  if (cur->next && !cur->next->used)
    {
      cur->size += sizeof(t_node) + cur->next->size;
      cur->next = cur->next->next;
      if (cur->next)
	  cur->next->prev = cur;
      start->size_left += sizeof(t_node);
    }
}

static bool	free_node(t_page *start, void *ptr)
{
  t_node	*cur;
  
  cur = &start->root;
  while (cur)
    {
      if ((void*)((uintptr_t)cur + sizeof(t_node)) == ptr)
	{
	  node_fuse(start, cur);
	  return (true);
	}
      cur = cur->next;
    }
  return (false);
}
  
void		free(void *ptr)
{
  t_page	*tmp;

  pthread_mutex_lock(&mutex);
  tmp = root;
  while (tmp && !free_node(tmp, ptr))
    {
      tmp = tmp->next;
    }
  if (!tmp->next && page_is_free(tmp))
    {
      sbrk(-tmp->size);
    }
  pthread_mutex_unlock(&mutex);
}
