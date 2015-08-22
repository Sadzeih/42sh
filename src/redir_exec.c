/*
** redir_exec.c for src in /home/desrum_m/code/epitech/S2/PSU/minishell2/PSU_2014_minishell2/src
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  dim. mars 08 18:25:24 2015 Martin Desrumaux
** Last update Sun May 24 22:32:50 2015 raout_t
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		<sys/stat.h>
#include		<fcntl.h>
#include		<signal.h>
#include		"mysh.h"
#include		"lib.h"

/*
** <unistd.h>			pipe
** <stdlib.h>			NULL
** <sys/stat.h> && <fcntl.h>	open && flags
** "lib.h"			my_putstrerr
*/

int			check_redir(t_redir *redir)
{
  if ((redir->right != NULL && redir->d_right != NULL) || \
      (redir->left != NULL && redir->d_left != NULL))
  {
    my_putstrerr("Ambiguous redirections.\n");
    return (1);
  }
  return (0);
}

int			right_redir(t_fd *fd, t_redir *redir)
{
  int			ret;
  struct stat		buf;

  if ((ret = open(redir->right, O_CREAT | O_WRONLY | O_TRUNC, 00644)) == -1)
  {
    my_putstrerr("Can't redirect to ");
    my_putstrerr(redir->right);
    if ((stat(redir->right, &buf)) != -1 && S_ISDIR(buf.st_mode))
      my_putstrerr(" : Is a directory.\n");
    else if (access(redir->right, W_OK) == 0)
      my_putstrerr(" : No write permissions.\n");
    else
      my_putstrerr(" : File doesn't exist.\n");
    return (1);
  }
  fd->out = ret;
  return (0);
}

int			dright_redir(t_fd *fd, t_redir *redir)
{
  int			ret;
  struct stat		buf;

  if ((ret = open(redir->d_right, O_CREAT | O_WRONLY | O_APPEND, 00644)) \
      == -1)
  {
    my_putstrerr("Can't redirect to ");
    my_putstrerr(redir->d_right);
    if ((stat(redir->d_right, &buf)) != -1 && S_ISDIR(buf.st_mode))
      my_putstrerr(" : Is a directory.\n");
    else if (access(redir->d_right, W_OK) == 0)
      my_putstrerr(" : No write permissions.\n");
    else
      my_putstrerr(" : File doesn't exist.\n");
    return (1);
  }
  fd->out = ret;
  return (0);
}

int			left_redir(t_fd *fd, t_redir *redir)
{
  int			ret;

  if ((ret = open(redir->left, O_RDONLY)) != -1)
    fd->in = ret;
  else
  {
    my_putstrerr("Can't open ");
    my_putstrerr(redir->left);
    if (access(redir->left, R_OK) == 0)
      my_putstrerr(" : No read permissions.\n");
    else
      my_putstrerr(" : File doesn't exist.\n");
    return (1);
  }
  return (0);
}

int			dleft_redir(t_fd *fd, t_redir *redir)
{
  int			file_d;
  char			*line;
  pid_t			ppid;

  if ((file_d = open("/tmp/redir_dleft.tmp",\
		     O_CREAT | O_WRONLY | O_TRUNC, 00644)) == -1)
    return (print_and_return_int(1, "Open failed.\n"));
  write(0, "? ", 2);
  while ((line = get_next_line(0)) && my_strcmp(line, redir->d_left) != 0)
  {
    write(0, "? ", 2);
    write(file_d, line, my_strlen(line));
    write(file_d, "\n", 1);
  }
  close(file_d);
  ppid = getppid();
  if (isatty(0))
    kill(ppid, SIGUSR1);
  if ((file_d = open("/tmp/redir_dleft.tmp", O_RDONLY)) == -1)
    return (print_and_return_int(1, "Open failed.\n"));
  fd->in = file_d;
  return (0);
}
