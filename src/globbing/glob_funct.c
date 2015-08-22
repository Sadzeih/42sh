/*
** glob.c for glob in /home/devos-f/Documents/Projet/PSU_2014_42sh
** 
** Made by Francois Devos
** Login   <devos_f@epitech.net>
** 
** Started on  Tue May 19 17:16:33 2015 Francois Devos
** Last update Fri Jun  5 16:41:21 2015 devos_f
*/

#include	<stdlib.h>
#include	<glob.h>
#include	"lib.h"
#include	"list.h"
#include	"mysh.h"
#include	"globbing.h"
#include	"scripting.h"

extern t_vars	*g_vars;

int		create_glob(char **lexed, t_dlist *list, char *cmd)
{
  glob_t	globbuf;
  int		i;
  char		*tmp;

  if ((glob(cmd, 0, NULL, &globbuf)) != 0)
    return (not_found(lexed, -1, cmd, "No match.\n"));
  i = 0;
  while (i < (int)globbuf.gl_pathc)
    {
      if ((tmp = my_strdup(globbuf.gl_pathv[i])) == NULL)
	return (-1);
      if ((add_in_list(tmp, list)) == -1)
	return (-1);
      i++;
    }
  globfree(&globbuf);
  return (0);
}

int		create_glob_local(t_dlist *list, char *cmd)
{
  t_vars	*tmp;
  char		*str;

  tmp = g_vars;
  while (tmp != NULL)
    {
      if (my_strcmp(cmd + 1, tmp->name) == 0)
	{
	  if ((str = my_strdup(tmp->value)) == NULL)
	    return (-1);
	  if ((add_in_list(str, list)) == -1)
	    return (-1);
	  return (0);
	}
      tmp = tmp->next;
    }
  if (cmd[1] == '\0')
    {
      if ((add_in_list(cmd, list)) == -1)
	return (-1);
      return (0);
    }
  return (-1);
}

int		create_glob_env(char **lexed, t_dlist *list,\
				char *cmd, char ***env)
{
  char		*tmp;
  char		*str;

  if (cmd[0] == '$')
    {
      if ((tmp = recup_env(env, cmd + 1)) != NULL)
	{
	  if ((str = my_strdup(tmp)) == NULL)
	    return (-1);
	  if ((add_in_list(str, list)) == -1)
	    return (-1);
	}
      else if (create_glob_local(list, cmd) == 0)
	return (0);
      else
	return (not_found(lexed, -1, cmd + 1, "Undefined variable.\n"));
    }
  else if (cmd[0] == '~')
    {
      if ((create_glob_env_tilde(list, env)) == -1)
	return (-1);
    }
  return (0);
}

int		create_glob_env_tilde(t_dlist *list, char ***env)
{
  char		*tmp;
  char		*str;

  if ((tmp = recup_env(env, "HOME")) != NULL)
    {
      if ((str = my_strdup(tmp)) == NULL)
	return (-1);
      if ((add_in_list(str, list)) == -1)
	return (-1);
    }
  else
    return (print_and_return_int(-1, "No $home variable set.\n"));
  return (0);
}

int		scan_tab(t_dlist *list, char **lexed,\
			 int pos, char ***env)
{
  int		i;
  int		token;

  i = 0;
  token = 0;
  while (lexed[pos][i] && token == 0)
    {
      if (lexed[pos][i] == '*' || lexed[pos][i] == '?' || lexed[pos][i] == '['
	  || lexed[pos][i] == '{' || lexed[pos][i] == '^')
	{
	  token = 1;
	  if ((create_glob(lexed, list, lexed[pos])) == -1)
	    return (-1);
	}
      else if (lexed[pos][i] == '$' || lexed[pos][i] == '~')
	{
	  token = 1;
	  if ((create_glob_env(lexed, list, lexed[pos], env)) == -1)
	    return (-1);
	}
      i++;
    }
  return (0);
}
