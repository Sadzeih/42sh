/*
** tree_exec_pipeline.c for 42sh in /tmp/PSU_2014_42sh/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.eu>
** 
** Started on  dim. mai 24 15:41:12 2015 Martin Desrumaux
** Last update Sun May 24 22:47:11 2015 raout_t
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		<wait.h>
#include		"lib.h"
#include		"mysh.h"
#include		"list.h"

int			g_waitredir;

static int		exec_tree_pipeline_exec(t_list **pipeline_base, \
						char ***env)
{
  t_list		*pipeline;
  t_list		*pipeline_prev;
  t_pipe_fd		pipe_fd;
  int			ret;

  pipeline = *pipeline_base;
  pipeline_prev = NULL;
  while (pipeline)
  {
    if ((ret = is_built_in(pipeline->data, env)) == 0 || ret < 0 || ret == 1)
    {
      rm_list(&pipeline, pipeline_base);
      if (ret < 0 || ret == 1)
	return (ret);
    }
    else
      if ((ret = exec_tree_pipeline_exec_cmd(&pipeline, &pipeline_prev, \
				      &pipe_fd, env)) < 0)
	return (ret);
  }
  return (0);
}

static t_list		*lexing_dtab(char **lexed, char *sep)
{
  t_list		*list;
  char			**token;
  int			i;

  i = -1;
  list = NULL;
  while (lexed[++i])
    if (my_strcmp(lexed[i], sep) == 0)
    {
      if ((token = dup_double_ntab(lexed, i)) == NULL)
	return (NULL);
      if (my_put_in_list_end(&list, token) == -1)
	return (NULL);
      i++;
      while (--i >= 0)
	lexed++;
    }
  if (i != 0)
  {
    if ((token = dup_double_ntab(lexed, i)) == NULL)
      return (NULL);
    if (my_put_in_list_end(&list, token) == -1)
      return (NULL);
  }
  return (list);
}

static int		check_pipe_error(t_list *pipeline)
{
  t_redir		redir;
  t_list		*pipeline_prev;
  char			**lexed_tmp;
  int			ret;

  pipeline_prev = NULL;
  while (pipeline)
  {
    if ((lexed_tmp = double_strdup(pipeline->data)) == NULL)
      return (-1);
    init_struct_redir(&redir);
    while ((ret = detect_struct_redir(&(lexed_tmp), &redir)) != 2)
      if (ret < 0 || ret == 1)
	return (ret);
    if (pipeline_prev != NULL)
      if (redir.left != NULL || redir.d_left != NULL)
	return (print_and_return_int(1, "Ambiguous input redirect.\n"));
    if (pipeline->next != NULL)
      if (redir.right != NULL || redir.d_right != NULL)
	return (print_and_return_int(1, "Ambiguous ouput redirect.\n"));
    double_free_tab(lexed_tmp);
    pipeline_prev = pipeline;
    pipeline = pipeline->next;
  }
  return (0);
}

static void		write_message_return(int status, t_list *pipeline)
{
  if (status == (128 + 11))
    my_putstrerr("Segmentation Fault.\n");
  if (pipeline->next == NULL && status == 2)
    my_putstr("\n");
}

int			exec_tree_pipeline(t_tree *tree, char ***env)
{
  int			status;
  t_list		*pipeline;
  extern pid_t		g_pgid;

  g_pgid = 0;
  if ((pipeline = lexing_dtab(tree->cmd, "|")) == NULL)
    return (-1);
  if ((status = check_pipe_error(pipeline)) < 0 || status == 1)
    return (status);
  status = 0;
  if ((status = exec_tree_pipeline_exec(&pipeline, env)) < 0)
    return (status);
  while (pipeline)
  {
    if (waitpid(-1, &status, 0) == -1)
      return (print_and_return_int(-1, "waitpid failed.\n"));
    write_message_return(status, pipeline);
    status = status / 256;
    pipeline = pipeline->next;
  }
  if (isatty(0) == 1)
    if (tcsetpgrp(0, getpid()) == -1)
      return (print_and_return_int(-1, "tcsetpgrp failed.\n"));
  g_pgid = 0;
  return (status);
}

