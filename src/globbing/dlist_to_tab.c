/*
** dlist_to_tab.c for dlist_to_tab in /home/devos-f/Documents/Projet/PSU_2014_42sh
** 
** Made by devos_f
** Login   <devos-f@epitech.net>
** 
** Started on Fri Jun  5 11:48:54 2015 devos_f
** Last update Fri Jun  5 15:31:42 2015 devos_f
*/

#include	<stdlib.h>
#include	"list.h"
#include	"lib.h"
#include	"globbing.h"

char		**dlist_to_tab(t_dlist *list)
{
  char		**ret;
  t_elem	*elem;
  int		i;

  elem = list->start;
  if ((ret = malloc(sizeof(char *) * (list->length + 1))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  i = 0;
  while (elem != NULL)
    {
      if ((ret[i] = my_strdup(elem->data)) == NULL)
	return (NULL);
      elem = elem->next;
      i++;
    }
  ret[i] = NULL;
  free_dlist(list);
  return (ret);
}
