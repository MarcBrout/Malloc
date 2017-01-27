/*
** myMalloc.c for  in /home/brout_m/rendu/system/PSU_2016_malloc/src
** 
** Made by Brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Mon Jan 23 15:43:40 2017 Brout
** Last update Fri Jan 27 14:28:12 2017 Benjamin DUHIEU
*/

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include "mymalloc.h"

static t_node *root = NULL;

t_node *create_node(t_node *next, t_node *prev, size_t size, bool used)
{
  t_node *node;

  if ((node = sbrk(sizeof(t_node) + size)) == (void *) -1)
    return (NULL);
  node->next = next;
  node->prev = prev;
  node->size = size;
  node->used = used;
  return (node);
}

void *set_new_node(t_node *prev, size_t size)
{
  if ((prev->next = create_node(NULL, prev, size, true)) == NULL)
    return (NULL);
  return ((void*)((uintptr_t) prev->next) + sizeof(t_node));
}

void *replace_node(t_node *cur, size_t size)
{
  (void) cur;
  (void) size;
  return (cur);
}

void *add_node(size_t size)
{
  t_node *cur;

  cur = root;
  while (cur->next)
    {
      if (!cur->used && cur->size >= size)
	return (replace_node(cur, size));
      cur = cur->next;
    }
  if (!cur->used && cur->size >= size)
    return (replace_node(cur, size));
  return (set_new_node(cur, size));
}

void *set_root(size_t size)
{
  if ((root = create_node(NULL, NULL, size, true)) == NULL)
    return (NULL);
  return ((void*)((uintptr_t)root + sizeof(t_node)));
}

void free(void *ptr)
{
  t_node *cur;

  //printf("CALLING FREE\n");
  if (ptr)
    {
      cur = root;
      while (cur)
	{
	  //printf("cur->data = %p\n", cur);
	  if ((void*)((uintptr_t)cur + sizeof(t_node)) == ptr)
	    {
	     // printf("free\n");
	      cur->used = false;
	      break;
	    }
	  cur = cur->next;
	}
    }
}

int main()
{
  void *brak = sbrk(0);
  //printf("break = %p\n", brak);
  int *test = malloc(sizeof(int));
  *test = 5;
  //printf("%d\n", *test);
  int *test2 = malloc(sizeof(*test2));
  *test2 = 4;
  //printf("%d\n", *test2);
  int *test3 = malloc(sizeof(*test3) * 2);
  test3[0] = 1;
  test3[1] = 3;
  for (int i = 0; i < 2; i++)
    {
      //printf("test[%d] = %d\n", i, test3[i]);
    }
  //printf("%d\n", *test2);
  //printf("%d\n", *test);
  free(test);
  free(test3);
  free(test2);
  return (0);
}
