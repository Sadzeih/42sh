/*
** glob_check.c for glob_check in /home/devos-f/Documents/Projet/PSU_2014_42sh/src/globbing
** 
** Made by Francois Devos
** Login   <devos_f@epitech.net>
** 
** Started on  Sun May 24 19:36:27 2015 Francois Devos
** Last update Sun May 24 22:32:34 2015 Alexis Guerville
*/

#include	<stdlib.h>
#include	"lib.h"

int		check_dleft(char **lexed)
{
  int		i;
  int		j;

  i = 0;
  while (lexed[i])
    {
      if (my_strcmp(lexed[i], "<<") == 0)
	{
	  if (lexed[i + 1] != NULL)
	    {
	      j = 0;
	      while (lexed[i + 1][j])
		{
		  if (lexed[i + 1][j] == '~' || lexed[i + 1][j] == '$'\
		      || lexed[i + 1][j] == '^' || lexed[i + 1][j] == '*'\
		      || lexed[i + 1][j] == '[' || lexed[i + 1][j] == '{'\
		      || lexed[i + 1][j] == '?')
		    return (1);
		  j++;
		}
	    }
	}
      i++;
    }
  return (0);
}

int		check_sign(char sign)
{
  if ((sign == '*' || sign == '?'\
       || sign == '[' || sign == '{' || sign == '^'))
    return (0);
  return (1);
}
