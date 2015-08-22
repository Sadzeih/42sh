/*
** history.c for history in /home/devos-f/Documents/Projet/PSU_2014_42sh
** 
** Made by Francois Devos
** Login   <devos_f@epitech.net>
** 
** Started on  Mon May  4 17:20:13 2015 Francois Devos
** Last update Sun May 24 22:28:13 2015 raout_t
*/

#include	<sys/stat.h>
#include	<stdio.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	"lib.h"
#include	"list.h"
#include	"history.h"

extern t_dlist	*g_history;

int		write_history(char *cmd)
{
  t_elem	*elem;
  char		*tmp;

  if (cmd[0] != '!')
    {
      if ((tmp = my_strdup(cmd)) == NULL)
	return (-1);
      if ((elem = init_elem(tmp)) == NULL)
	return (-1);
      add_elem(g_history, elem);
    }
  return (0);
}
