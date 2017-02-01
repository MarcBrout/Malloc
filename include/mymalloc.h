/*
1;4402;0c** mymalloc.h in /home/brout_m/rendu/system/PSU_2016_malloc/src
** 
** Made by Brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Mon Jan 23 15:48:38 2017 Brout
** Last update Wed Feb  1 10:01:23 2017 Benjamin DUHIEU
*/

#ifndef MYMALLOC_H_
# define MYMALLOC_H_

# include <pthread.h>
# include <stddef.h>
# include <stdbool.h>

typedef struct s_node	t_node;

struct			s_node
{
  size_t		size;
  bool			used;
  t_node		*next;
  t_node		*prev;
};

typedef struct		s_page
{
  struct s_page		*next;
  size_t		size;
  size_t		size_left;
  t_node		root;
}			t_page;

extern t_page		*root;
extern pthread_mutex_t	mutex;

/*
** src/mymalloc.c
*/
t_node	*create_node(t_node *cur, t_node *next, size_t size, bool used);
void	*add_node(size_t size, t_page *page);
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

/*
** src/show_alloc_mem.c
*/
void	show_alloc_mem();
void	putHexa(size_t, char const * const);

/*
** src/myrealloc.c
*/
void	*realloc(void *ptr, size_t size);

/*
** src/mycalloc.c
*/
void	*calloc(size_t nmemb, size_t size);

#endif /* MYMALLOC_H_ */
