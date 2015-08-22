/*
** echo.c for 42sh in /home/guervi-a/rendu/Sys_Unix/PSU_2014_42sh
** 
** Made by Alexis Guerville
** Login   <guervi_a@epitech.net>
** 
** Started on  Wed May 20 17:13:04 2015 Alexis Guerville
** Last update Sun May 24 23:02:19 2015 Francois Devos
*/

#include	<stdlib.h>
#include	"lib.h"

int		my_echo(char ***env, char **lexed)
{
  int		i;
  int		n;

  (void)env;
  i = 1;
  n = 0;
  if (lexed[1] != NULL && my_strcmp("-n", lexed[1]) == 0)
    {
      n = 1;
      i++;
    }
  while (lexed[i] != NULL)
    {
      my_putstr(lexed[i]);
      if (lexed[i + 1] != NULL)
	my_putstr(" ");
      i++;
    }
  if (n == 0)
    my_putstr("\n");
  return (0);
}
