/*
** get_next_line.c for get_next_line.c in /home/thomas/rendu/PSU/PSU_2014_42sh/src/lib
** 
** Made by raout_t
** Login   <thomas@epitech.net>
** 
** Started on Thu May 21 11:56:54 2015 raout_t
** Last update Sun May 24 22:40:42 2015 Francois Devos
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	"get_next_line.h"
#include	"lib.h"

int		put_buf_in_line(char *buffer, char *save, char *line)
{
  int		i;
  int		j;

  i = 0;
  j = my_strlen(line);
  while (buffer[i] != '\0')
    {
      if (buffer[i] == '\n' || j == MALLOC_SIZE)
	{
	  line[j] = '\0';
	  if (buffer[i] == '\n')
	    i++;
	  my_strcpy(save, buffer + i);
	  return (0);
	}
      line[j] = buffer[i];
      j++;
      i++;
    }
  save[0] = '\0';
  line[j] = '\0';
  return (1);
}

char		*get_next_line(const int fd)
{
  static char	save[BUFFER];
  char		buffer[BUFFER + 1];
  int		ret;
  char		*line;

  if ((line = malloc(sizeof(char) * MALLOC_SIZE)) == NULL)
    return (print_and_return_ptr(NULL, "Malloc failed.\n"));
  line[0] = '\0';
  if (put_buf_in_line(save, save, line) == 0)
    return (line);
  while ((ret = read(fd, buffer, BUFFER)) > 0)
    {
      buffer[ret] = '\0';
      if (put_buf_in_line(buffer, save, line) == 0)
	return (line);
    }
  if (line != NULL && line[0] != '\0')
    return (line);
  return (NULL);
}
