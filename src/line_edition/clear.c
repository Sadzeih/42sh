/*
** clear.c for 42sh in /home/guervi-a/rendu/Sys_Unix/PSU_2014_42sh
** 
** Made by Alexis Guerville
** Login   <guervi_a@epitech.net>
** 
** Started on  Tue May 19 16:18:40 2015 Alexis Guerville
** Last update Sun May 24 22:47:10 2015 Francois Devos
*/

#include	<stdlib.h>
#include	"line.h"
#include	"lib.h"

extern t_line	*g_line;

int		clear_line(void)
{
  if (g_line->cmd != NULL)
    free(g_line->cmd);
  g_line->pos = 0;
  g_line->cmd = NULL;
  return (0);
}

int		clear_start_line(void)
{
  int		i;

  i = g_line->pos;
  while (i > 0)
    {
      del_char();
      i--;
    }
  return (0);
}

int		clear_end_line(void)
{
  int		i;

  i = g_line->pos;
  if (g_line->cmd == NULL)
    return (0);
  while (g_line->cmd[i] != '\0')
    g_line->cmd[i++] = '\0';
  return (0);
}

int		clear_scrn(void)
{
  if (cap("cl") == -1)
    return (-1);
  my_putstr("> ");
  return (0);
}

int		clear_display(void)
{
  static int	length = 0;
  int		i;

  if (cap("dl") == -1)
    return (-1);
  if (g_line->cmd != NULL)
    {
      if (my_strlen(g_line->cmd) < length)
	i = ((my_strlen(g_line->cmd) + 2) / get_width()) + 1;
      else
	i = (my_strlen(g_line->cmd) / get_width()) + 1;
      length = my_strlen(g_line->cmd);
      while (--i > 0)
	{
	  if (cap_multi_line() == -1)
	    return (-1);
	}
      if (cap("sc") == -1)
	return (-1);
    }
  my_putstr("> ");
  if (g_line->cmd != NULL)
    my_putstr(g_line->cmd);
  return (0);
}
