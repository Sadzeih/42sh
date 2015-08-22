/*
** exec_tree_op.c for mysh in /home/desrum_m/code/epitech/S2/PSU/minishell2/PSU_2014_minishell2/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.eu>
** 
** Started on  lun. mai 04 14:26:48 2015 Martin Desrumaux
** Last update lun. mai 04 14:26:48 2015 Martin Desrumaux
*/

#include		<unistd.h>
#include		"mysh.h"

int			exec_tree_comma(t_tree *tree, char ***env)
{
  int			status;

  status = 0;
  if (tree->left != NULL)
    if ((status = exec_tree(tree->left, env)) < 0)
      return (status);
  if (tree->right != NULL)
    if ((status = exec_tree(tree->right, env)) < 0)
      return (status);
  return (status);
}

int			exec_tree_and(t_tree *tree, char ***env)
{
  int			status;

  status = 0;
  if (tree->left != NULL)
  {
    if ((status = exec_tree(tree->left, env)) < 0)
      return (status);
    else if (status == 0)
      if (tree->right != NULL)
	if ((status = exec_tree(tree->right, env)) < 0)
	  return (status);
  }
  else
    status = 1;
  return (status);
}

int			exec_tree_or(t_tree *tree, char ***env)
{
  int			status;

  status = 0;
  if (tree->left != NULL)
  {
    if ((status = exec_tree(tree->left, env)) < 0)
      return (status);
    else if (status != 0)
      if (tree->right != NULL)
	if ((status = exec_tree(tree->right, env)) < 0)
	  return (status);
  }
  else
    status = 1;
  return (status);
}
