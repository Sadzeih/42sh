/*
** lib.h for mysh in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1
** 
** Made by value
** Login   <desrum_m@epitech.net>
** 
** Started on  Mon Jan 19 17:03:33 2015 value
** Last update Sun May 24 01:56:46 2015 raout_t
*/

#ifndef			LIB_H_

# define		LIB_H_

int			my_putchar(char c);
int			my_strlen(char *str);
char			*my_strcat(char *dest, char *src);
void			my_putstr(char *str);
int			my_strncmp(char *s1, char *s2, int len);
char			*get_next_line(int fd);
void			my_putstrerr(char *str);
char			*my_strncat(char *dest, char *src, int nb);
int			my_getnbr(char *str);
int			my_strstrcmp(char **src, char **dest);
int			is_a_nbr(char *str);
char			**str_to_tab(char *str);
int			my_strcmp(char *s1, char *s2);
char			*my_strdup(char *str);
void			double_free_tab(char **);
char			**double_strdup(char **);
void			*print_and_return_ptr(void *err, char *str);
int			print_and_return_int(int err, char *str);

#endif			/* !LIB_H_ */
