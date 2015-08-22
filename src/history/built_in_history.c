/*
** built_in_history.c for built_in_history in /home/devos-f/Documents/Projet/PSU_2014_42sh
** 
** Made by Francois Devos
** Login   <devos_f@epitech.net>
** 
** Started on  Tue May  5 10:47:03 2015 Francois Devos
** Last update Fri Jun  5 16:13:05 2015 devos_f
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<limits.h>
#include	"lib.h"
#include	"list.h"
#include	"history.h"
#include	"mysh.h"

extern t_dlist	*g_history;

/*
** !$
*/

char		**excla_dollar(char **lexed)
{
  t_elem	*tmp;
  int		i;
  int		j;
  char		**cmd;

  i = -1;
  j = -1;
  if ((tmp = g_history->end) == NULL)
    return (NULL);
  if ((cmd = lexing(tmp->data, " \t",
		    (str_to_token("||#|#&&#;#>>#>#<<#<")))) == NULL)
    return (NULL);
  while (cmd[++j]);
  while (lexed[++i])
    {
      if (lexed[i][0] == '!' && lexed[i][1] == '$')
	{
	  if ((lexed[i] = my_strdup(cmd[--j])) == NULL)
	    return (NULL);
	}
    }
  double_free_tab(cmd);
  return (lexed);
}

/*
** !*
*/

char		**excla_star(char **lexed)
{
  t_elem	*tmp;
  char		**tab;
  char		**tab_tmp;
  char		*str;
  int		i;

  if (((tmp = g_history->end) != NULL) && (i = -1))
    {
      str = tmp->data;
      if ((tab_tmp = lexing
	   (str, " \t",(str_to_token("||#|#&&#;#>>#>#<<#<")))) == NULL)
	return (NULL);
      while (tab_tmp[0][++i]);
      if (tab_tmp[1] != NULL)
	{
	if ((tab = create_new_cmd(lexed, str + i)) == NULL)
	  return (NULL);
	}
      else
	return (NULL);
    }
  else
    return (NULL);
  double_free_tab(tab_tmp);
  return (tab);
}

/*
** !10 || !-10
*/

char		**excla_mark_nbr(char **lexed, char *cmd)
{
  long		nbr_line;
  t_elem	*tmp;

  nbr_line = nb_line(cmd);
  if (nbr_line < INT_MIN || nbr_line > INT_MAX)
    return (NULL);
  if (nbr_line < 0)
    nbr_line = nbr_line * -1;
  if (cmd[1] == '-')
    {
      if (g_history->length < nbr_line || nbr_line == 0)
	return (NULL);
      tmp = g_history->end;
      while (--nbr_line > 0 && tmp != NULL)
	tmp = tmp->prev;
    }
  else
    {
      if (g_history->length < nbr_line || nbr_line == 0)
	return (NULL);
      tmp = g_history->start;
      while (--nbr_line > 0 && tmp != NULL)
	tmp = tmp->next;
    }
  return (create_new_cmd(lexed, tmp->data));
}

/*
** !text
*/

char		**excla_mark_text(char **lexed)
{
  t_elem	*tmp;
  char		*str;
  int		i;

  if ((tmp = g_history->end) == NULL)
    return (NULL);
  while (tmp != NULL)
    {
      i = 0;
      str = tmp->data;
      while (lexed[i])
	{
	  if (lexed[i][0] == '!')
	    {
	      if (my_strcmp(str, lexed[i] + 1) == 0 ||\
		  my_strncmp(str, lexed[i] + 1, my_strlen(lexed[i] + 1)) == 0)
		return (create_new_cmd(lexed, tmp->data));
	    }
	  i++;
	}
      tmp = tmp->prev;
    }
  return (NULL);
}

/*
** !?text
*/

char		**excla_inter_mark_text(char **lexed)
{
  char		**tab;
  t_elem	*tmp;
  int		i;
  int		j;

  tmp = g_history->end;
  while (tmp != NULL && (j = -1))
    {
      while (lexed[++j])
	if (lexed[j][0] == '!' && (i = -1))
	  {
	    if ((tab = lexing(tmp->data, " \t", NULL)) == NULL)
	      return (NULL);
	    while (tab[++i])
	      if (my_strcmp(tab[i], lexed[j] + 2) == 0 ||\
		  my_strncmp(tab[i], lexed[j] + 2,\
			     my_strlen(lexed[j] + 2)) == 0)
		{
		  double_free_tab(tab);
		  return (create_new_cmd(lexed, tmp->data));
		}
	  }
      tmp = tmp->prev;
    }
  return (NULL);
}
