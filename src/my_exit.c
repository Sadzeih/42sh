/*
** my_exit.c for 42sh in /home/desrum_m/code/epitech/S2/PSU/42sh/PSU_2014_42sh/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.eu>
** 
** Started on  ven. mai 15 13:19:52 2015 Martin Desrumaux
** Last update Sun May 24 16:54:00 2015 Alexis Guerville
*/

#include		<stdlib.h>
#include		"list.h"
#include		"globbing.h"
#include		"lib.h"

extern t_dlist		*g_history;

int			my_exit_cmd(char ***env, char **lexed)
{
  int			nbr;

  (void)env;
  nbr = 0;
  if (lexed[1] != NULL)
    {
      if (is_a_nbr(lexed[1]) == 0)
	nbr = (my_getnbr(lexed[1]) % 256);
    }
  free_dlist(g_history);
  my_putstr("exit\n");
  return (nbr - (256 * 2));
}
