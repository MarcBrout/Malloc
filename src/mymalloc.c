/*
** myMalloc.c for  in /home/brout_m/rendu/system/PSU_2016_malloc/src
** 
** Made by Brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Mon Jan 23 15:43:40 2017 Brout
** Last update Mon Jan 23 19:00:50 2017 Brout
*/

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include "mymalloc.h"

t_node *create_node(t_node *next, t_node *prev, size_t size, bool used)
{
  t_node *node;

  if ((node = sbrk(sizeof(t_header) + size)) == (void *) -1)
    return (NULL);
  node->header.next = next;
  node->header.prev = prev;
  node->header.size = size;
  node->header.used = used;
  return (node);
}

void set_data_addr_of(t_node *addr)
{
  uintptr_t value;

  value = (uintptr_t) addr;
  printf("value = %u\n", value);
  printf("addr = %d\n", (uintptr_t) addr);
  value += sizeof(t_header);
  printf("addr + value = %u\n", value);
  addr->data = (void *) value;
}

void *set_new_node(t_node *prev, size_t size)
{
  t_node *node;
  
  if ((node = create_node(NULL, prev, size, true)) == NULL)
    return (NULL);
  set_data_addr_of(node);
  return (node);
}

void *replace_node(t_node *cur, size_t size)
{
  (void) cur;
  (void) size;
  return (cur);
}

void *add_node(t_node *roo, size_t size)
{
  t_node *cur;

  cur = roo;
  while (cur->header.next)
    {
      if (!cur->header.used && cur->header.size >= size)
	return (replace_node(cur, size));
      cur = cur->header.next;
    }
  if (!cur->header.used && cur->header.size >= size)
    return (replace_node(cur, size));
  return (set_new_node(cur, size));
}

void *set_root(t_node **roo , size_t size)
{
  if ((*roo  = create_node(NULL, NULL, size, true)) == NULL)
    return (NULL);
  set_data_addr_of(*roo);
  return ((*roo)->data);
}

static t_node *root = NULL;

void *malloc(size_t size)
{
  size += size % sizeof(long);
  if (!root)
    return (set_root(&root, size));
  return (add_node(root, size));
}

void free(void *ptr)
{
  t_node *cur;

  printf("ptr = %p\n", ptr);
  if (ptr)
    {
      cur = root;
      while (cur)
	{
	  printf("cur->data = %p\n", cur->data);
	  if (cur->data == ptr)
	    {
	      printf("free\n");
	      cur->header.used = false;
	      break;
	    }
	  cur = cur->header.next;
	}
    }
}

int main()
{
  int *test = malloc(sizeof(*test));
  *test = 5;
  printf("%d\n", *test);
  int *test2 = malloc(sizeof(*test2));
  *test2 = 4;
  printf("%d\n", *test2);
  int *test3 = malloc(sizeof(*test3) * 2);
  test3[0] = 1;
  test3[1] = 3;
  for (int i = 0; i < 2; i++)
    {
      printf("test[%d] = %d\n", i, test3[i]); 
    }
  printf("%d\n", *test2);
  printf("%d\n", *test);
  free(test);
  free(test2);
  free(test3);
  return (0);
}
