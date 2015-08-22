/*
** scripting.c for scripting.c in /home/thomas/rendu/PSU/PSU_2014_42sh/src_scripting
** 
** Made by raout_t
** Login   <thomas@epitech.net>
** 
** Started on Fri May 15 15:41:18 2015 raout_t
** Last update Sun May 24 22:53:29 2015 Francois Devos
*/

#include	<stdlib.h>
#include	"lib.h"
#include	"mysh.h"
#include	"scripting.h"

extern t_vars	*g_vars;

t_vars		*init_new_var(char **lexed)
{
  t_vars	*new_var;

  if ((new_var = malloc(sizeof(t_vars))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  if ((new_var->name = my_strdup(lexed[1])) == NULL)
    return (NULL);
  if ((new_var->value = my_strdup(lexed[3])) == NULL)
    return (NULL);
  new_var->next = NULL;
  return (new_var);
}

int		set_local_var(char **lexed)
{
  t_vars	*tmp;

  tmp = g_vars;
  if (tmp == NULL)
    {
      if ((g_vars = init_new_var(lexed)) == NULL)
	return (-1);
    }
  else
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      if ((tmp->next = init_new_var(lexed)) == NULL)
	return (print_and_return_int(-1, "Malloc failed."));
    }
  return (0);
}

int		is_in_list(char *name, char *value)
{
  t_vars	*tmp;

  tmp = g_vars;
  while (tmp != NULL)
    {
      if (my_strcmp(tmp->name, name) == 0)
	{
	  free(tmp->value);
	  if ((tmp->value = my_strdup(value)) == NULL)
	    return (-1);
	  return (1);
	}
      tmp = tmp->next;
    }
  return (0);
}

int		my_set(char ***env, char **lexed)
{
  int		ret;

  (void)env;
  if (lexed[1] == NULL ||
      lexed[2] == NULL || my_strcmp(lexed[2], "=") != 0 ||
      lexed[3] == NULL)
    return (print_and_return_int(0, "set usage: \"set [name] = [value]\"\n"));
  if ((lexed[1][0] < 'a' ||  lexed[1][0] > 'z') &&
      (lexed[1][0] < 'A' || lexed[1][0] > 'Z'))
    {
      my_putstr("set: Variable name must begin with a letter.\n");
      return (0);
    }
  if ((ret = is_in_list(lexed[1], lexed[3])) == -1)
    return (-1);
  else if (ret == 0)
    {
      if (set_local_var(lexed) == -1)
	return (-1);
    }
  return (0);
}
