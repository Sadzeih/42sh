/*
** cmd_check.c for src in /home/desrum_m/code/epitech/S2/PSU/minishell2/PSU_2014_minishell2/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  dim. mars 08 15:26:24 2015 Martin Desrumaux
** Last update Sun May 24 22:24:31 2015 Alexis Guerville
*/

#include		<stdlib.h>
#include		"lib.h"

/*
** the ";" exception have to be changed because it make ls | ; ls works
*/

int			is_that_token_special(char *str, char **token)
{
  int			i;

  i = -1;
  while (token[++i])
    {
      if (my_strcmp(token[i], str) == 0 && my_strcmp(";", str) != 0 \
	  && my_strcmp(">", str) != 0\
	  && my_strcmp(">>", str) != 0\
	  && my_strcmp("<", str) != 0\
	  && my_strcmp("<<", str) != 0)
	return (1);
    }
  return (0);
}

int			cmd_check(char **lexed, char **token)
{
  int			i;

  i = -1;
  while (lexed[++i])
    {
      if ((my_strcmp(lexed[i], "|") == 0 &&\
	   (i == 0 || is_that_token_special(lexed[i - 1], token) == 1)) ||\
	  (is_that_token_special(lexed[i], token) == 1 &&\
	   (lexed[i + 1] == NULL ||\
	    is_that_token_special(lexed[i + 1], token) == 1)))
	{
	  my_putstrerr("Invalid syntax.\n");
	  return (1);
	}
    }
  return (0);
}
