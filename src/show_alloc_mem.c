/*
** show_alloc_mem.c in /home/brout_m/rendu/system/PSU_2016_malloc/src
** 
** Made by Brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Fri Jan 27 17:53:14 2017 Brout
** Last update Fri Jan 27 18:31:32 2017 Brout
*/

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include "mymalloc.h"

extern t_page * root;

static void printNode(t_node const * const node)
{
  printf("%p - %p : %u bytes\n", node, (void*)((const uintptr_t)(node) +
					       sizeof(t_node) + node->size),
	 sizeof(t_node) + node->size);
}

void show_alloc_mem()
{
  t_page *curPage;
  t_node *curNode;
  
  printf("break : %X\n", sbrk(0));
  curPage = root;
  while (curPage)
    {
      curNode = &curPage->root;
      while (curNode)
	{
	  printNode(curNode);
	  curNode = curNode->next;
	}
      curPage = curPage->next;
    }
}
