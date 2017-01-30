/*
** page.c for page in /home/duhieu_b/SystemeUnix/PSU_2016_malloc/src
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 14:26:01 2017 Benjamin DUHIEU
** Last update Mon Jan 30 16:04:28 2017 marc brout
*/

#include <stdint.h>
#include <unistd.h>
#include "mymalloc.h"

t_page *root;

static t_page	*create_page(size_t size, size_t pageSize)
{
  t_page	*node;

  if ((node = sbrk(pageSize)) == (void *) -1)
	return (NULL);
  node->next = NULL;
  node->size = pageSize;
  node->size_left = pageSize - size - sizeof(t_page);
  create_node(&node->root, NULL, size, true);
  return (node);
}


void		*set_node_page(size_t size, t_page **node)
{
  size_t	realPageSize;

  realPageSize = getpagesize();
  if (size + sizeof(t_page) >= (size_t) realPageSize)
    realPageSize = size + sizeof(t_page);
  if ((*node = create_page(size, realPageSize)) == NULL)
    return NULL;
  return ((void *)((uintptr_t)(*node) + sizeof(t_page)));
}
 
void		*add_page(size_t size)
{
  t_page	*tmp;
  t_page	*new_page;
  void		*pos;
  
  tmp = root;
  //  write(1, "size = ", 7);
  //putHexa(size, "0123456789");
  //write(1, "\n", 1);

  //   if (size == 1024)
  //     __asm__ volatile ("int $3");
  while (tmp->next)
    {
      if (tmp->size_left > size)
	{
	  //	  write(1, "size = ", 7);
	  //	  putHexa(size, "0123456789");
	  //	  write(1, " ", 1);
	  //	  write(1, "size_left = ", 12);
	  //	  putHexa(tmp->size_left, "0123456789");
	  //	  write(1, "\n", 1);	  
	  if ((pos = add_node(&tmp->root, size, tmp)) == NULL)
	    {
	      tmp = tmp->next;
	      continue;
	    }
	  //	  write(1, "pos = ", 6);
	  //	  putHexa((uintptr_t)pos, "0123456789ABCDEF");
	  //	  write(1, "\n", 1);
	  //	  write(1, "pos->next = ", 12);
	  //	  putHexa((uintptr_t)((t_node*)((uintptr_t)pos + size)), "0123456789ABCDEF");
	  //	  write(1, "\n", 1);
	  return pos;
	}
      tmp = tmp->next;
    }
  if (tmp->size_left > size)
    {
      //      write(1, "size = ", 7);
      //      putHexa(size, "0123456789");
      //      write(1, " ", 1);
      //      write(1, "size_left = ", 12);
      //      putHexa(tmp->size_left, "0123456789");
      //      write(1, "\n", 1);	  
      if ((pos = add_node(&tmp->root, size, tmp)) == NULL)
	{
	  //	  write(1, "COUCOU2\n", 8);
	  pos = set_node_page(size, &new_page);
	  tmp->next = new_page;
	}
      //      write(1, "pos2 = ", 7);
      //      putHexa((uintptr_t)pos, "0123456789ABCDEF");
      //      write(1, "\n", 1);
      //      write(1, "pos2->next = ", 13);
      //      putHexa((uintptr_t)((t_node*)((uintptr_t)pos + size)), "0123456789ABCDEF");
      //      write(1, "\n", 1);
    }
  else
    {
      pos = set_node_page(size, &new_page);
      tmp->next = new_page;
      //      write(1, "pos3 = ", 7);
      //      putHexa((uintptr_t)pos, "0123456789ABCDEF");
      //      write(1, "\n", 1);
      //      write(1, "pos3->next = ", 13);
      //      putHexa((uintptr_t)((t_node*)((uintptr_t)pos + size)), "0123456789ABCDEF");
      //      write(1, "\n", 1);
    }
  return (pos);
}
