/*
** redirections.c for src in /home/desrum_m/code/epitech/S2/PSU/minishell2/PSU_2014_minishell2/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  ven. mars 06 15:22:59 2015 Martin Desrumaux
** Last update Sun May 24 22:23:21 2015 Francois Devos
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		"lib.h"
#include		"mysh.h"

/*
** Those functions are called in the execution of the binary tree
** They fill a structure of char* with the name of the file
** just before executing the command.
*/

int			init_struct_redir(t_redir *redir)
{
  redir->right = NULL;
  redir->d_right = NULL;
  redir->left = NULL;
  redir->d_left = NULL;
  return (0);
}

static int		modify_string(char ***token, int pos_redir)
{
  int			i;
  int			j;
  char			**new;

  i = -1;
  j = -1;
  if ((new = malloc(sizeof(char*) * (tokenlen((*token)) - 1))) == NULL)
    return (print_and_return_int(-1, "Malloc failed.\n"));
  while ((*token)[++i])
  {
    if (i != pos_redir && i != (pos_redir + 1))
    {
      if ((new[++j] = my_strdup((*token)[i])) == NULL)
	return (-1);
      free((*token)[i]);
    }
    else
      free((*token)[i]);
  }
  new[++j] = NULL;
  free((*token));
  *token = new;
  return (0);
}

static int		check_token(char ***token, int pos_redir, \
				    char **redir, char *this_token)
{
  if ((*token)[pos_redir + 1] != NULL && \
      my_strcmp((*token)[pos_redir], this_token) == 0)
  {
    if (*redir != NULL)
    {
      if (my_strcmp(this_token, ">") == 0 || my_strcmp(this_token, ">>") == 0)
	return (print_and_return_int(1, "Ambiguous output redirect.\n"));
      else if (my_strcmp(this_token, "<") == 0 || \
	       my_strcmp(this_token, "<<") == 0)
	return (print_and_return_int(1, "Ambiguous input redirect.\n"));
    }
    if ((*redir = my_strdup((*token)[pos_redir + 1])) == NULL)
      return (-1);
    return (2);
  }
  return (0);
}

static void		init_tab(char *this_redir_tab[5], \
				 char **redir_to_fill[5], t_redir *redir)
{
  redir_to_fill[0] = &redir->right;
  redir_to_fill[1] = &redir->d_right;
  redir_to_fill[2] = &redir->left;
  redir_to_fill[3] = &redir->d_left;
  redir_to_fill[4] = NULL;
  this_redir_tab[0] = ">";
  this_redir_tab[1] = ">>";
  this_redir_tab[2] = "<";
  this_redir_tab[3] = "<<";
  this_redir_tab[4] = NULL;
}

int			detect_struct_redir(char ***token, t_redir *redir)
{
  int			ret;
  char			*this_redir_tab[5];
  char			**redir_to_fill[5];
  int			i;
  int			pos;

  pos = -1;
  init_tab(this_redir_tab, redir_to_fill, redir);
  while ((*token)[++pos])
  {
    i = -1;
    while (this_redir_tab[++i])
    {
      if ((ret = check_token(token, pos, redir_to_fill[i], this_redir_tab[i])) \
	  == 2)
      {
	if (modify_string(token, pos) == -1)
	  return (-1);
	return (0);
      }
      else if (ret == -1 || ret == 1)
	return (ret);
    }
  }
  return (2);
}
