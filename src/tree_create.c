/*
** create_tree.c for src in /home/desrum_m/code/epitech/S2/PSU/minishell2/PSU_2014_minishell2/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  lun. mars 02 16:51:14 2015 Martin Desrumaux
** Last update Sun May 24 22:38:43 2015 raout_t
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		"mysh.h"
#include		"lib.h"

/*
** This function is used to find the position of the biggest priotity operand
** in the string given in parameters finishing at end
**
** return the position of the operand
*/

static int		is_special_token(char **lexed, int end)
{
  int			i;

  i = -1;
  while (lexed[++i] && i < end)
    if (my_strcmp(lexed[i], ";") == 0)
      return (i);
  i = -1;
  while (lexed[++i] && i < end)
    if (my_strcmp(lexed[i], "||") == 0)
      return (i);
  i = -1;
  while (lexed[++i] && i < end)
    if (my_strcmp(lexed[i], "&&") == 0)
      return (i);
  return (0);
}

char			**dup_double_ntab(char **dtab, int size)
{
  char			**new;
  int			i;
  int			j;

  j = 0;
  if ((new = malloc(sizeof(char*) * (size + 1))) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  i = -1;
  while (++i < size)
    if ((new[j++] = my_strdup(dtab[i])) == NULL)
      return (NULL);
  new[j] = NULL;
  return (new);
}

static int		add_tree_elem(char **tab, t_tree **tree, char pos)
{
  t_tree		*elem;

  if ((elem = malloc(sizeof(t_tree))) == NULL)
    return (print_and_return_int(-1, "Malloc failed.\n"));
  elem->cmd = tab;
  elem->left = NULL;
  elem->right = NULL;
  if (*tree == NULL)
    *tree = elem;
  else
  {
    if (pos == 'l')
      (*tree)->left = elem;
    else if (pos == 'r')
      (*tree)->right = elem;
  }
  return (0);
}

/*
** This function is recursive.
** It fills the tree like that :
**			|
**	ls -la				|
**			  grep "include"	cat
**
** Or :
**			;
**	ls -la				|
**			 ls -la			cat
**
** It finds the position of the biggest priority operands
** it fills the tree with everything before that position and then it goes on.
*/

int			fill_tree(char **lexed, t_tree **tree,
				  int token_pos_end)
{
  int			pos_spec_token;
  char			**ret;

  if ((pos_spec_token = is_special_token(lexed, token_pos_end)) > 0)
  {
    if (lexed[0] + pos_spec_token == NULL || lexed[1] + pos_spec_token == NULL)
      return (-1);
    if ((ret = dup_double_ntab(lexed + pos_spec_token, 1)) == NULL)
      return (-1);
    if (add_tree_elem(ret, tree, 'l') == -1)
      return (-1);
    if (fill_tree(lexed, &((*tree)->left), pos_spec_token) == -1)
      return (-1);
    if (fill_tree(lexed + pos_spec_token + 1, &((*tree)->right), \
		  token_pos_end - (pos_spec_token + 1)) == -1)
      return (-1);
  }
  else
  {
    if ((ret = dup_double_ntab(lexed, token_pos_end)) == NULL)
      return (-1);
    if (add_tree_elem(ret, tree, 'l') == -1)
      return (-1);
  }
  return (0);
}
