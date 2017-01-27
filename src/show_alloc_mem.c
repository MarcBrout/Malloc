/*
** show_alloc_mem.c in /home/brout_m/rendu/system/PSU_2016_malloc/src
** 
** Made by Brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Fri Jan 27 17:53:14 2017 Brout
** Last update Fri Jan 27 22:01:01 2017 Brout
*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"

extern t_page *   root;

static void putHexa(size_t nb, char *str)
{
  if (nb / strlen(str))
    putHexa(nb / strlen(str), str);
  write(1, &str[nb % strlen(str)], 1);
}

static void printNode(t_node *node)
{
  write(1, "0x", 2);
  putHexa((uintptr_t)node, "0123456789ABCDEF");
  write(1, " - 0x", 5);
  putHexa((uintptr_t)((uintptr_t)(node) +
		      sizeof(t_node) + node->size), "0123456789ABCDEF");
  write(1, " : ", 3);
  putHexa(sizeof(t_node) + node->size, "0123456789");
  write(1, " bytes\n", 7);
}

void show_alloc_mem()
{
  t_page *curPage;
  t_node *curNode;

  write(1, "break : 0x", 10);
  putHexa((uintptr_t)sbrk(0), "0123456789ABCDEF");
  write(1, "\n", 1);
  curPage = root;
  while (curPage)
    {
      curNode = &curPage->root;
      while (curNode)
	{
	  if (curNode->used)
	    printNode(curNode);
	  curNode = curNode->next;
	}
      curPage = curPage->next;
    }
}
