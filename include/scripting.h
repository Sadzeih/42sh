/*
** scripting.h for scripting.h in /home/thomas/rendu/PSU/PSU_2014_42sh
** 
** Made by raout_t
** Login   <thomas@epitech.net>
** 
** Started on Mon May 18 15:24:27 2015 raout_t
** Last update Fri May 22 11:48:19 2015 raout_t
*/

#ifndef			SCRIPTING_H_

# define		SCRIPTING_H_

typedef	struct		s_vars
{
  char			*name;
  char			*value;
  struct s_vars		*next;
}			t_vars;

int			my_set(char ***env, char **lexed);
int			my_unset(char ***env, char **lexed);

#endif			/* !SCRIPTING_H_ */
