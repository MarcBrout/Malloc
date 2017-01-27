/*
** mymalloc.h in /home/brout_m/rendu/system/PSU_2016_malloc/src
** 
** Made by Brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Mon Jan 23 15:48:38 2017 Brout
** Last update Fri Jan 27 18:46:21 2017 Brout
*/

#ifndef MYMALLOC_H_
# define MYMALLOC_H_

# include <stddef.h>
# include <stdbool.h>

typedef struct s_node	t_node;

struct			s_node
{
  size_t		size;
  bool			used;
  t_node		*next;
};

typedef struct		s_page
{
  struct s_page		*next;
  int			size;
  int			size_left;
  t_node		root;
}			t_page;

static t_page *root = NULL;

/*
** src/mymalloc.c
*/
t_node	*create_node(t_node *cur, t_node *next, size_t size, bool used);
void	*add_node(t_node *start, size_t size, size_t totalSize);
void	*malloc(size_t size);

/*
** src/page.c
*/
void	*set_node_page(size_t size, t_page **node);
void	*add_page(size_t size);

/*
** src/myfree.c
*/
void	free(void *ptr);
bool	free_node(t_node *start, void *ptr);

/*
** src/show_alloc_mem.c
*/
void	show_alloc_mem();

/*
** src/myrealloc.c
*/
void	*realloc(void *ptr, size_t size);

#endif /* MYMALLOC_H_ */
