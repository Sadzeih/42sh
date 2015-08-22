/*
** main.c for src in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  lun. janv. 19 14:44:30 2015 Martin Desrumaux
** Last update Fri Jun  5 15:45:45 2015 devos_f
*/

#include		<stdlib.h>
#include		<signal.h>
#include		"lib.h"
#include		"list.h"
#include		"mysh.h"
#include		"scripting.h"
#include		"history.h"
#include		"aliases.h"
#include		"globbing.h"
#include		"line.h"

t_aliases		*g_aliases;
t_vars			*g_vars;
t_dlist			*g_history;
t_elem			*g_pos_history;
t_line			*g_line;
pid_t			g_pgid;

/*
** signal		: <signal.h>
** NULL			: <stdlib.h>
** isatty		: <unistd.h>
*/

/*
** write every command in history list
*/

char			**maj_and_check_lexed(char **lexed, char ***env,\
					      int *ret)
{
  char			*tmp;

  if ((lexed = check_history_replacement(lexed)) == NULL)
    return (print_and_return_ptr(NULL, "Event not found.\n"));
  if ((tmp = generate_string(lexed)) == NULL && (*ret = -1))
    return (NULL);
  if ((write_history(tmp)) == -1 && (*ret = -1))
    return (NULL);
  free(tmp);
  g_pos_history = g_history->end;
  if ((lexed = globbing(lexed, env)) == NULL)
    return (NULL);
  if (lexed[0] != NULL && my_strcmp(lexed[0], "alias") == 0)
    {
      if (my_alias(env, lexed, ret) == -1 && (*ret = -1))
	return (NULL);
    }
  else if (lexed[0] != NULL && my_strcmp(lexed[0], "unalias") == 0)
    if (my_unalias(env, lexed, ret) == -1 && (*ret = -1))
      return (NULL);
  if ((lexed = check_alias(lexed)) == NULL && (*ret = -1))
    return (NULL);
  return (lexed);
}

int			exec_line(char ***env, char *out)
{
  char			**token;
  char			**lexed;
  t_tree		*tree;
  int			ret;

  ret = 0;
  tree = NULL;
  if ((token = str_to_token("||#|#&&#;#>>#>#<<#<")) == NULL)
    return (-1);
  if ((lexed = lexing(out,  " \t", token)) == NULL)
    return (0);
  if ((lexed = maj_and_check_lexed(lexed, env, &ret)) == NULL || ret != 0)
    return (ret);
  if (lexed[0] != NULL && cmd_check(lexed, token) == 0)
    {
      if (fill_tree(lexed, &tree, tokenlen(lexed)) == -1)
	return (-1);
      ret = exec_tree(tree, env);
      free_tree(tree);
    }
  double_free_tab(token);
  double_free_tab(lexed);
  return (ret);
}

int			loop(char ***env)
{
  char			*out;
  int			ret;
  extern pid_t		g_pgid;

  ret = 0;
  init_signal_shell();
  while ((out = line_edition(*env)))
  {
    init_signal_shell();
    if ((ret = exec_line(env, out)) < 0)
    {
      if (g_pgid != 0)
	kill(g_pgid, SIGTERM);
      return (ret);
      signal(SIGUSR1, SIG_DFL);
    }
    if (isatty(0) == 1)
      my_putstr("> ");
    free(out);
  }
  if (ret >= 0 && isatty(0) == 1)
    my_putstr("exit\n");
  return (ret);
}

int			main(int ac, char **av, char **env)
{
  char			*pwd;
  int			ret;

  ret = 0;
  (void)ac;
  (void)av;
  if ((env = double_strdup(env)) == NULL)
    return (1);
  if ((g_history = make_list()) == NULL)
    return (-1);
  if ((pwd = my_getcwd()) != NULL)
    {
      if ((env = my_setenv(env, "PWD", pwd, 1)) == NULL)
	return (-1);
      free(pwd);
    }
  if (isatty(0) == 1)
    my_putstr("> ");
  g_aliases = NULL;
  g_vars = NULL;
  ret = loop(&env);
  double_free_tab(env);
  return (ret + 256 * 2);
}
