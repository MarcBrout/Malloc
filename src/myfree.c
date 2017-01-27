/*
** myfree.c for free in /home/duhieu_b/SystemeUnix/PSU_2016_malloc
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 18:02:44 2017 Benjamin DUHIEU
** Last update Fri Jan 27 23:49:55 2017 Brout
*/

#include <unistd.h>
#include <stdint.h>
#include "mymalloc.h"

extern t_page *root;

void		free(void *ptr)
{
  t_page	*tmp;

  tmp = root;
  //  write(1, "FREE!\n", 6);
  while (tmp && !free_node(&tmp->root, ptr))
    {
      tmp = tmp->next;
    }
}

bool		free_node(t_node *start, void *ptr)
{
  t_node	*cur;

  cur = start;
  while (cur)
    {
      if ((void*)((uintptr_t)cur + sizeof(t_node)) == ptr)
	{
	  cur->used = false;
	  return (true);
	}
      cur = cur->next;
    }
  return (false);
}
