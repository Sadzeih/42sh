/*
** add_del_char.c for 42sh in /home/guervi-a/rendu/Sys_Unix/PSU_2014_42sh
** 
** Made by Alexis Guerville
** Login   <guervi_a@epitech.net>
** 
** Started on  Mon May 18 16:56:07 2015 Alexis Guerville
** Last update Sun May 24 22:45:20 2015 Francois Devos
*/

#include	<stdlib.h>
#include	<string.h>
#include	"line.h"
#include	"mysh.h"
#include	"lib.h"

extern t_line	*g_line;

int		add_char(void)
{
  int		i;

  if (g_line->cmd == NULL)
    {
      if ((g_line->cmd = malloc(2 * sizeof(char))) == NULL)
	return (print_and_return_int(-1, "Allocation error.\n"));
      g_line->cmd[0] = g_line->buffer;
      g_line->cmd[1] = '\0';
    }
  else
    {
      if ((g_line->cmd = realloc(g_line->cmd,\
				 (my_strlen(g_line->cmd) + 2))) == NULL)
	return (-1);
      bzero(g_line->cmd + my_strlen(g_line->cmd), 2);
      i = my_strlen(g_line->cmd);
      while (i > 0 && i > g_line->pos)
	{
	  g_line->cmd[i] = g_line->cmd[i - 1];
	  i--;
	}
      g_line->cmd[i] = g_line->buffer;
    }
  g_line->pos++;
  return (0);
}

int		del_char(void)
{
  int		i;

  if (g_line->cmd != NULL && g_line->pos > 0)
    {
      i = g_line->pos - 1;
      while (g_line->cmd[i] != '\0')
	{
	  g_line->cmd[i] = g_line->cmd[i + 1];
	  i++;
	}
      g_line->cmd[i] = '\0';
      if ((g_line->cmd = realloc(g_line->cmd, sizeof(char) *\
			       (my_strlen(g_line->cmd) + 1))) == NULL)
	return (-1);
      g_line->pos--;
    }
  return (0);
}
