/*
** lib_again.c for lib in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Mon Jan 26 17:33:02 2015 Martin Desrumaux
** Last update Mon Jan 26 17:33:03 2015 Martin Desrumaux
*/

#include		<stdlib.h>
#include		"lib.h"

int			is_a_nbr(char *str)
{
  int			i;

  i = -1;
  while (str[++i] && (str[i] == '+' || str[i] == '-'));
  while (str[i])
  {
    if (str[i] < '0' || str[i] > '9')
      return (1);
    i++;
  }
  return (0);
}

int			my_strcmp(char *s1, char *s2)
{
  int			i;

  i = 0;
  while (s1[i] && s2[i] && s1[i] == s2[i])
    i++;
  if (s1[i] == '\0' && s2[i] == '\0')
    return (0);
  else
    return (1);
}

char			*my_strdup(char *str)
{
  int			i;
  char			*out;

  if ((out = malloc(sizeof(char) * (my_strlen(str) + 1))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  i = -1;
  while (str[++i])
    out[i] = str[i];
  out[i] = '\0';
  return (out);
}

void			double_free_tab(char **tab)
{
  int			i;

  i = 0;
  while (tab[i])
  {
    free(tab[i]);
    i++;
  }
  free(tab);
}

char			**double_strdup(char **tab)
{
  int			i;
  char			**out;

  i = -1;
  while (tab[++i]);
  if ((out = malloc(sizeof(char*) * (i + 1))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  i = 0;
  while (tab[i])
  {
    if ((out[i] = malloc(sizeof(char) * (my_strlen(tab[i]) + 1))) == NULL)
      return (print_and_return_ptr(NULL, "Malloc failed.\n"));
    out[i][0] = '\0';
    my_strcat(out[i], tab[i]);
    i++;
  }
  out[i] = NULL;
  return (out);
}
