/*
** my_lexer.c for minishell1 in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Fri Jan 23 02:09:46 2015 Martin Desrumaux
** Last update Fri May 22 17:56:22 2015 Francois Devos
*/

/*
** Transformer pour gérer les "", '' et \ ça sort un seul token
** Transformer pour sortir une liste doublement chainée (mieux pour le 42sh,
** pour gérer le parsing avec arbre binaire) !
*/

#include		<stdlib.h>
#include		"lib.h"
#include		"list.h"
#include		"lexer.h"

char			**str_to_token(char *str)
{
  int			i;
  char			**d_token;
  t_list		*list;

  if ((i = 0) == 0 && (list = NULL) == NULL)
    while (str[i])
      if (str[i] == '#')
      {
	if (malloc_cat_putlist_token(str, i, &list) == -1)
	  return (NULL);
	while (i > 0)
	{
	  i--;
	  str++;
	}
	str++;
      }
      else
	i++;
  if (malloc_cat_putlist_token(str, i, &list) == -1)
    return (NULL);
  if ((d_token = list_to_doubletab(list)) == NULL)
    return (NULL);
  free_list(list);
  return (d_token);
}

char			**lexing(char *str, char *sep, char **token)
{
  t_list		*lexed_list;
  char			**d_lexed;

  if ((lexed_list = lexer(str, sep, token)) == NULL)
    return (NULL);
  if ((d_lexed = list_to_doubletab(lexed_list)) == NULL)
    return (NULL);
  free_list(lexed_list);
  return (d_lexed);
}
