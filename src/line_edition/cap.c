/*
** cap.c for 42sh in /home/guervi-a/rendu/Sys_Unix/PSU_2014_42sh
** 
** Made by Alexis Guerville
** Login   <guervi_a@epitech.net>
** 
** Started on  Tue May 12 18:26:55 2015 Alexis Guerville
** Last update Sun May 24 22:46:22 2015 Francois Devos
*/

#include	<curses.h>
#include	<term.h>
#include	<stdlib.h>
#include	<string.h>
#include	"line.h"
#include	"lib.h"

int		cap(char *str)
{
  char		*tmp;

  tmp = NULL;
  if (str == NULL || (tmp = tgetstr(str, NULL)) == NULL)
    {
      if (set_termcaps(0) == -1)
	return (-1);
      return (print_and_return_int(-1, "Termcap not available.\n"));
    }
  my_putstr(tmp);
  if (strcmp("dl", str) == 0)
    {
      if ((tmp = tgetstr("cr", NULL)) == NULL)
	{
	  if (set_termcaps(0) == -1)
	    return (-1);
	  return (print_and_return_int(-1, "Termcap not available.\n"));
	}
      my_putstr(tmp);
    }
  return (0);
}

int		get_width(void)
{
  int		ret;

  if ((ret = tgetnum("co")) == -1)
    return (print_and_return_int(-1, "Termcap not available.\n"));
  return (ret);
}
