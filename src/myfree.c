/*
** myfree.c for free in /home/duhieu_b/SystemeUnix/PSU_2016_malloc
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 18:02:44 2017 Benjamin DUHIEU
** Last update Sun Jan 29 13:49:55 2017 marc brout
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
  while (tmp && !free_node(tmp, ptr))
    {
      tmp = tmp->next;
    }
}

bool		free_node(t_page *start, void *ptr)
{
  t_node	*cur;

  cur = &start->root;
  while (cur)
    {
      if ((void*)((uintptr_t)cur + sizeof(t_node)) == ptr)
	{
	  cur->used = false;
	  start->size_left += cur->size;
	  return (true);
	}
      //      write(1, "cur = ", 6);
      //putHexa((uintptr_t)cur, "0123456789ABCDEF");
      //write(1, "\n", 1);
      cur = cur->next;
    }
  return (false);
}
