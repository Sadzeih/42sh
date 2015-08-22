/*
** unset.c for unset.c in /home/thomas/rendu/PSU/PSU_2014_42sh/src_scripting
** 
** Made by raout_t
** Login   <thomas@epitech.net>
** 
** Started on Thu May 21 12:35:49 2015 raout_t
** Last update Sun May 24 22:08:36 2015 raout_t
*/

#include		<stdlib.h>
#include		"lib.h"
#include		"mysh.h"
#include		"aliases.h"

extern t_aliases	*g_aliases;

void			free_alias(t_aliases *elem)
{
  int			i;

  i = 0;
  if (elem != NULL)
    {
      if (elem->alias != NULL)
	free(elem->alias);
      if (elem->cmd != NULL)
	{
	  while (elem->cmd[i] != NULL)
	    {
	      free(elem->cmd[i]);
	      i++;
	    }
	  free(elem->cmd);
	}
    }
}

int			unset_alias(t_aliases *tmp, t_aliases *prev, int *check)
{
  (*check)++;
  if (prev == NULL)
    {
      if (g_aliases->next == NULL)
	{
	  free_alias(g_aliases);
	  g_aliases = NULL;
	}
      else
	{
	  prev = g_aliases;
	  g_aliases = g_aliases->next;
	  free_alias(prev);
	}
    }
  else
    {
      prev->next = tmp->next;
      free_alias(tmp);
    }
  return (0);
}

int			my_unalias(char ***env, char **lexed, int *ret)
{
  t_aliases		*prev;
  t_aliases		*tmp;
  char			*alias;
  int			check;

  (void)env;
  (*ret)++;
  check = 0;
  if (lexed[1] == NULL)
    return (print_and_return_int(0, "unset usage: \"unset [name]\"\n"));
  tmp = g_aliases;
  prev = NULL;
  alias = lexed[1];
  while (tmp != NULL && check == 0)
    {
      if (my_strcmp(tmp->alias, alias) == 0)
	unset_alias(tmp, prev, &check);
      else
	{
	  prev = tmp;
	  tmp = tmp->next;
	}
    }
  return (1);
}
