/*
** lib.c for src in /home/desrum_m/code/epitech/PSU/my_select/PSU_2014_my_select/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  jeu. déc. 25 18:49:09 2014 Martin Desrumaux
** Last update Sun May 24 17:17:50 2015 Alexis Guerville
*/

#include		<stdlib.h>
#include		<unistd.h>

int			my_strlen(char *str)
{
  char			*tmp;

  tmp = str;
  while (*tmp != '\0')
    tmp++;
  return (tmp - str);
}

void			my_putstr(char *str)
{
  write(1, str, my_strlen(str));
}

int			my_strncmp(char *s1, char *s2, int len)
{
  int			i;

  i = 0;
  while  (i < len && s1[i] == s2[i])
  {
    i++;
  }
  if (i == len)
    return (0);
  else
    return (1);
}

int			tokenlen(char **token)
{
  int			i;

  i = -1;
  while (token[++i] != NULL);
  return (i);
}
