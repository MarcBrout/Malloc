/*
** myfree.c for free in /home/duhieu_b/SystemeUnix/PSU_2016_malloc
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 18:02:44 2017 Benjamin DUHIEU
** Last update Tue Jan 31 11:30:54 2017 Benjamin DUHIEU
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

void				free(void *ptr)
{
  t_page			*tmp;

  pthread_mutex_lock(&mutex);
  tmp = root;
  //  write(1, "FREE!\n", 6);
  while (tmp && !free_node(tmp, ptr))
    {
      tmp = tmp->next;
    }
  while (tmp->next)
    {
      tmp = tmp->next;
    }
  if (page_is_free(tmp))
    {
      sbrk(-tmp->size);
    }
  pthread_mutex_unlock(&mutex);
}

bool		free_node(t_page *start, void *ptr)
{
  t_node	*cur;
  
  cur = &start->root;
  while (cur)
    {
      if ((void*)((uintptr_t)cur + sizeof(t_node)) == ptr)
	{
	  //write(1, "free_size = ", 12);
	  //putHexa((uintptr_t)cur->size, "0123456789");
	  //write(1, "\n", 1);
	  cur->used = false;
	  start->size_left += cur->size;
	  return (true);
	}
      cur = cur->next;
    }
  return (false);
}
