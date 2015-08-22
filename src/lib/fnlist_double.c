/*
** fnlist_double.c for fnlist_double in /home/devos-f/Documents/Projet/PSU_2014_42sh/src/lib
** 
** Made by Francois Devos
** Login   <devos_f@epitech.net>
** 
** Started on  Tue May  5 09:13:48 2015 Francois Devos
** Last update Mon May 18 17:00:13 2015 Francois Devos
*/

#include	<stdlib.h>
#include	"lib.h"
#include	"list.h"

t_dlist		*make_list(void)
{
  t_dlist	*list;

  if ((list = malloc(sizeof(t_dlist))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  list->start = NULL;
  list->end = NULL;
  list->length = 0;
  return (list);
}

t_elem		*init_elem(void *data)
{
  t_elem	*elem;

  if ((elem = malloc(sizeof(t_elem))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  elem->prev = NULL;
  elem->next = NULL;
  elem->data = data;
  return (elem);
}

void		add_elem(t_dlist *list, t_elem *elem)
{
  if (list->length == 0)
    {
      list->start = elem;
      list->end = elem;
      list->length++;
      return;
    }
  elem->prev = list->end;
  list->end->next = elem;
  list->end = elem;
  list->length++;
}

void		add_elem_first(t_dlist *list, t_elem *elem)
{
  if (list->length == 0)
    {
      list->start = elem;
      list->end = elem;
      list->length++;
      return;
    }
  elem->prev = NULL;
  elem->next = list->start;
  list->start->prev = elem;
  list->start = elem;
  list->length++;
}
