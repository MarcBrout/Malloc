/*
** page.c for page in /home/duhieu_b/SystemeUnix/PSU_2016_malloc/src
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 14:26:01 2017 Benjamin DUHIEU
** Last update Fri Jan 27 18:37:22 2017 Brout
*/

#include <stdint.h>
#include <unistd.h>
#include "mymalloc.h"

extern t_page *root;

t_page *create_page(t_page *next, int size, int size_left)
{
  t_page *node;

  if ((node = sbrk(size)) == (void *) -1)
	return (NULL);
  node->next = next;
  node->size = size;
  node->size_left = size_left;
  create_node(&node->root, NULL, size - size_left, true);
  return (node);
}

t_page *create_big_page(t_page *next, int size, int size_left)
{
  t_page *node;

  if ((node = sbrk(size)) == (void *) -1)
	return (NULL);
  node->next = next;
  node->size = size;
  node->size_left = size_left;
  create_node(&node->root, NULL, size - sizeof(t_page), true);
  return (node);
}

void *set_node_page(size_t size, t_page **node)
{
  if (size + sizeof(t_page) > getpagesize())
    {
      if ((*node = create_big_page(NULL, size + sizeof(t_page), 0)) == NULL)
	return NULL;
    }
  else
    {
      if ((*node = create_page(NULL, getpagesize(), getpagesize() - size)) == NULL)
	return NULL;
    }
  return ((void *)((uintptr_t)(*node) + sizeof(t_page)));
}
 
void *add_page(size_t size)
{
  t_page *tmp;
  t_page *new_page;
  void *pos;
  
  tmp = root;
  while (tmp->next)
    {
      if (tmp->size_left > size)
	{
	  if ((pos = add_node(&tmp->root, size, tmp->size)) == NULL)
	    {
	      tmp = tmp->next;
	      continue;
	    }
	  return pos;
	}
      tmp = tmp->next;
    }
  if (tmp->size_left > size)
    {
      if ((pos = add_node(&tmp->root, size, tmp->size)) == NULL)
	{
	  pos = set_node_page(size, &new_page);
	  tmp->next = new_page;
	}
    }
  else
    {
      pos = set_node_page(size, &new_page);
      tmp->next = new_page;
    }
  return (pos);
}

void *malloc(size_t size)
{
  t_page *tmp;

  size += size % sizeof(long);
  if (!root)
    return (set_node_page(size, &root));
  return (add_page(size)); 
}

void free(void *ptr)
{
  t_page *tmp;

  tmp = root;
  while (tmp && !free_node(&tmp->root, ptr))
    {
      tmp = tmp->next;
    }
}

/*
int main()
{
	int *test = malloc(sizeof(int));
	t_node *node = malloc(sizeof(t_node) * 1000);
	char *str = malloc(sizeof(char) * 10);

	*test = 10;
	node->next = NULL;
	node->size = 10;
	node->used = false;

	free(node);
	int *test2 = malloc(sizeof(int));
	*test2 = 13;
	str[0] = '0';
	str[1] = '1';
	str[2] = '2';
	str[3] = '3';
	str[4] = '4';
	str[5] = '5';
	str[6] = '6';
	str[7] = '7';
	str[8] = '8';
	str[9] = '9';
	int *test3 = malloc(sizeof(int));

	free(test);
	free(test2);
	free(str);
	return (0);
}
*/
