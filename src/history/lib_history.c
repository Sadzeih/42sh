/*
** lib_history.c for lib_history in /home/devos-f/Documents/Projet/PSU_2014_42sh
** 
** Made by Francois Devos
** Login   <devos_f@epitech.net>
** 
** Started on  Tue May 12 11:25:00 2015 Francois Devos
** Last update Fri Jun  5 15:43:39 2015 devos_f
*/

#include	<stdlib.h>
#include	"lib.h"
#include	"history.h"
#include	"mysh.h"

int		size_dtab(char **tab)
{
  int		i;

  i = 0;
  if (tab == NULL)
    return (0);
  while (tab[i])
    i++;
  return (i);
}

int		nb_line(char *cmd)
{
  unsigned int	nbr_line;

  if (cmd[1] == '-')
    nbr_line = my_getnbr(cmd + 2);
  else
    nbr_line = my_getnbr(cmd + 1);
  return (nbr_line);
}

void		print_lexed(char **lexed)
{
  int		i;

  i = 0;
  while (lexed[i])
    {
      if (lexed[i + 1] != NULL)
	{
	  my_putstr(lexed[i]);
	  my_putstr(" ");
	}
      else
	{
	  my_putstr(lexed[i]);
	  my_putstr("\n");
	}
      i++;
    }
}

char		**create_new_cmd(char **lexed, char *cmd)
{
  char		**new_lex;
  char		**new_cmd;
  int		i;
  int		j;
  int		k;

  if ((new_cmd = lexing
       (cmd, " \t", (str_to_token("||#|#&&#;#>>#>#<<#<")))) == NULL)
    return (NULL);
  if ((new_lex = malloc(sizeof(char *) * (size_dtab(lexed) +
					  size_dtab(new_cmd) + 1))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  i = -1;
  while (lexed[++i] && (j = -1) && (k = -1))
    if (lexed[i][0] != '!')
      {
	if ((new_lex[++j] = my_strdup(lexed[i])) == NULL)
	  return (NULL);
      }
    else
      while (new_cmd[++k])
	if ((new_lex[++j] = my_strdup(new_cmd[k])) == NULL)
	  return (NULL);
  new_lex[++j] = NULL;
  return (new_lex);
}

char		*generate_string(char **lexed)
{
  int		total;
  int		i;
  int		j;
  int		k;
  char		*ret;

  i = -1;
  total = 0;
  while (lexed[++i])
    total = total + (my_strlen(lexed[i]) + 1);
  if ((ret = malloc(sizeof(char) * (total + 1))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  i = -1;
  k = -1;
  while (lexed[++i])
    {
      j = -1;
      while (lexed[i][++j])
	ret[++k] = lexed[i][j];
      ret[++k] = ' ';
    }
  ret[k] = '\0';
  return (ret);
}
