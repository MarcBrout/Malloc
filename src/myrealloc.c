/*
** myrealloc.c for myrealloc in /home/duhieu_b/SystemeUnix/PSU_2016_malloc
** 
** Made by Benjamin DUHIEU
** Login   <duhieu_b@epitech.net>
** 
** Started on  Fri Jan 27 17:54:00 2017 Benjamin DUHIEU
** Last update Fri Jan 27 18:23:38 2017 Benjamin DUHIEU
*/

#include <string.h>
#include "mymalloc.h"

void	*realloc(void *ptr, size_t size)
{
  void	*cpy;

  cpy = malloc(size);
  cpy = memcpy(cpy, ptr, size);
  free(ptr);
  return (cpy);
}
