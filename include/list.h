/*
** list.h for list in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1/getcwd
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Wed Jan 21 18:42:56 2015 Martin Desrumaux
** Last update Mon May 11 13:11:05 2015 Alexis Guerville
*/

#ifndef			LIST_H_

# define		LIST_H_

typedef	struct		s_list
{
  void			*data;
  struct s_list		*next;
  struct s_list		*prev;
}			t_list;

typedef struct		s_elem
{
  struct s_elem		*prev;
  struct s_elem		*next;
  void			*data;
}			t_elem;

typedef struct		s_dlist
{
  t_elem		*start;
  t_elem		*end;
  int			length;
}			t_dlist;

t_dlist			*make_list(void);
t_elem			*init_elem(void * data);
void			add_elem(t_dlist *list, t_elem *elem);
void			add_elem_first(t_dlist *list, t_elem *elem);
void			rm_list(t_list **list, t_list **listbegin);

int			my_put_in_list_begin(t_list **list, void *str);
int			my_put_in_list_end(t_list **list, void *str);
void			free_list(t_list *list);

#endif			/* !LIST_H_ */
