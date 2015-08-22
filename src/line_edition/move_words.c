/*
** move_words.c for 42sh in /home/guervi-a/rendu/Sys_Unix/PSU_2014_42sh
** 
** Made by Alexis Guerville
** Login   <guervi_a@epitech.net>
** 
** Started on  Tue May 19 04:22:57 2015 Alexis Guerville
** Last update Sun May 24 22:51:50 2015 Francois Devos
*/

#include	"line.h"
#include	"lib.h"

extern t_line	*g_line;

int		move_start()
{
  g_line->pos = 0;
  return (0);
}

int		move_end()
{
  if (g_line->cmd != NULL)
    g_line->pos = my_strlen(g_line->cmd);
  return (0);
}

int		move_start_word()
{
  while (g_line->cmd != NULL && g_line->pos > 0 &&\
	 (g_line->cmd[g_line->pos - 1] == ' ' ||\
	  g_line->cmd[g_line->pos - 1] == '\t'))
    g_line->pos--;
  while (g_line->cmd != NULL && g_line->pos > 0 &&\
	 (g_line->cmd[g_line->pos - 1] != ' ' &&\
	  g_line->cmd[g_line->pos - 1] != '\t'))
    g_line->pos--;
  return (0);
}

int		move_end_word()
{
  while (g_line->cmd != NULL && g_line->pos < my_strlen(g_line->cmd) &&\
	 (g_line->cmd[g_line->pos] == ' ' ||\
	  g_line->cmd[g_line->pos] == '\t'))
    g_line->pos++;
  while (g_line->cmd != NULL && g_line->pos < my_strlen(g_line->cmd) &&\
	 (g_line->cmd[g_line->pos] != ' ' &&\
	  g_line->cmd[g_line->pos] != '\t'))
    g_line->pos++;
  return (0);
}
