/*
** termcaps.c for 42sh in /home/guervi-a/rendu/Sys_Unix/PSU_2014_42sh
** 
** Made by Alexis Guerville
** Login   <guervi_a@epitech.net>
** 
** Started on  Tue May 12 20:09:45 2015 Alexis Guerville
** Last update Sun May 24 22:52:33 2015 Francois Devos
*/

#include	<termios.h>
#include	<term.h>
#include	<curses.h>
#include	"line.h"
#include	"mysh.h"
#include	"lib.h"

extern t_line	*g_line;

int		get_termcaps(char **env)
{
  char		*term;

  if ((term = my_parsenv(env, "TERM")) == NULL)
    return (1);
  if (tgetent(NULL, term) < 0)
    return (-1);
  if (tcgetattr(0, &(g_line->save)) < 0 || tcgetattr(0, &(g_line->new)) < 0)
    return (-1);
  return (0);
}

int		set_termcaps(int status)
{
  if (status == 1)
    {
      g_line->new.c_lflag &= ~(ICANON | ECHO);
      if (tcsetattr(0, TCSANOW, &(g_line->new)) < 0)
	return (-1);
    }
  else
    {
      if (tcsetattr(0, TCSANOW, &(g_line->save)) < 0)
	return (-1);
    }
  return (0);
}

int		cap_multi_line(void)
{
  if (cap("dl") == -1)
    return (-1);
  if (cap("al") == -1)
    return (-1);
  if (cap("up") == -1)
    return (-1);
  return (0);
}
