/*
** fnlist.c for my_ls in /home/desrum_m/rendu/myls/PSU_2014_my_ls
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Thu Nov 27 12:47:40 2014 Martin Desrumaux
** Last update Thu May  7 15:45:23 2015 Alexis Guerville
*/

#include		<stdlib.h>
#include		"lib.h"
#include		"list.h"

int			my_put_in_list_begin(t_list **list, void *str)
{
  t_list		*elem;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (print_and_return_int(-1, "Allocation error\n"));
  if (*list == NULL)
    {
      elem->data = str;
      elem->next = NULL;
      elem->next = NULL;
      *list = elem;
    }
  else
    {
      elem->data = str;
      elem->next = *list;
      elem->next->prev = elem;
      *list = elem;
    }
  return (0);
}

int			my_put_in_list_end(t_list **list, void *str)
{
  t_list		*elem;
  t_list		*tmp;

  tmp = *list;
  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (print_and_return_int(-1, "Allocation error\n"));
  elem->data = str;
  elem->next = NULL;
  elem->prev = NULL;
  if (*list == NULL)
    *list = elem;
  else
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      elem->prev = tmp;
      tmp->next = elem;
    }
  return (0);
}

void			free_list(t_list *list)
{
  t_list		*tmp;

  while (list != NULL)
  {
    tmp = list;
    list = list->next;
    free(tmp->data);
    free(tmp);
  }
}

void			rm_list(t_list **list, t_list **listbegin)
{
  t_list		*tmp;

  tmp = (*list)->next;
  if ((*list)->next != NULL)
    {
      (*list)->data = (*list)->next->data;
      (*list)->next = (*list)->next->next;
      free(tmp);
    }
  else
    {
      if (*listbegin == *list)
	*listbegin = NULL;
      else
	{
	  tmp = *listbegin;
	  while (tmp->next != (*list))
	    tmp = tmp->next;
	  tmp->next = NULL;
	}
      *list = NULL;
    }
}
