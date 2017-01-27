/*
** myrealloc.c for myrealloc in /home/duhieu_b/SystemeUnix/PSU_2016_malloc
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 17:54:00 2017 Benjamin DUHIEU
** Last update Sat Jan 28 00:04:13 2017 Brout
*/

#include <string.h>
#include "mymalloc.h"

void	*realloc(void *ptr, size_t size)
{
  void	*cpy;

  if (size)
    cpy = malloc(size);
  if (ptr && size)
    cpy = memcpy(cpy, ptr, size);
  if (ptr)
    free(ptr);
  return (cpy);
}
