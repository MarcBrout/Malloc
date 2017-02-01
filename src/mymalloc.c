/*
** myMalloc.c for  in /home/brout_m/rendu/system/PSU_2016_malloc/src
** 
** Made by Brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Mon Jan 23 15:43:40 2017 Brout
** Last update Wed Feb  1 14:44:29 2017 Benjamin DUHIEU
*/

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include "mymalloc.h"

t_page			*root = NULL;
pthread_mutex_t		mutex = PTHREAD_MUTEX_INITIALIZER;

t_node		*create_node(t_node *cur, t_node *next,
			     size_t size, bool used)
{
  cur->next = next;
  cur->size = size;
  cur->used = used;
  cur->prev = NULL;
  return (cur);
}

static void	*set_new_node(t_node *cur, size_t size, t_page *page)
{
  cur->next =
    create_node((t_node*)(((uintptr_t)cur) + sizeof(t_node) + cur->size),
		NULL, size, true);
  cur->next->prev = cur;
  page->size_left -= sizeof(t_node) + size;
  return ((void*)((uintptr_t) cur->next) + sizeof(t_node));
}

void		*replace_node(t_node *cur, size_t size, t_page *page)
{
  t_node	*new;

  cur->used = true;
  if (cur->size > size)
    {
      if (cur->size - size > sizeof(t_node) + sizeof(long))
	{
	  new =
	    create_node((t_node*)(((uintptr_t)cur) + sizeof(t_node) + size),
			cur->next, cur->size - size - sizeof(t_node), false);
	  cur->size = size;
	  cur->next = new;
	  cur->next->prev = cur;
	  page->size_left -= sizeof(t_node);
	}
    }
  page->size_left -= cur->size;
  return ((void*)((uintptr_t) cur) + sizeof(t_node));
}

void		*add_node(size_t size, t_page *page)
{
  t_node	*cur;

  cur = &page->root;
  while (cur->next)
  {
    if (!cur->used && cur->size > size)
      return (replace_node(cur, size, page));
    cur = cur->next;
  }
  if (!cur->used && cur->size > size)
    return (replace_node(cur, size, page));
  if (((uintptr_t)cur + sizeof(t_node) + cur->size + sizeof(t_node) + size) -
      (uintptr_t)page < page->size)
    return (set_new_node(cur, size, page));
  return (NULL);
}

void		*malloc(size_t size)
{
  void		*val;

  pthread_mutex_lock(&mutex);
  size = size % sizeof(long) ? size + sizeof(long) -
    size % sizeof(long) : size;
  if (!root)
    {
      val = set_node_page(size, &root);
      pthread_mutex_unlock(&mutex);
      return (val);
    }
  val = add_page(size);
  pthread_mutex_unlock(&mutex);
  return (val);
}
