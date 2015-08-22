/*
** get_next_line.h for get_next_line in /home/desrum_m/rendu/GetNextLine/CPE_2014_get_next_line
** 
** Made by Martin Desrumaux
** Login   <desrum_m@epitech.net>
** 
** Started on  Mon Nov 17 02:10:34 2014 Martin Desrumaux
** Last update Thu May 21 12:10:56 2015 raout_t
*/

#ifndef			GET_NEXT_LINE_H_

# define		GET_NEXT_LINE_H_

# define		MALLOC_SIZE 4096
# define		BUFFER 8

char			*my_strcpy(char *src, char *dest);
char			*get_next_line(const int fd);
int			malloc_getnl(int fd);
char			*concatenate(char *save, char *buffer, int fd);
unsigned int		my_nput_this_nstr(char *in, unsigned int i,
					  char *out, unsigned int j);

#endif			/* !GET_NEXT_LINE_H_ */
