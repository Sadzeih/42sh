/*
** termcaps.h for 42sh in /home/guervi-a/rendu/Sys_Unix/PSU_2014_42sh/include
** 
** Made by Alexis Guerville
** Login   <guervi_a@epitech.net>
** 
** Started on  Mon May  4 17:03:06 2015 Alexis Guerville
** Last update Sun May 24 16:20:18 2015 Alexis Guerville
*/

#ifndef			TERMCAPS_H_

# define		TERMCAPS_H_

#include		<termios.h>
#include		<unistd.h>

# define K_LEFT		4479771
# define K_RIGHT	4414235
# define K_DEL		127
# define K_UP		4283163
# define K_DOWN		4348699
# define CTRL_A		1
# define CTRL_E		5
# define CTRL_B		2
# define ALT_B		25115
# define CTRL_F		6
# define ALT_F		26139
# define CTRL_U		21
# define CTRL_K		11
# define CTRL_W		23
# define CTRL_L		12
# define ENTER		10
# define CTRL_D		4

typedef struct		s_line
{
  int			length;
  struct termios	save;
  struct termios	new;
  char			*cmd;
  int			keys[15];
  int			pos;
  int			buffer;
}			t_line;

int			get_termcaps(char **env);
int			set_termcaps(int status);
int			cap(char *str);
int			cap_multi_line(void);
int			line_ret(void);
char			*line_edition(char **env);
void			init_actions(int (*key_actions[15])(void));
void			init_keys(void);
void			free_line(int code);

int			get_width(void);
int			clear_display(void);
int			add_char(void);
int			del_char(void);
int			move_to_cursor(void);
int			move_left(void);
int			move_right(void);
int			move_start(void);
int			move_start_word(void);
int			move_end_word(void);
int			move_end(void);
int			clear_line(void);
int			clear_scrn(void);
int			clear_end_line(void);
int			clear_start_line(void);
int			history_up(void);
int			history_down(void);

#endif			/* !TERMCAPS_H_ */
