/*
** lexer.h for lexer in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Mon Jan 19 17:03:23 2015 value
** Last update Sun May 24 15:49:50 2015 Alexis Guerville
*/

#ifndef			LEXER_H_

# define		LEXER_H_

char			**list_to_doubletab(t_list *list);
int			malloc_cat_putlist_token(char *str, int i,\
					    t_list **list);
t_list			*lexer(char *str, char *sep, char **token);

#endif			/* !LEXER_H_ */
