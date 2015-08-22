/*
** tree_execution_pipe.c for 42sh in /home/desrum_m/code/epitech/S2/PSU/42sh/PSU_2014_42sh/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.eu>
** 
** Started on  mer. mai 06 19:17:39 2015 Martin Desrumaux
** Last update mer. mai 06 19:17:39 2015 Martin Desrumaux
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		<signal.h>
#include		<sys/wait.h>
#include		"lib.h"
#include		"mysh.h"

int			check_pipe_error(t_tree *tree)
{
  t_redir		redir;
  char			**right_tmp;
  char			**left_tmp;
  int			ret;

  if ((right_tmp = double_strdup(tree->right->cmd)) == NULL)
    return (-1);
  if ((left_tmp = double_strdup(tree->left->cmd)) == NULL)
    return (-1);
  init_struct_redir(&redir);
  while ((ret = detect_struct_redir(&(right_tmp), &redir)) != 2)
    if (ret < 0 || ret == 1)
      return (ret);
  if (redir.left != NULL || redir.d_left != NULL)
    return (print_and_return_int(1, "Ambiguous input redirect.\n"));
  free(right_tmp);
  init_struct_redir(&redir);
  while ((ret = detect_struct_redir(&(left_tmp), &redir)) != 2)
    if (ret < 0 || ret == 1)
      return (ret);
  if (redir.right != NULL || redir.d_right != NULL)
    return (print_and_return_int(1, "Ambiguous ouput redirect.\n"));
  free(left_tmp);
  return (0);
}

int			close_n_dup(int in, int out, int fd)
{
  if (close(in) == -1)
    return (-1);
  if (dup2(out, fd) == -1)
    return (-1);
  if (close(out) == -1)
    return (-1);
  return (0);
}

int			exec_tree_pipe_second_fork(t_tree *tree, int *fd_fork, \
						   char ***env)
{
  pid_t			pid;
  int			status;

  status = 0;
  if ((pid = fork()) == 0)
  {
    if (close_n_dup(fd_fork[1], fd_fork[0], 0) == -1)
      return (-1);
    signal(SIGINT, SIG_DFL);
    status = exec_tree(tree->right, env);
    return (status / 256 - (256 * 2));
  }
  else if (pid < 0)
    return (-1);
  else if (pid > 0)
  {
    if (close(fd_fork[1]) == -1)
      return (-1);
    if (close(fd_fork[0]) == -1)
      return (-1);
  }
  return (status);
}

int			exec_father(t_tree *tree, int *fd_fork, char ***env)
{
  int			status;

  status = 0;
  if ((status = exec_tree_pipe_second_fork(tree, fd_fork, env)) < 0)
    return (status);
  if (waitpid(0, &status, 0) == -1)
    return (print_and_return_int(-1, "waitpid() failed.\n"));
  if (waitpid(0, &status, 0) == -1)
    return (print_and_return_int(-1, "waitpid() failed.\n"));
  return (status);
}

int			exec_tree_pipe(t_tree *tree, char ***env)
{
  int			fd_fork[2];
  int			pid;
  int			status;
  int			ret;

  status = 0;
  if ((ret = check_pipe_error(tree)) == 1 || ret < 0)
    return (ret);
  if (pipe(fd_fork) == -1)
    return (-1);
  if ((pid = fork()) == 0)
  {
    if (close_n_dup(fd_fork[0], fd_fork[1], 1) == -1)
      return (-1);
    signal(SIGINT, SIG_DFL);
    status = exec_tree(tree->left, env);
    return (status / 256 - (256 * 2));
  }
  else if (pid < 0)
    return (print_and_return_int(-1, "Fork failed.\n"));
  else if (pid > 0)
    status = exec_father(tree, fd_fork, env);
  return (status);
}
