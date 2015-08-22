/*
** tree_execution.c for src in /home/desrum_m/code/epitech/S2/PSU/minishell2/PSU_2014_minishell2/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  ven. mars 06 15:19:27 2015 Martin Desrumaux
** Last update Sun May 24 22:43:22 2015 raout_t
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		<sys/types.h>
#include		<sys/wait.h>
#include		"mysh.h"
#include		"lib.h"

/*
** The execution of the binary tree is done recursively :
**	If we found a '|', we create the pipe (with the dup2) and we fork,
**	in the son, we reexecute the same function
**	with the right part of the tree.
**	in the father, we do the same with the left part of the tree.
**
**	If we find a ';' we reexecute the same function on the right node
**	and then on the left node
**
**	Else, we fork, and we execute the node.
*/

static int		exec_tree_which_type(char **cmd, char ***env, \
					     t_redir *redir)
{
  int			ret;
  int			status;

  status = 0;
  if ((ret = is_built_in_child(cmd, env, redir)) == 0 || ret < 0)
    return (ret);
  else if (cmd[0][0] == '.' || cmd[0][0] == '/')
    {
      if ((ret = execute(cmd, env, redir, cmd[0])) < 0 || ret == 1)
	return (-1);
    }
  else if ((ret = is_path(cmd, env, redir)) == 0);
  else if (ret < 0 || ret == 1)
    return (ret);
  else
    {
      my_putstrerr(cmd[0]);
      my_putstrerr(" : Program doesn't exist.\n");
      kill(getppid(), SIGUSR1);
      return (1);
    }
  return (status);
}

int			exec_tree_exec_type(char **cmd, char ***env)
{
  t_redir		redir;
  int			ret;

  ret = 0;
  init_struct_redir(&redir);
  while ((ret = detect_struct_redir(&cmd, &redir)) != 2)
    if (ret < 0 || ret == 1)
      return (ret);
  if (cmd[0] == NULL)
    return (print_and_return_int(1, "Invalid null command.\n"));
  if ((ret = exec_tree_which_type(cmd, env, &redir)) < 0 || ret == 1)
    return (ret);
  return (ret);
}

static int		init_ptr_fctn(char **op, \
				      int (**op_fctn)(t_tree *, char ***env))
{
  op[0] = ";";
  op[1] = "&&";
  op[2] = "||";
  op[3] = NULL;
  op_fctn[0] = &exec_tree_comma;
  op_fctn[1] = &exec_tree_and;
  op_fctn[2] = &exec_tree_or;
  op_fctn[3] = NULL;
  return (0);
}

int			exec_tree(t_tree *tree, char ***env)
{
  int			status;
  int			(*op_fctn[4])(t_tree *, char ***env);
  char			*op[4];
  int			i;
  int			stop;

  status = 0;
  stop = 0;
  init_ptr_fctn(op, op_fctn);
  i = -1;
  if (tree == NULL || tree->cmd[0] == NULL)
    return (1);
  while (op[++i] && stop == 0)
    if (my_strcmp(tree->cmd[0], op[i]) == 0 && (stop = 1) == 1)
      if ((status = op_fctn[i](tree, env)) < 0)
	return (status);
  if (op[i] == NULL && stop == 0)
    if ((status = exec_tree_pipeline(tree, env)) < 0 || status == 1)
      return (status);
  return (status);
}

int			free_tree(t_tree *tree)
{
  int			i;

  if (tree->right != NULL)
    free_tree(tree->right);
  if (tree->left != NULL)
    free_tree(tree->left);
  i = -1;
  while (tree->cmd[++i] != NULL)
    free(tree->cmd[i]);
  free(tree->cmd);
  free(tree);
  return (0);
}

/*
** void			show_tree(t_tree *tree)
** {
**   if (tree == NULL)
**     return ;
**   printf("%s\n", tree->cmd[0]);
**   if (tree->left != NULL)
**     show_tree(tree->left);
**   if (tree->right != NULL)
**     show_tree(tree->right);
** }
*/
