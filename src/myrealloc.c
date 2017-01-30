/*
** myrealloc.c for myrealloc in /home/duhieu_b/SystemeUnix/PSU_2016_malloc
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 17:54:00 2017 Benjamin DUHIEU
** Last update Mon Jan 30 14:51:23 2017 marc brout
*/

#include <string.h>
#include "mymalloc.h"

void	*realloc(void *ptr, size_t size)
{
  void	*cpy;

  cpy = malloc(size);
  if (ptr && size)
    cpy = memcpy(cpy, ptr, size);
  if (ptr)
    free(ptr);
  return (cpy);
}
