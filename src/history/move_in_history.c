/*
** move_in_history.c for move_in_history in /home/devos-f/Documents/Projet/PSU_2014_42sh
** 
** Made by Francois Devos
** Login   <devos_f@epitech.net>
** 
** Started on  Wed May  6 15:20:49 2015 Francois Devos
** Last update Sun May 24 22:30:27 2015 raout_t
*/

#include	<unistd.h>
#include	<string.h>
#include	"mysh.h"
#include	"list.h"
#include	"lib.h"
#include	"history.h"
#include	"line.h"

extern t_elem	*g_pos_history;
extern t_dlist	*g_history;
extern t_line	*g_line;

int		history_up(void)
{
  if (g_pos_history != NULL)
    {
      if (g_pos_history->prev == NULL ||\
	  g_pos_history == g_history->end)
	{
	  if ((g_line->cmd = strdup(g_pos_history->data)) == NULL)
	    return (-1);
	  g_line->pos = my_strlen(g_pos_history->data);
	  if (g_pos_history->prev != NULL)
	    g_pos_history = g_pos_history->prev;
	}
      else if (g_pos_history->prev != NULL)
	{
	  if ((g_line->cmd = strdup(g_pos_history->data)) == NULL)
	    return (-1);
	  g_line->pos = strlen(g_pos_history->data);
	  g_pos_history = g_pos_history->prev;
	}
    }
  return (0);
}

int		history_down(void)
{
  if (g_pos_history != NULL)
    {
      if (g_pos_history->next != NULL)
	{
	  g_pos_history = g_pos_history->next;
	  if ((g_line->cmd = strdup(g_pos_history->data)) == NULL)
	    return (-1);
	  g_line->pos = strlen(g_pos_history->data);
	}
      else if (g_pos_history->next == NULL)
	g_line->cmd = NULL;
    }
  return (0);
}
