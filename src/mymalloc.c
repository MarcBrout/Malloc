/*
** myMalloc.c for  in /home/brout_m/rendu/system/PSU_2016_malloc/src
** 
** Made by Brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Mon Jan 23 15:43:40 2017 Brout
** Last update Tue Jan 31 10:40:37 2017 marc brout
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

  // putHexa((uintptr_t) &cur->next, "0123456789ABCDEF");
  cur->next = next;
  //  write(1, "AAD\n", 4);
  cur->size = size;
  //  write(1, "AAE\n", 4);
  cur->used = used;
  //  write(1, "AAF\n", 4);
  cur->prev = NULL;
  return (cur);
}

static void	*set_new_node(t_node *cur, size_t size, t_page *page)
{
  //  write(1, "AAA\n", 4);
  cur->next =
    create_node((t_node*)(((uintptr_t)cur) + sizeof(t_node) + cur->size),
		NULL, size, true);
  cur->next->prev = cur;
  //  write(1, "NEWNODE\n", 8);
  page->size_left -= sizeof(t_node) + size;
  //  write(1, "AAB\n", 4);
  //  putHexa((uintptr_t)sbrk(0), "0123456789ABCDEF");
  //  write(1, "\n", 1);
  //  putHexa(((uintptr_t) cur->next), "0123456789ABCDEF");
  return ((void*)((uintptr_t) cur->next) + sizeof(t_node));
}

static void	*replace_node(t_node *cur, size_t size, t_page *page)
{
  t_node	*new;

  cur->used = true;
  // write(1, "REPLACE1\n", 9);
  if (cur->size > size)
    {
      //  write(1, "REPLACE2\n", 9);
      if (cur->size - size > sizeof(t_node) + sizeof(long))
	{
	  //  write(1, "REPLACE3\n", 9);
	  new =
	    create_node((t_node*)(((uintptr_t)cur) + sizeof(t_node) + size),
			cur->next, cur->size - size - sizeof(t_node), false);
	  //	  write(1, "new = ", 6);
	  //	  putHexa((uintptr_t)new, "0123456789ABCDEF");
	  // write(1, "\n", 1);
	  cur->size = size;
	  cur->next = new;
	  new->prev = cur;
	  page->size_left -= sizeof(t_node);
	}
    }
  page->size_left -= cur->size;
  return ((void*)((uintptr_t) cur) + sizeof(t_node));
}

void		*add_node(size_t size, t_page *page)
{
  static int	i = 0;
  t_node	*cur;
  //  size_t	acc;
  cur = &page->root;

  ++i;
  //  acc = sizeof(t_page) - sizeof(t_node);
  while (cur->next /*&& acc < page->size*/)
    {
            if (!cur->used && cur->size > size)
      	return (replace_node(cur, size, page));
      
      //      acc += cur->size + sizeof(t_node);
      cur = cur->next;
    }
  //    write(1, "LASTONE\n", 8);
  //  putHexa(totalSize, "0123456789");
  // write(1, "\n", 1);
  //write(1, "acc = ", 6);
  //  putHexa(acc, "0123456789");
  //  write(1, "\n", 1);
  //  write(1, "page->size = ", 13);
  //  putHexa(page->size, "0123456789");
  //  write(1, "\n", 1);
    if (!cur->used && cur->size > size)
      return (replace_node(cur, size, page));
 
  //  write(1, "add_node = ", 11);
  //  putHexa(page->size - ((uintptr_t)cur - (uintptr_t)page), "0123456789");
  //  write(1, " page->size = ", 14);
  //  putHexa(page->size, "0123456789");
  //  write(1, "\n", 1);

  //if (acc < page->size && page->size - acc > size + sizeof(t_node) * 2)
  //  if (i == 24)
  //    __asm__ volatile ("int $3");
  if (((uintptr_t)cur + sizeof(t_node) + cur->size + sizeof(t_node) + size) -
      (uintptr_t)page < page->size)
    return (set_new_node(cur, size, page));

  //  write(1, "NULL\n", 5);
  return (NULL);
}

void				*malloc(size_t size)
{
  pthread_mutex_lock(&mutex);
 //  show_alloc_mem();
  //  write(1, "MALLOC SIZE IN = ", strlen("MALLOC SIZE IN = "));
  //  putHexa(size, "0123456789");
  //  write(1, "\n", 1);
  size = size % sizeof(long) ? size + sizeof(long) - size % sizeof(long) : size;
  //  write(1, "MALLOC SIZE OUT = ", strlen("MALLOC SIZE OUT = "));
  //  putHexa(size, "0123456789");
  //  write(1, "\n", 1);
  //  write(1, "SIZEOF(T_NODE) = ", strlen("SIZEOF(T_NODE) = "));
  //  putHexa(sizeof(t_node), "0123456789");
  //  write(1, "\n", 1);
  if (!root)
    {
      pthread_mutex_unlock(&mutex);
      return (set_node_page(size, &root));
    }
  pthread_mutex_unlock(&mutex);
  return (add_page(size)); 
}
