/*
** my_built_in_cmd.c for 42sh in /home/desrum_m/code/epitech/S2/PSU/42sh/PSU_2014_42sh/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.eu>
** 
** Started on  ven. mai 22 13:20:41 2015 Martin Desrumaux
** Last update Sun May 24 23:10:53 2015 Francois Devos
*/

#include		<stdlib.h>
#include		"lib.h"
#include		"mysh.h"

int			my_setenv_cmd(char ***env, char **lexed)
{
  int			i;

  if ((i = -1) == -1 && lexed[1] != NULL)
  {
    if (lexed[1][0] != '\0' && lexed[1][0] > 48 && lexed[1][0] < 57)
      return (print_and_return_int(1, \
	      "First character of name can't be a number.\n"));
    while (lexed[1][++i])
      if (!((lexed[1][i] >= 48 && lexed[1][i] <= 57) || \
	  (lexed[1][i] >= 65 && lexed[1][i] <= 90) || \
	  (lexed[1][i] >= 97 && lexed[1][i] <= 122) || lexed[1][i] == '_'))
	return (print_and_return_int(1, "Invalid name.\n"));
    if (lexed[2] == NULL)
    {
      if ((*env = my_setenv(*env, lexed[1], "", 1)) == NULL)
	return (-1);
    }
    else
      if ((*env = my_setenv(*env, lexed[1], lexed[2], 1)) == NULL)
	return (-1);
  }
  else
    my_putstrerr("Missing argument.\n");
  return (0);
}

int			my_unsetenv_cmd(char ***env, char **lexed)
{
  char			*tmp;

  if (lexed[1] != NULL)
  {
    if ((tmp = my_parsenv(*env, lexed[1])) != NULL)
    {
      if ((*env = my_unsetenv(*env, lexed[1])) == NULL)
	return (-1);
    }
    else
      my_putstrerr("Variable doesn't exist.\n");
  }
  else
    my_putstrerr("Missing argument.\n");
  return (0);
}

int			my_cd_cmd(char ***env, char **lexed)
{
  char			*pwd;

  if (lexed[1] == NULL)
    if ((pwd = my_parsenv(*env, "HOME")) != NULL)
    {
      if (my_cd(env, pwd) == -1)
	return (-1);
    }
    else
      my_putstrerr("$HOME doesn't exist.\n");
  else if (lexed[1][0] == '-' && lexed[1][1] == '\0')
  {
    if ((pwd = my_parsenv(*env, "OLDPWD")) != NULL)
    {
      if (my_cd(env, pwd) == -1)
	return (-1);
    }
    else
      my_putstrerr("$OLDPWD doesn't exist.\n");
  }
  else
    if (my_cd(env, lexed[1]) == -1)
      return (-1);
  return (0);
}
