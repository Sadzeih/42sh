/*
** my_cd_getcwd_listcat.c for 42sh in /home/desrum_m/code/epitech/S2/PSU/42sh/PSU_2014_42sh
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.eu>
** 
** Started on  ven. mai 15 13:11:09 2015 Martin Desrumaux
** Last update ven. mai 15 13:11:09 2015 Martin Desrumaux
*/

#include		<stdlib.h>
#include		"lib.h"
#include		"list.h"

char			*list_strcat(t_list *list)
{
  char			*absolute_path;
  t_list		*tmp;
  int			i;

  i = 0;
  tmp = list;
  while (tmp != NULL)
  {
    i += my_strlen(tmp->data);
    tmp = tmp->next;
  }
  if ((absolute_path = malloc(sizeof(char) * (i + 1))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  absolute_path[0] = '\0';
  tmp = list;
  while (tmp != NULL)
  {
    absolute_path = my_strcat(absolute_path, (char*)tmp->data);
    tmp = tmp->next;
  }
  i = my_strlen(absolute_path);
  absolute_path[i == 1 ? i : (i - 1)] = '\0';
  return (absolute_path);
}
