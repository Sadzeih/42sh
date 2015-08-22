/*
** mysh.h for mysh in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Mon Jan 19 17:03:23 2015 value
** Last update Sun May 24 18:38:46 2015 Alexis Guerville
*/

#ifndef			MYSH_H_

# define		MYSH_H_

# define		ABS(X)	( (X) < 0 ? (-X) : (X) )

# include		"list.h"

typedef struct		s_tree
{
  char			**cmd;
  struct s_tree		*left;
  struct s_tree		*right;
}			t_tree;

typedef	struct		s_fd
{
  int			in;
  int			out;
  int			err;
}			t_fd;

typedef struct		s_redir
{
  char			*right;
  char			*d_right;
  char			*left;
  char			*d_left;
}			t_redir;

typedef	struct		s_pipe_fd
{
  int			before[2];
  int			next[2];
}			t_pipe_fd;

void			signal_handler_cmd(int nbr);
void			set_var(int nbr);
void			init_signal_shell(void);
void			init_signal_prgrm(void);
void			signal_handler(int nbr);
char			*my_parsenv(char **env, char *keyword);
int			my_env(char **env);
char			**my_setenv(char **env, char *name, char *value, \
				    int overwrite);
char			**my_unsetenv(char **env, char *name);
char			*list_strcat(t_list *list);
char			*my_getcwd(void);
int			my_cd(char ***env, char *name);
int			my_exit_cmd(char ***env, char **lexed);
int			my_echo(char ***env, char **lexed);
char			**lexing(char *str, char *sep, char **token);
char			**str_to_token(char *str);
t_list			*lexer(char *str, char *sep, char **token);
int			my_setenv_cmd(char ***env, char **lexed);
int			my_unsetenv_cmd(char ***env, char **lexed);
int			my_cd_cmd(char ***env, char **lexed);
int			is_built_in(char **lexed, char ***env);
int			is_built_in_child(char **lexed, char ***env, \
					  t_redir *redir);
int			execute_redir(t_redir *redir, t_fd *fd);
int			execute(char **lexed, char ***env, t_redir *redir, \
				char *exec_test);
int			execute_builtin(int (*func)(char ***env, char **lexed), \
					char **lexed, char ***env, \
					t_redir *redir);
int			is_path(char **lexed, char ***env, t_redir *redir);
char			**dup_double_ntab(char **dtab, int size);
int			fill_tree(char **lexed, t_tree **tree, \
				  int token_pos_end);
int			exec_tree_exec_type(char **cmd, char ***env);
int			exec_tree_pipeline(t_tree *tree, char ***env);
int			exec_tree_pipeline_exec_cmd(t_list **pipeline, \
						    t_list **pipeline_prev, \
						    t_pipe_fd *pipe_fd, \
						    char ***env);
int			exec_tree(t_tree *tree, char ***env);
int			exec_tree_comma(t_tree *tree, char ***env);
int			exec_tree_and(t_tree *tree, char ***env);
int			exec_tree_or(t_tree *tree, char ***env);
int			free_tree(t_tree *tree);
int			tokenlen(char **token);
int			init_struct_redir(t_redir *redir);
int			detect_struct_redir(char ***token, t_redir *redir);
int			cmd_check(char **lexed, char **token);
int			right_redir(t_fd *fd, t_redir *redir);
int			dright_redir(t_fd *fd, t_redir *redir);
int			left_redir(t_fd *fd, t_redir *redir);
int			dleft_redir(t_fd *fd, t_redir *redir);
int			check_redir(t_redir *redir);

#endif			/* !MYSH_H_ */
