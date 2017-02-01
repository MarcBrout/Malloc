/*
** mycalloc.c for mymalloc in /home/brout_m/rendu/system/PSU_2016_malloc
** 
** Made by marc brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Sun Jan 29 11:45:05 2017 marc brout
** Last update Wed Feb  1 12:56:31 2017 Brout
*/

#include <string.h>
#include <stddef.h>
#include "mymalloc.h"

void		*calloc(size_t nmemb, size_t size)
{
  char		*data;

  data = malloc(nmemb * size);
  if (!data)
      return (NULL);
  memset(data, 0, nmemb * size);
  return (data);
}
