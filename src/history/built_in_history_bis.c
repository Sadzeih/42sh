/*
** built_in_history_bis.c for built_in_history_bis in /home/devos-f/Documents/Projet/PSU_2014_42sh
** 
** Made by Francois Devos
** Login   <devos_f@epitech.net>
** 
** Started on  Fri May 15 13:19:12 2015 Francois Devos
** Last update Fri Jun  5 15:30:33 2015 devos_f
*/

#include	<stdlib.h>
#include	"lib.h"
#include	"mysh.h"
#include	"history.h"

extern t_dlist	*g_history;

/*
** !!
*/

char		**double_excla_mark(char **lexed)
{
  t_elem	*tmp;
  char		**tab;

  if ((tmp = g_history->end) == NULL)
    return (NULL);
  if (tmp != NULL)
    tab = create_new_cmd(lexed, tmp->data);
  else
    return (NULL);
  return (tab);
}

/*
**!:-
*/

char		**excla_double_point_minus(int nb_word, \
					   char **cmd_tmp, char **lexed)
{
  char		**new_cmd;
  char		*tmp;
  int		i;

  if ((new_cmd = malloc(sizeof(char *) * ((nb_word * -1) + 2))) == NULL)
    return (NULL);
  i = 0;
  while (i <= (nb_word * -1))
    {
      if ((new_cmd[i] = my_strdup(cmd_tmp[i])) == NULL)
	return (NULL);
      i++;
    }
  new_cmd[i] = NULL;
  if ((tmp = generate_string(new_cmd)) == NULL)
    return (NULL);
  double_free_tab(new_cmd);
  return (create_new_cmd(lexed, tmp));
}

/*
** !:
*/

char		**excla_double_point(char **lexed, char *cmd)
{
  int		nb_word;
  t_elem	*tmp;
  char		**cmd_tmp;
  int		i;

  nb_word = my_getnbr(cmd + 2);
  if ((tmp = g_history->end) == NULL ||
       (cmd_tmp = lexing(tmp->data, " \t",
			(str_to_token("||#|#&&#;#>>#>#<<#<")))) == NULL)
    return (NULL);
  if (nb_word >= 0 && nb_word < size_dtab(cmd_tmp) && (i = -1))
    {
      while (lexed[++i])
	if (lexed[i][0] == '!' && lexed[i][1] == ':')
	  {
	    if ((lexed[i] = my_strdup(cmd_tmp[nb_word])) == NULL)
	      return (NULL);
	  }
      return (lexed);
    }
  else if (nb_word < 0 && (nb_word * -1) < size_dtab(cmd_tmp))
    return (excla_double_point_minus(nb_word, cmd_tmp, lexed));
  else
    return (NULL);
}

/*
** main function to check what option history is
*/

char		**my_built_in_history(char **lexed)
{
  char		**ret;
  int		i;

  i = -1;
  ret = NULL;
  while (lexed[++i])
    if (lexed[i][0] == '!')
      {
	if (lexed[i][1] == '!')
	  ret = double_excla_mark(lexed);
	else if (((lexed[i][1] >= '0' && lexed[i][1] <= '9')
		  || lexed[i][1] == '-'))
	  ret = excla_mark_nbr(lexed, lexed[i]);
	else if (lexed[i][1] == '?')
	  ret = excla_inter_mark_text(lexed);
	else if (lexed[i][1] == '*')
	  ret = excla_star(lexed);
	else if (lexed[i][1] == '$' && lexed[i][2] == '\0')
	  ret = excla_dollar(lexed);
	else if (lexed[i][1] == ':')
	  ret = excla_double_point(lexed, lexed[i]);
	else if (lexed[i][1] != '!' && lexed[i][1] != '\0')
	  ret = excla_mark_text(lexed);
      }
  return (ret);
}

/*
** this function check if a '!' is in the cmd and replace this by old cmd
*/

char		**check_history_replacement(char **lexed)
{
  int		i;
  int		check;
  char		**tmp;

  i = -1;
  tmp = NULL;
  check = 0;
  while (lexed[++i])
    if (lexed[i][0] == '!')
      {
	check = 1;
	tmp = my_built_in_history(lexed);
      }
  if (check == 1)
    {
      if (tmp != NULL)
	{
	  print_lexed(tmp);
	  //double_free_tab(lexed);
	}
      return (tmp);
    }
  else
    return (lexed);
}
