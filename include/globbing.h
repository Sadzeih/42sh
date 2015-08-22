/*
** globbing.h for globbing in /home/devos-f/Documents/Projet/PSU_2014_42sh/include
** 
** Made by Francois Devos
** Login   <devos_f@epitech.net>
** 
** Started on  Tue May 19 11:42:53 2015 Francois Devos
** Last update Fri Jun  5 12:03:42 2015 devos_f
*/

#ifndef		GLOBBING_H_
# define	GLOBBING_H_

#include	<glob.h>

int		create_glob_env_tilde(t_dlist *, char ***);
int		check_dleft(char **);
int		check_sign(char);
char		*recup_env(char ***, char*);
void		free_dlist(t_dlist *);
int		not_found(char **, int, char *, char *);
int		create_glob(char **, t_dlist *, char *);
int		create_glob_env(char **, t_dlist *, char *, char ***);
int		scan_tab(t_dlist *, char **, int, char ***);
char		**dlist_to_tab(t_dlist *);
char		**globbing(char **, char ***);
int		add_in_list(char *, t_dlist *);

#endif		/* !GLOBBING_H_ */
