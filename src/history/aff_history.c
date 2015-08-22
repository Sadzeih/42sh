/*
** aff_history.c for aff_history in /home/devos-f/Documents/Projet/PSU_2014_42sh
** 
** Made by Francois Devos
** Login   <devos_f@epitech.net>
** 
** Started on  Wed May  6 15:17:25 2015 Francois Devos
** Last update Sun May 24 22:27:25 2015 raout_t
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"lib.h"
#include	"list.h"

extern t_dlist	*g_history;

static void	my_putnbr(int nb)
{
  char		c;

  if (nb < 0)
    {
      nb = nb * -1;
      write(1, "-", 1);
    }
  if (nb / 10 > 0)
    my_putnbr(nb / 10);
  c = nb % 10 + 48;
  write(1, &c, 1);
}

int		aff_history(char ***env, char **lexed)
{
  int		i;
  char		*str;
  t_elem	*elem;

  (void)env;
  (void)lexed;
  i = 1;
  if (g_history->start == NULL)
    return (print_and_return_int(-1, "History doesn't exist\n"));
  elem = g_history->start;
  while (elem != NULL)
    {
      str = elem->data;
      my_putnbr(i);
      my_putstr("\t");
      my_putstr(str);
      my_putstr("\n");
      i++;
      elem = elem->next;
    }
  return (0);
}
