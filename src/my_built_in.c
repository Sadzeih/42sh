/*
** my_built_in.c for minishell1 in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Mon Jan 26 17:21:23 2015 Martin Desrumaux
** Last update Sun May 24 23:11:06 2015 Francois Devos
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		"mysh.h"
#include		"lib.h"
#include		"aliases.h"
#include		"scripting.h"
#include		"history.h"

int			launch_builtin(int (*func)(char ***env, char **lexed), \
				       char **lexed, char ***env, t_fd *fd)
{
  int			ret;

  if (dup2(fd->in, 0) == -1)
    return (-1);
  if (dup2(fd->out, 1) == -1)
    return (-1);
  if (dup2(fd->err, 2) == -1)
    return (-1);
  ret = func(env, lexed);
  return (ret);
}

int			close_restore_fd(t_redir *redir, t_fd *fd, t_fd *save)
{
  if (redir->d_left != NULL)
    close(fd->in);
  if (redir->right != NULL)
    close(fd->out);
  if (redir->left != NULL)
    close(fd->in);
  if (redir->d_right != NULL)
    close(fd->out);
  if (dup2(save->in, 0) == -1)
    return (-1);
  if (dup2(save->out, 1) == -1)
    return (-1);
  if (dup2(save->err, 2) == -1)
    return (-1);
  return (0);
}

int			execute_builtin(int (*func)(char ***env, char **lexed),
					char **lexed, char ***env, \
					t_redir *redir)
{
  t_fd			fd;
  int			ret;
  t_fd			save;

  fd.in = 0;
  fd.out = 1;
  fd.err = 2;
  if ((save.in = dup(0)) == -1)
    return (-1);
  if ((save.out = dup(1)) == -1)
    return (-1);
  if ((save.err = dup(2)) == -1)
    return (-1);
  if ((execute_redir(redir, &fd)) == 1)
    return (1);
  if ((ret = launch_builtin(func, lexed, env, &fd)) == -1)
    return (ret);
  if (close_restore_fd(redir, &fd, &save) == -1)
    return (-1);
  return (ret);
}

static int		init_ptr_func(char *name[7], \
				      int (*func[7])(char ***env, char **lexed))
{
  name[0] = "cd";
  name[1] = "setenv";
  name[2] = "unsetenv";
  name[3] = "exit";
  name[4] = "set";
  name[5] = "unset";
  name[6] = NULL;
  func[0] = my_cd_cmd;
  func[1] = my_setenv_cmd;
  func[2] = my_unsetenv_cmd;
  func[3] = my_exit_cmd;
  func[4] = my_set;
  func[5] = my_unset;
  func[6] = NULL;
  return (0);
}

int			is_built_in(char **lexed, char ***env)
{
  char			*name[7];
  int			(*func[7])(char ***env, char **lexed);
  int			i;
  int			ret;
  char			**tmp;
  t_redir		redir;

  i = -1;
  tmp = double_strdup(lexed);
  init_struct_redir(&redir);
  while ((ret = detect_struct_redir(&tmp, &redir)) != 2)
    if (ret < 0 || ret == 1)
      return (ret);
  if (tmp[0] == NULL)
    return (print_and_return_int(1, "Invalid null command.\n"));
  init_ptr_func(name, func);
  while (name[++i])
    if (my_strcmp(tmp[0], name[i]) == 0)
    {
      ret = execute_builtin(func[i], tmp, env, &redir);
      return (ret);
    }
  double_free_tab(tmp);
  return (2);
}
