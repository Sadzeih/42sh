/*
** aliases.h for aliases.h in /home/thomas/rendu/PSU/aliases
** 
** Made by raout_t
** Login   <thomas@epitech.net>
** 
** Started on Fri May 22 17:09:49 2015 raout_t
** Last update Sun May 24 17:12:25 2015 raout_t
*/

#ifndef			ALIASES_H_

# define		ALIASES_H_

typedef	struct		s_aliases
{
  char			*alias;
  char			**cmd;
  struct s_aliases	*next;
}			t_aliases;

char			**check_alias(char **lexed);
char			*my_strcat_char(char *top, char *tail, char border);
int			search_alias(char *str);
int			my_alias(char ***env, char **lexed, int *ret);
int			size_dtab(char **tab);
int			my_unalias(char ***env, char **lexed, int *ret);

#endif			/* !ALIASES_H_ */
