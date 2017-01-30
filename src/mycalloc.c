/*
** mycalloc.c for mymalloc in /home/brout_m/rendu/system/PSU_2016_malloc
** 
** Made by marc brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Sun Jan 29 11:45:05 2017 marc brout
** Last update Mon Jan 30 13:34:54 2017 marc brout
*/

#include <stddef.h>
#include "mymalloc.h"

void		*calloc(size_t nmemb, size_t size)
{
  char		*data;
  size_t	i;

  data = malloc(nmemb * size);
  if (!data)
    return (NULL);
  i = 0;
  while (i < nmemb * size)
    {
      data[i] = 0;
      ++i;
    }
  return (data);
}
