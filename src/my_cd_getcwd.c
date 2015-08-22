/*
** getcwd.c for getcwd in /home/desrum_m/code/epitech/PSU/minishell1/PSU_2014_minishell1/getcwd
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  mer. janv. 21 18:07:41 2015 Martin Desrumaux
** Last update Sun May 24 22:13:01 2015 Francois Devos
*/

#include		<sys/types.h>
#include		<sys/stat.h>
#include		<dirent.h>
#include		<unistd.h>
#include		<stdlib.h>
#include		"mysh.h"
#include		"list.h"
#include		"lib.h"

/*
** Optimisation :
**	Test if the env PWD exist.
**	Test with lstat if it is the current directory
**	If it is remove the . and .. in the PWD if there are
**
**	Else
**	Use the below technique
*/

static char		*malloc_fill(char *name)
{
  char			*to_list;

  if ((to_list = malloc(my_strlen(name) + my_strlen("/") + 1)) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  to_list[0] = '\0';
  to_list = my_strcat(to_list, name);
  to_list = my_strcat(to_list, "/");
  to_list[my_strlen(to_list)] = '\0';
  return (to_list);
}

static int		init_vars(struct stat *stat_buf, \
				  struct stat *stat_begin, \
				  struct stat *stat_prev_buf, \
				  t_list **dir_list)
{
  stat_buf->st_ino = 0;
  stat_buf->st_dev = 0;
  *dir_list = NULL;
  if (lstat("/", stat_begin) == -1)
    return (-1);
  if (lstat(".", stat_prev_buf) == -1)
    return (-1);
  return (0);
}

int			save_found_value(struct dirent *dir_stat, \
					 t_list **dir_list, \
					 struct stat *stat_prev_buf, \
					 void *dir)
{
  void			*ret;

  if ((ret = malloc_fill(dir_stat->d_name)) == NULL)
    return (1);
  if (my_put_in_list_begin(dir_list, ret) == -1)
    return (1);
  if (lstat(".", stat_prev_buf) == -1)
    return (1);
  if ((closedir(dir)) == -1)
    return (1);
  return (0);
}

static t_list		*find_absolute_path(t_list *dir_list, void *dir)
{
  struct dirent		*dir_stat;
  struct stat		stat_prev_buf;
  struct stat		stat_buf;
  struct stat		stat_begin;

  dir = NULL;
  if (init_vars(&stat_buf, &stat_begin, &stat_prev_buf, &dir_list) == -1)
    return (NULL);
  while (stat_prev_buf.st_dev != stat_begin.st_dev || \
	 stat_prev_buf.st_ino != stat_begin.st_ino)
  {
    if (chdir("..") != 0)
      return (NULL);
    if ((dir = opendir(".")) == NULL)
      return (NULL);
    while ((stat_buf.st_ino != stat_prev_buf.st_ino || \
	  stat_buf.st_dev != stat_prev_buf.st_dev) && (dir_stat = readdir(dir)))
      if (lstat(dir_stat->d_name, &stat_buf) == -1)
	return (NULL);
    if (save_found_value(dir_stat, &dir_list, &stat_prev_buf, dir) == 1)
      return (NULL);
  }
  return (dir_list);
}

char			*my_getcwd(void)
{
  void			*ret;
  char			*absolute_path;
  t_list		*dir_list;

  dir_list = NULL;
  ret = NULL;
  if ((dir_list = find_absolute_path(dir_list, ret)) == NULL)
    return (NULL);
  if ((ret = malloc_fill("")) == NULL)
    return (NULL);
  if (my_put_in_list_begin(&dir_list, ret) == -1)
    return (NULL);
  if ((absolute_path = list_strcat(dir_list)) == NULL)
    return (NULL);
  free_list(dir_list);
  if ((chdir(absolute_path)) != 0)
    return (NULL);
  return (absolute_path);
}
