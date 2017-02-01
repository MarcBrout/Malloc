/*
** myrealloc.c for myrealloc in /home/duhieu_b/SystemeUnix/PSU_2016_malloc
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 17:54:00 2017 Benjamin DUHIEU
** Last update Wed Feb  1 10:04:46 2017 Brout
*/

#include <string.h>
#include <stdint.h>
#include "mymalloc.h"

void		*realloc(void *ptr, size_t size)
{
  size_t	nodeSize;
  void		*cpy;

  cpy = malloc(size);
  if (ptr && size)
    {
      nodeSize = ((t_node*)((uintptr_t)ptr - sizeof(t_node)))->size;
      if (nodeSize > size)
	nodeSize = size;
      cpy = memcpy(cpy, ptr, nodeSize);
    }
  if (ptr)
    free(ptr);
  return (cpy);
}
