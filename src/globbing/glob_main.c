/*
** glob_main.c for glob_main in /home/devos-f/Documents/Projet/PSU_2014_42sh/src/globbing
** 
** Made by Francois Devos
** Login   <devos_f@epitech.net>
** 
** Started on  Tue May 19 21:48:48 2015 Francois Devos
** Last update Fri Jun  5 15:34:53 2015 devos_f
*/

#include	<stdlib.h>
#include	"list.h"
#include	"lib.h"
#include	"globbing.h"
#include	"mysh.h"

int		not_found(char **lexed, int ret, char *cmd, char *str)
{
  int		i;
  int		pos;

  i = 0;
  pos = 0;
  while (lexed[i])
    {
      if (my_strcmp(lexed[i], cmd) == 0)
	pos = i;
      i++;
    }
  if (pos == 0)
    my_putstrerr(lexed[pos]);
  else
    my_putstrerr(lexed[pos - 1]);
  my_putstrerr(":");
  my_putstrerr(" ");
  my_putstrerr(str);
  return (ret);
}

int		add_in_list(char *cmd, t_dlist *list)
{
  t_elem	*elem;

  if ((elem = init_elem(cmd)) == NULL)
    return (-1);
  add_elem(list, elem);
  return (0);
}

void		free_dlist(t_dlist *list)
{
  t_elem	*elem;

  elem = list->start;
  if (elem == NULL)
    {
      free(list);
      return ;
    }
  if (elem->next == NULL)
    {
      //free(elem->data);
      free(list);
      return ;
    }
  while (elem->next != NULL)
    {
      elem = elem->next;
      //free(elem->prev->data);
      free(elem->prev);
    }
  free(list);
}

char		*recup_env(char ***env, char *cmd)
{
  char		*tmp;
  char		*ret;

  if ((tmp = my_parsenv(*env, cmd)) == NULL)
    return (NULL);
  if ((ret = my_strdup(tmp)) == NULL)
    return (NULL);
  return (ret);
}

char		**globbing(char **lexed, char ***env)
{
  t_dlist	*list;
  int		i;
  int		j;
  int		token;

  if ((list = make_list()) == NULL)
    return (NULL);
  if (check_dleft(lexed) == 1)
    return (lexed);
  i = -1;
  while (lexed[++i] && (j = -1))
    {
      token = 0;
      while (lexed[i][++j] && token == 0)
	{
	  if ((check_sign(lexed[i][j]) == 0 || lexed[i][0] == '$'
	      || lexed[i][0] == '~') && (token = 1))
	      if ((scan_tab(list, lexed, i, env)) == -1)
	      return (NULL);
	}
      if (token == 0)
	if (add_in_list(lexed[i], list) == -1)
	  return (NULL);
    }
  return (dlist_to_tab(list));
}
