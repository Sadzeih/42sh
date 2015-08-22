/*
** edit.c for 42sh in /home/guervi-a/rendu/Sys_Unix/PSU_2014_42sh
** 
** Made by Alexis Guerville
** Login   <guervi_a@epitech.net>
** 
** Started on  Fri May 15 17:41:25 2015 Alexis Guerville
** Last update Sun May 24 22:48:27 2015 Francois Devos
*/

#include	<stdlib.h>
#include	<signal.h>
#include	"line.h"
#include	"mysh.h"
#include	"lib.h"

extern t_line	*g_line;

int		do_action(int (*keys_actions[15])(void))
{
  int		i;

  i = 0;
  while (i < 15)
    {
      if (g_line->buffer == g_line->keys[i])
	{
	  if (keys_actions[i]() == -1)
	    return (-1);
	  return (0);
	}
      i++;
    }
  if (g_line->buffer > 31 && g_line->buffer < 127)
    {
      if (add_char() == -1)
	return (-1);
    }
  return (0);
}

int		loop_keys(int (*keys_actions[15])(void))
{
  int		ret;

  g_line->buffer = 0;
  while ((ret = read(0, &(g_line->buffer), 3)) > 0)
    {
      if (g_line->buffer == CTRL_D)
	return (1);
      if (g_line->buffer == ENTER)
	return (0);
      if (do_action(keys_actions) == -1)
	return (-1);
      if (clear_display() == -1)
	return (-1);
      if (move_to_cursor() == -1)
	return (-1);
      g_line->buffer = 0;
    }
  return (0);
}

int		line_ret()
{
  if (g_line->cmd == NULL)
    {
      if ((g_line->cmd = malloc(1 * sizeof(char))) == NULL)
	return (print_and_return_int(-1, "Allocation error.\n"));
      g_line->cmd[0] = '\0';
    }
  my_putstr("\n");
  return (0);
}

void		free_line(int code)
{
  (void)code;
  if (g_line->cmd != NULL)
    {
      g_line->cmd[0] = '\0';
      g_line->pos = 0;
    }
  my_putstr("\n> ");
}

char		*line_edition(char **env)
{
  int		(*keys_actions[15])(void);
  int		ret;

  if (isatty(0) == 0)
    return (get_next_line(0));
  if ((g_line = malloc(sizeof(t_line))) == NULL)
    return (print_and_return_ptr(NULL, "Allocation error.\n"));
  if ((ret = get_termcaps(env) == 1) || ret == -1 || (set_termcaps(1) == -1))
    return (get_next_line(0));
  g_line->pos = 0;
  g_line->cmd = NULL;
  signal(SIGINT, &free_line);
  init_actions(keys_actions);
  init_keys();
  ret = loop_keys(keys_actions);
  if (set_termcaps(0) == -1)
    return (NULL);
  if (ret == 0)
    {
      if (line_ret() == -1)
	return (NULL);
      return (g_line->cmd);
    }
  return (NULL);
}
