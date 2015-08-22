/*
** move.c for 42sh in /home/guervi-a/rendu/Sys_Unix/PSU_2014_42sh
** 
** Made by Alexis Guerville
** Login   <guervi_a@epitech.net>
** 
** Started on  Tue May 19 01:16:07 2015 Alexis Guerville
** Last update Sun May 24 22:50:03 2015 Francois Devos
*/

#include	<stdlib.h>
#include	"line.h"
#include	"lib.h"

extern t_line	*g_line;

int		move_left(void)
{
  if (g_line->pos != 0)
    g_line->pos--;
  return (0);
}

int		move_right(void)
{
  if (g_line->cmd != NULL && g_line->pos != my_strlen(g_line->cmd))
    g_line->pos++;
  return (0);
}

int		move_to_cursor(void)
{
  int		i;

  if (g_line->cmd != NULL)
    {
      i = my_strlen(g_line->cmd);
      while (i > g_line->pos)
	{
	  if (cap("le") == -1)
	    return (-1);
	  i--;
	}
    }
  return (0);
}
