/*
** signal.c for signal_shell.c in /home/desrum_m/code/epitech/S2/PSU/42sh/PSU_2014_42sh/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.eu>
** 
** Started on  jeu. mai 07 11:45:25 2015 Martin Desrumaux
** Last update jeu. mai 07 11:45:25 2015 Martin Desrumaux
*/

#include		<signal.h>
#include		"lib.h"

/*
** Default signal_handler for shell
*/

void			signal_handler(int nbr)
{
  (void)nbr;
  my_putstr("\n> ");
}

/*
** signal_handler while executing a command
*/

void			signal_handler_cmd(int nbr)
{
  (void)nbr;
  my_putstr("\n");
}

/*
** Initialization of shell signal handler's
** signal(SIGCHLD, SIG_IGN);
**	Make kill the process after each execution
*/

void			init_signal_shell(void)
{
  signal(SIGINT, signal_handler);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
}

void			init_signal_prgrm(void)
{
  signal(SIGINT, SIG_DFL);
  signal(SIGQUIT, SIG_DFL);
  signal(SIGTTIN, SIG_DFL);
  signal(SIGTTOU, SIG_DFL);
  signal(SIGCHLD, SIG_DFL);
  signal(SIGTSTP, SIG_IGN);
}

/*
** This function set the global g_waitredir that is used to wait the
** doub left redir
*/

void			set_var(int nbr)
{
  extern int		g_waitredir;

  (void)nbr;
  g_waitredir = 1;
}
