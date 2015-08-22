/*
** my_lexer_general.c for lexer in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Mon Jan 26 01:44:41 2015 Martin Desrumaux
** Last update Sun May 24 16:59:20 2015 Alexis Guerville
*/

#include		<stdlib.h>
#include		"lib.h"
#include		"list.h"

int			calc_list_size(t_list *list)
{
  int			list_size;

  list_size = 0;
  while (list != NULL)
  {
    list_size++;
    list = list->next;
  }
  return (list_size);
}

char			**list_to_doubletab(t_list *list)
{
  int			list_size;
  char			**doubletab;
  int			i;

  i = 0;
  list_size = calc_list_size(list);
  if ((doubletab = malloc(sizeof(char*) * (list_size + 1))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  while (list != NULL)
  {
    if ((doubletab[i] = malloc(sizeof(char) * my_strlen(list->data) + 1)) \
	== NULL)
      return (print_and_return_ptr(NULL, "Malloc failed.\n"));
    doubletab[i][0] = '\0';
    doubletab[i] = my_strcat(doubletab[i], (char*)list->data);
    list = list->next;
    i++;
  }
  doubletab[i] = NULL;
  return (doubletab);
}

int			malloc_cat_putlist_token(char *str, int i, \
						 t_list **list)
{
  char			*token;

  if ((token = malloc(sizeof(char) * (i + 1))) == NULL)
    return (print_and_return_int(-1, "Malloc failed.\n"));
  token[0] = '\0';
  token = my_strncat(token, str, i);
  if (my_put_in_list_end(list, token) == -1)
    return (-1);
  return (0);
}
