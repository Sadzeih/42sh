/*
** my_cd.c for minishell1 in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Thu Jan 22 03:11:37 2015 Martin Desrumaux
** Last update Thu Jan 22 03:11:40 2015 Martin Desrumaux
*/

#include		<sys/types.h>
#include		<sys/stat.h>
#include		<unistd.h>
#include		<stdlib.h>
#include		"lib.h"
#include		"mysh.h"

/*
** <unistd.h>				: chdir && access &&& fstat
** <sys/types.h> && <sys/stat.h>	: fstat
** <stdlib.h>				: free
*/

int			check_errors_cd(char *name)
{
  struct stat		buf;

  my_putstrerr(name);
  if (lstat(name, &buf) == 0)
  {
    if (!S_ISDIR(buf.st_mode))
      my_putstrerr(" : Is not a directory\n");
    else if (access(name, X_OK) == -1)
      my_putstrerr(" : Permission Denied\n");
    else
      my_putstrerr(" : Unknown Error\n");
  }
  else
    my_putstrerr(" : File doesn't exist.\n");
  return (0);
}

static int		set_vars(char ***env)
{
  char			*old_pwd;
  char			*pwd;

  if ((old_pwd = my_parsenv(*env, "PWD")) != NULL)
  {
    if ((*env = my_setenv(*env, "OLDPWD", old_pwd, 1)) == NULL)
      return (-1);
    if ((pwd = my_getcwd()) != NULL)
    {
      if ((*env = my_setenv(*env, "PWD", pwd, 1)) == NULL)
	return (-1);
      free(pwd);
    }
  }
  else if ((pwd = my_getcwd()) != NULL)
  {
    if ((*env = my_setenv(*env, "PWD", pwd, 1)) == NULL)
      return (-1);
    if ((*env = my_setenv(*env, "OLDPWD", pwd, 1)) == NULL)
      return (-1);
    free(pwd);
  }
  return (0);
}

int			my_cd(char ***env, char *name)
{
  if (chdir(name) == 0)
  {
    if (set_vars(env) == -1)
      return (-1);
  }
  else
  {
    check_errors_cd(name);
    return (1);
  }
  return (0);
}
