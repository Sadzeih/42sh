/*
** tree_execution_pipeline_cmd.c for tree_execution_pipeline_cmd in /home/devos-f/Documents/Projet/PSU_2014_42sh
** 
** Made by Francois Devos
** Login   <devos_f@epitech.net>
** 
** Started on  Sun May 24 21:16:52 2015 Francois Devos
** Last update Sun May 24 21:16:59 2015 Francois Devos
*/

#include		<signal.h>
#include		<stdlib.h>
#include		<unistd.h>
#include		"lib.h"
#include		"mysh.h"

/*
** pipe_fd[0] ==> Part in which we read
** pipe_fd[1] ==> Part in which we write
*/

static int		close_n_dup(int in, int out, int fd)
{
  if (close(in) == -1)
    return (print_and_return_int(-1, "close failed.\n"));
  if (dup2(out, fd) == -1)
    return (print_and_return_int(-1, "dup2 failed.\n"));
  if (close(out) == -1)
    return (print_and_return_int(-1, "close failed.\n"));
  return (0);
}

static int		exec_tree_pipeline_child(t_list *pipeline, \
						 t_list *pipeline_prev, \
						 t_pipe_fd *pipe_fd, \
						 char ***env)
{
  int			status;

  init_signal_prgrm();
  if (pipeline_prev != NULL)
    if (close_n_dup(pipe_fd->before[1], pipe_fd->before[0], 0) == -1)
      return (-1);
  if (pipeline->next != NULL)
    if (close_n_dup(pipe_fd->next[0], pipe_fd->next[1], 1) == -1)
      return (-1);
  status = exec_tree_exec_type(pipeline->data, env);
  return (status - (256 * 2));
}

static int		wait_dleft_redir(t_list *pipeline)
{
  t_redir		redir;
  char			**lexed_tmp;
  int			ret;
  extern int		g_waitredir;

  g_waitredir = 0;
  signal(SIGUSR1, set_var);
  if (isatty(0) == 1)
  {
    if ((lexed_tmp = double_strdup(pipeline->data)) == NULL)
      return (-1);
    init_struct_redir(&redir);
    while ((ret = detect_struct_redir(&(lexed_tmp), &redir)) != 2)
      if (ret < 0 || ret == 1)
	return (ret);
    if (redir.d_left != NULL)
      while (g_waitredir != 1);
  }
  g_waitredir = 0;
  return (0);
}

static int		exec_tree_pipeline_exec_father(t_list *pipeline, \
						       t_list *pipeline_prev, \
						       int pipe_fd_before[2], \
						       pid_t pid)
{
  extern int		g_pgid;

  if (setpgid(pid, g_pgid) == -1)
    return (print_and_return_int(-1, "setpgid failed.\n"));
  if (g_pgid == 0)
    g_pgid = pid;
  if (isatty(0) == 1)
    if (tcsetpgrp(0, g_pgid) == -1)
      return (print_and_return_int(-1, "tcsetpgrp failed.\n"));
  if (wait_dleft_redir(pipeline) == -1)
    return (-1);
  if (pipeline_prev != NULL)
  {
    close(pipe_fd_before[0]);
    close(pipe_fd_before[1]);
  }
  return (0);
}

int		exec_tree_pipeline_exec_cmd(t_list **pipeline, \
						    t_list **pipeline_prev, \
						    t_pipe_fd *pipe_fd, \
						    char ***env)
{
  int			pid;

  if ((*pipeline)->next != NULL)
    if (pipe(pipe_fd->next) == -1)
      return (-1);
  if ((pid = fork()) == 0)
    return (exec_tree_pipeline_child(*pipeline, *pipeline_prev, pipe_fd, env));
  else if (pid < 0)
    return (print_and_return_int(-1, "Fork failed.\n"));
  else if (pid > 0)
    if (exec_tree_pipeline_exec_father(*pipeline, *pipeline_prev, \
				       pipe_fd->before, pid) == -1)
      return (-1);
  pipe_fd->before[0] = pipe_fd->next[0];
  pipe_fd->before[1] = pipe_fd->next[1];
  *pipeline_prev = *pipeline;
  *pipeline = (*pipeline)->next;
  return (0);
}
