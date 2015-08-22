/*
** lib_error.c for src in /home/desrum_m/code/epitech/S2/PSU/minishell2/PSU_2014_minishell2/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  lun. mars 02 16:58:13 2015 Martin Desrumaux
** Last update lun. mars 02 16:58:13 2015 Martin Desrumaux
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		"lib.h"

void			my_putstrerr(char *str)
{
  write(2, str, my_strlen(str));
}

void			*print_and_return_ptr(void *err, char *str)
{
  write(2, str, my_strlen(str));
  return (err);
}

int			print_and_return_int(int err, char *str)
{
  write(2, str, my_strlen(str));
  return (err);
}
