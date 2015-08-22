/*
** alias.c for alias.c in /home/thomas/rendu/PSU/aliases
** 
** Made by raout_t
** Login   <thomas@epitech.net>
** 
** Started on Fri May 22 15:07:23 2015 raout_t
** Last update Sun May 24 22:30:07 2015 Alexis Guerville
*/

#include		<stdlib.h>
#include		"lib.h"
#include		"mysh.h"
#include		"aliases.h"

extern t_aliases	*g_aliases;

t_aliases		*init_new_alias(char *alias, char **cmd)
{
  t_aliases		*new_alias;

  if ((new_alias = malloc(sizeof(t_aliases))) == NULL)
    return (NULL);
  if ((new_alias->alias = alias) == NULL)
    return (NULL);
  if ((new_alias->cmd = cmd) == NULL)
    return (NULL);
  new_alias->next = NULL;
  return (new_alias);
}

int			set_alias(char *alias, char **cmd)
{
  t_aliases		*tmp;

  tmp = g_aliases;
  if (tmp == NULL)
    {
      if ((g_aliases = init_new_alias(alias, cmd)) == NULL)
	return (-1);
    }
  else
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      if ((tmp->next = init_new_alias(alias, cmd)) == NULL)
	return (print_and_return_int(-1, "Malloc failed."));
    }
  return (0);
}

int			is_an_alias(char *alias, char **cmd)
{
  t_aliases		*tmp;

  tmp = g_aliases;
  while (tmp != NULL)
    {
      if (my_strcmp(tmp->alias, alias) == 0)
	{
	  free(tmp->cmd);
	  if ((tmp->cmd = cmd) == NULL)
	    return (-1);
	  return (1);
	}
      tmp = tmp->next;
    }
  return (0);
}

char			**get_cmd(char **lexed)
{
  char			**token;
  char			*cmd;
  char			**final;
  int			i;

  i = 3;
  if ((cmd = my_strdup(lexed[2])) == NULL)
    return (NULL);
  while (lexed[i] != NULL)
    {
      if ((cmd = my_strcat_char(cmd, lexed[i], ' ')) == NULL)
	return (NULL);
      i++;
    }
  if (i != 0)
    {
      if ((token = str_to_token("||#|#&&#;#>>#>#<<#<")) == NULL)
	return (NULL);
      if ((final = lexing(cmd,  " \t", token)) == NULL)
	return (NULL);
      return (final);
    }
  else
    return (str_to_tab(cmd));
}

int			my_alias(char ***env, char **lexed, int *check)
{
  int			ret;
  char			*alias;
  char			**cmd;

  (void)env;
  (*check)++;
  if (lexed[1] == NULL || lexed[2] == NULL)
    return (print_and_return_int(0,\
				 "alias usage: \"alias [name] [command]\"\n"));
  if (my_strcmp(lexed[1], "alias") == 0 || my_strcmp(lexed[2], "alias") == 0)
    return (print_and_return_int(0, "Mike je t'ai vu venir\n"));
  if ((alias = my_strdup(lexed[1])) == NULL)
    return (-1);
  if ((cmd = get_cmd(lexed)) == NULL)
    return (-1);
  if ((ret = is_an_alias(alias, cmd)) == -1)
    return (-1);
  else if (ret == 0)
    {
      if (set_alias(alias, cmd) == -1)
	return (-1);
    }
  return (1);
}
