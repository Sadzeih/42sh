/*
** change_env.c for src in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  mar. janv. 20 13:39:37 2015 Martin Desrumaux
** Last update mar. janv. 20 13:39:37 2015 Martin Desrumaux
*/

#include		<stdlib.h>
#include		"lib.h"
#include		"mysh.h"

static char		*create_value(char *name, char *value)
{
  char			*outvalue;

  if ((outvalue = malloc(sizeof(char) * \
	  (my_strlen(name) + my_strlen(value) + my_strlen("=") + 1))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  outvalue[0] = '\0';
  my_strcat(outvalue, name);
  my_strcat(outvalue, "=");
  my_strcat(outvalue, value);
  outvalue[my_strlen(outvalue)] = '\0';
  return (outvalue);
}

static char		**change_value(char **env, char *name, char *value)
{
  int			i;
  int			len;

  i = -1;
  len = my_strlen(name);
  while (env[++i])
  {
    if ((my_strncmp(name, env[i], len)) == 0 && env[i][len] == '=')
    {
      free(env[i]);
      if ((env[i] = create_value(name, value)) == NULL)
	return (NULL);
      return (env);
    }
  }
  return (NULL);
}

static char		**add_value(char **env, char *name, char *value)
{
  int			i;
  int			size;
  char			**newenv;

  size = -1;
  i = -1;
  while (env[++size]);
  if ((newenv = malloc(sizeof(char*) * (size + 2))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  while (++i < size)
    if ((newenv[i] = my_strdup(env[i])) == NULL)
      return (NULL);
  if ((newenv[size] = create_value(name, value)) == NULL)
    return (NULL);
  newenv[size + 1] = NULL;
  double_free_tab(env);
  return (newenv);
}

char			**my_setenv(char **env, char *name, char *value, \
				    int overwrite)
{
  char			**newenv;

  newenv = NULL;
  if (my_parsenv(env, name) != NULL)
  {
    if (overwrite == 0)
      return (env);
    else
      if ((newenv = change_value(env, name, value)) == NULL)
	return (NULL);
  }
  else
    if ((newenv = add_value(env, name, value)) == NULL)
      return (NULL);
  return (newenv);
}

char			**my_unsetenv(char **env, char *name)
{
  int			size;
  int			i;
  int			j;
  char			**newenv;

  size = -1;
  i = -1;
  j = 0;
  while (env[++size]);
  if ((newenv = malloc(sizeof(char*) * (size + 1))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  while (++i < (size))
    if (my_strncmp(env[i], name, my_strlen(name)) != 0 \
	|| env[i][my_strlen(name)] != '=')
    {
      if ((newenv[j] = my_strdup(env[i])) == NULL)
	return (NULL);
      j++;
    }
  newenv[j] = NULL;
  double_free_tab(env);
  env = NULL;
  return (newenv);
}
