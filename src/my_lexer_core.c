/*
** my_lexer_core.c for lexer in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Mon Jan 26 01:44:30 2015 Martin Desrumaux
** Last update Mon Jan 26 01:44:32 2015 Martin Desrumaux
*/

#include		<stdlib.h>
#include		"lib.h"
#include		"list.h"
#include		"lexer.h"

static char		*move_str(int *i, char *str)
{
  while (*i > 0)
  {
    (*i)--;
    str++;
  }
  return (str);
}

static int		is_sep(char c, char *sep)
{
  int			i;

  i = 0;
  while (sep[i])
  {
    if (c == sep[i])
      return (1);
    i++;
  }
  return (0);
}

static int		is_spec_token(char *str, int *i, char **token, \
				      t_list **list)
{
  int			j;
  int			tmp;
  char			*tmp_str;

  j = 0;
  tmp = *i;
  tmp_str = str;
  tmp_str = move_str(&tmp, tmp_str);
  while (token[j])
  {
    if ((my_strncmp(token[j], tmp_str, my_strlen(token[j])) == 0))
    {
      if (*i != 0)
	if (malloc_cat_putlist_token(str, *i, list) == -1)
	  return (-1);
      if (malloc_cat_putlist_token(token[j], my_strlen(token[j]), list) == -1)
	return (-1);
      tmp = my_strlen(token[j]);
      while (tmp-- > 0)
	(*i)++;
      return (1);
    }
    j++;
  }
  return (0);
}

static char		*do_if_sep(char *str, int *i, t_list **list)
{
  if (*i != 0)
  {
    if (malloc_cat_putlist_token(str, *i, list) == -1)
      return (NULL);
    str = move_str(i, str);
    str++;
  }
  else
    str++;
  return (str);
}

t_list			*lexer(char *str, char *sep, char **token)
{
  t_list		*list;
  int			i;
  int			ret;

  i = 0;
  list = NULL;
  while (str[i])
    if (is_sep(str[i], sep) == 1)
    {
      if ((str = do_if_sep(str, &i, &list)) == NULL)
	return (NULL);
    }
    else if (token != NULL && (ret = is_spec_token(str, &i, token, &list)) == 1)
      str = move_str(&i, str);
    else if (token != NULL && ret == -1)
      return (NULL);
    else
      i++;
  if (i != 0)
  {
    if (malloc_cat_putlist_token(str, i, &list) == -1)
      return (NULL);
    str = move_str(&i, str);
  }
  return (list);
}
