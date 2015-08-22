/*
** unset.c for unset.c in /home/thomas/rendu/PSU/PSU_2014_42sh/src_scripting
** 
** Made by raout_t
** Login   <thomas@epitech.net>
** 
** Started on Thu May 21 12:35:49 2015 raout_t
** Last update Sun May 24 16:47:33 2015 Alexis Guerville
*/

#include	<stdlib.h>
#include	"lib.h"
#include	"mysh.h"
#include	"scripting.h"

extern t_vars	*g_vars;

void		free_elem(t_vars *elem)
{
  if (elem != NULL)
    {
      if (elem->name != NULL)
	free(elem->name);
      if (elem->value != NULL)
	free(elem->value);
    }
}

int		unset_var(t_vars *tmp, t_vars *prev, int *check)
{
  (*check)++;
  if (prev == NULL)
    {
      if (g_vars->next == NULL)
	{
	  free_elem(g_vars);
	  g_vars = NULL;
	}
      else
	{
	  prev = g_vars;
	  g_vars = g_vars->next;
	  free_elem(prev);
	}
    }
  else
    {
      prev->next = tmp->next;
      free_elem(tmp);
    }
  return (0);
}

int		my_unset(char ***env, char **lexed)
{
  t_vars	*prev;
  t_vars	*tmp;
  char		*name;
  int		check;

  (void)env;
  check = 0;
  if (lexed[1] == NULL)
    return (print_and_return_int(0, "unset usage: \"unset [name]\"\n"));
  tmp = g_vars;
  prev = NULL;
  name = lexed[1];
  while (tmp != NULL && check == 0)
    {
      if (my_strcmp(tmp->name, name) == 0)
	unset_var(tmp, prev, &check);
      else
	{
	  prev = tmp;
	  tmp = tmp->next;
	}
    }
  return (0);
}
