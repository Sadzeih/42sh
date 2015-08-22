/*
** exec_alias.c for exec_alias.c in /home/thomas/rendu/PSU/PSU_2014_42sh/src/aliases
** 
** Made by raout_t
** Login   <thomas@epitech.net>
** 
** Started on Sat May 23 13:50:49 2015 raout_t
** Last update Sun May 24 22:26:31 2015 raout_t
*/

#include		<stdlib.h>
#include		"lib.h"
#include		"aliases.h"

extern t_aliases	*g_aliases;

char			**insert_alias(char **new_cmd, char **cmd, int *curr)
{
  int			i;

  i = 0;
  while (cmd[i] != NULL)
    {
      if ((new_cmd[*curr] = my_strdup(cmd[i])) == NULL)
	return (NULL);
      (*curr)++;
      i++;
    }
  return (new_cmd);
}

char			**build_new_command(t_aliases *tmp, char **lexed, int i)
{
  char			**new_command;
  int			len_cmd;
  int			curr;
  int			j;

  j = -1;
  curr = 0;
  len_cmd = (size_dtab(lexed) - 1) + size_dtab(tmp->cmd);
  if ((new_command = malloc(sizeof(char *) * (len_cmd + 1))) == NULL)
    return (NULL);
  while (lexed[++j] != NULL)
    {
      if (curr == i)
	{
	  if ((new_command = insert_alias(new_command,\
					  tmp->cmd, &curr)) == NULL)
	    return (NULL);
	}
      else
	if ((new_command[curr++] = my_strdup(lexed[j])) == NULL)
	  return (NULL);
    }
  new_command[curr] = NULL;
  return (new_command);
}

char			**replace_alias(char **lexed, int i)
{
  t_aliases		*tmp;
  char			**new_command;

  tmp = g_aliases;
  while (tmp != NULL && my_strcmp(lexed[i], tmp->alias))
    tmp = tmp->next;
  if (tmp == NULL)
    return (lexed);
  if ((new_command = build_new_command(tmp, lexed, i)) == NULL)
    return (NULL);
  return (new_command);
}

char			**check_alias(char **lexed)
{
  int			i;

  i = 0;
  while (lexed[i] != NULL)
    {
      if (search_alias(lexed[i]) == 0)
	{
	  if ((lexed = replace_alias(lexed, i)) == NULL)
	    return (NULL);
	}
      i++;
    }
  return (lexed);
}
