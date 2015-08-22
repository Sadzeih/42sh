/*
** lib_bis.c for lib in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Thu Jan 22 19:01:02 2015 Martin Desrumaux
** Last update Thu Jan 22 19:01:05 2015 Martin Desrumaux
*/

#include		"lib.h"

char			*my_strcat(char *dest, char *src)
{
  int			i;
  int			j;

  i = my_strlen(dest);
  j = 0;
  while (src[j])
  {
    dest[i + j] = src[j];
    j++;
  }
  dest[i + j] = '\0';
  return (dest);
}

char			*my_strncat(char *dest, char *src, int nb)
{
  int			i;
  int			j;

  i = my_strlen(dest);
  j = 0;
  while (src[j] && j < nb)
  {
    dest[i + j] = src[j];
    j++;
  }
  dest[i + j] = '\0';
  return (dest);
}

int			my_power_rec(int nb, int power)
{
  if (power == 0)
    return (1);
  if (power == 1)
    return (nb);
  else
    return (nb * my_power_rec(nb, (power - 1)));
}

int			my_strlenalpha(char *str)
{
  int			i;

  i = 0;
  while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    ++i;
  return (i);
}

int			my_getnbr(char *str)
{
  int			ent;
  int			neg;
  int			length;

  ent = 0;
  neg = 0;
  while (*str && (*str == '-' || *str == '+'))
  {
    if (*str == '-')
      neg++;
    str++;
  }
  length = (my_strlenalpha(str) - 1);
  while (*str && length >= 0 && (*str >= '0' && *str <= '9'))
  {
    ent = ent + (*str - '0') * my_power_rec(10, (length));
    ++str;
    --length;
  }
  if (neg % 2 == 1)
    ent = ent * -1;
  return (ent);
}
