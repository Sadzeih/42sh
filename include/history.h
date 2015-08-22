/*
** history.h for history in /home/devos-f/Documents/Projet/PSU_2014_42sh/include
** 
** Made by Francois Devos
** Login   <devos_f@epitech.net>
** 
** Started on  Mon May 18 13:33:49 2015 Francois Devos
** Last update Fri May 22 13:21:08 2015 Francois Devos
*/

#ifndef			HISTORY_H_
# define		HISTORY_H_

int			aff_history(char ***env, char **lexed);
int			write_history(char *cmd);
char			**my_built_in_history(char **lexed);
int			size_dtab(char **tab);
int			nb_line(char *cmd);
void			print_lexed(char **lexed);
char			**create_new_cmd(char **lexed, char *cmd);
char			*generate_string(char **lexed);
char			**double_excla_mark(char **lexed);
char			**excla_double_point_minus(int nb_word, char \
						   **cmd_tmp, char **lexed);
char			**excla_double_point(char **lexed, char *cmd);
char			**check_history_replacement(char **lexed);
char			**excla_dollar(char **lexed);
char			**excla_star(char **lexed);
char			**excla_mark_nbr(char **lexed, char *cmd);
char			**excla_mark_text(char **lexed);
char			**excla_inter_mark_text(char **lexed);

#endif			/* !HISTORY_H_ */
