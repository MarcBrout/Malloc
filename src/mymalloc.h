/*
** mymalloc.h in /home/brout_m/rendu/system/PSU_2016_malloc/src
** 
** Made by Brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Mon Jan 23 15:48:38 2017 Brout
** Last update Mon Jan 23 17:14:55 2017 Brout
*/

#ifndef MYMALLOC_H_
# define MYMALLOC_H_

# include <stddef.h>
# include <stdbool.h>

typedef struct s_node	t_node;
typedef struct s_header t_header;

struct			s_header
{
  size_t		size;
  bool			used;
  t_node		*prev;
  t_node		*next;
};

struct			s_node
{
  t_header		header;
  void			*data;
};

#endif /* MYMALLOC_H_ */
