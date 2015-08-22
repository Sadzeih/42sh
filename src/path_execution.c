/*
** my_path.c for my_path in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Fri Jan 30 18:07:06 2015 Martin Desrumaux
** Last update Fri Jan 30 18:07:08 2015 Martin Desrumaux
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		"lib.h"
#include		"list.h"
#include		"mysh.h"

/*
** Access	  : <unsistd.h>
** NULL		  : <stdlib.h>
** stat		  : <sys/stat.h> <types.h>
*/

static char		*malloc_and_concat(t_list *list, char **lexed, int len)
{
  char			*exec_test;

  if (!(exec_test = malloc(sizeof(char) * (my_strlen(list->data) + len + 2))))
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  exec_test[0] = '\0';
  my_strcat(exec_test, list->data);
  my_strcat(exec_test, "/");
  my_strcat(exec_test, lexed[0]);
  return (exec_test);
}

static int		is_path_match(char **lexed, char ***env, \
				      t_redir *redir, t_list *l_path)
{
  char			*exec_test;
  int			len;
  int			status;

  status = 0;
  len = my_strlen(lexed[0]);
  while (l_path != NULL)
  {
    if ((exec_test = malloc_and_concat(l_path, lexed, len)) == NULL)
      return (-1);
    if (access(exec_test, F_OK) == 0)
    {
      if ((status = execute(lexed, env, redir, exec_test)) < 0 || status == 1)
	return (status);
      free(exec_test);
      return (0);
    }
    free(exec_test);
    l_path = l_path->next;
  }
  return (2);
}

/*
** This function giva back :
**	- 0 if everything was fine
**	- 1 for an error when program is found but
**		there was another error
**	- 2 if program wasn't found
*/

int			is_path(char **lexed, char ***env, t_redir *redir)
{
  t_list		*l_path;
  char			*path;
  int			ret;

  ret = 0;
  if ((path = my_parsenv(*env, "PATH")) == NULL)
    return (print_and_return_int(1, "Can't find $PATH in env.\n"));
  if (path[0] == '\0')
    return (print_and_return_int(-1, "Empty $PATH.\n"));
  if ((l_path = lexer(path, ":", NULL)) == NULL)
    return (-1);
  if ((ret = is_path_match(lexed, env, redir, l_path)) != 0)
    return (ret);
  free_list(l_path);
  return (ret);
}
