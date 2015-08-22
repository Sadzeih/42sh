/*
** execution.c for src in /home/desrum_m/code/epitech/S2/PSU/minishell2/PSU_2014_minishell2/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  dim. mars 08 19:08:49 2015 Martin Desrumaux
** Last update Sun May 24 23:04:19 2015 Francois Devos
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		<sys/stat.h>
#include		<sys/types.h>
#include		<signal.h>
#include		"lib.h"
#include		"mysh.h"
#include		"history.h"

/*
** Access && fork : <unsistd.h>
** NULL		  : <stdlib.h>
** stat		  : <sys/stat.h> <types.h>
*/

int			launch_error(char *path)
{
  struct stat		buf;

  my_putstrerr(path);
  if ((stat(path, &buf)) != -1 && S_ISDIR(buf.st_mode))
    my_putstrerr(" : Is a directory.\n");
  else if (access(path, F_OK) == 0)
    my_putstrerr(" : No execution permissions.\n");
  else
    my_putstrerr(" : Program doesn't exist.\n");
  return (-1);
}

int			launch(char *path, char **av, char ***env, t_fd *fd)
{
  if (dup2(fd->in, 0) == -1)
    return (-1);
  if (dup2(fd->out, 1) == -1)
    return (-1);
  if (dup2(fd->err, 2) == -1)
    return (-1);
  if ((execve(path, av, *env)) == -1)
    return (launch_error(path));
  return (0);
}

int			execute_redir(t_redir *redir, t_fd *fd)
{
  if (check_redir(redir) == 1)
    return (1);
  if (redir->left != NULL)
    if (left_redir(fd, redir) == 1)
      return (1);
  if (redir->right != NULL)
    if (right_redir(fd, redir) == 1)
      return (1);
  if (redir->d_right != NULL)
    if (dright_redir(fd, redir) == 1)
      return (1);
  if (redir->d_left != NULL)
    if (dleft_redir(fd, redir) == 1)
      return (1);
  return (0);
}

int			execute(char **lexed, char ***env, t_redir *redir,\
				char *exec_test)
{
  t_fd			fd;
  int			ret;

  fd.in = 0;
  fd.out = 1;
  fd.err = 2;
  if ((execute_redir(redir, &fd)) == 1)
    return (1);
  if ((ret = launch(exec_test, lexed, env, &fd)) != 0)
    return (ret);
  if (redir->d_left != NULL)
    close(fd.in);
  if (redir->right != NULL)
    close(fd.out);
  if (redir->left != NULL)
    close(fd.in);
  if (redir->d_right != NULL)
    close(fd.out);
  return (0);
}

int			is_built_in_child(char **lexed, char ***env,\
					  t_redir *redir)
{
  char			*name[3];
  int			(*func[3])(char ***env, char **lexed);
  int			i;
  int			ret;

  name[0] = "history";
  name[1] = "echo";
  name[2] = NULL;
  func[0] = aff_history;
  func[1] = my_echo;
  func[2] = NULL;
  i = -1;
  while (name[++i])
  {
    if (my_strcmp(lexed[0], name[i]) == 0)
    {
      ret = execute_builtin(func[i], lexed, env, redir);
      return (ret);
    }
  }
  return (1);
}
