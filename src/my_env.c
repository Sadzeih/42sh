/*
** my_env.c for src in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  mar. janv. 20 13:37:00 2015 Martin Desrumaux
** Last update mar. janv. 20 13:37:00 2015 Martin Desrumaux
*/

#include		<stdlib.h>
#include		"lib.h"

char			*after_equal(char *str)
{
  while (*str != '=')
    str++;
  str++;
  return (str);
}

char			*my_parsenv(char **env, char *keyword)
{
  int			i;
  int			len;

  i = -1;
  len = my_strlen(keyword);
  while (env[++i])
  {
    if ((my_strncmp(keyword, env[i], len)) == 0 && env[i][len] == '=')
      return (after_equal(env[i]));
  }
  return (NULL);
}

int			my_env(char **env)
{
  int			i;

  i = -1;
  while (env[++i])
  {
    my_putstr(env[i]);
    my_putstr("\n");
  }
  return (0);
}
