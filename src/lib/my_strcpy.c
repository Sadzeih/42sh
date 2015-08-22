/*
** my_strcpy.c for my_strcpy.c in /home/thomas/rendu/PSU/PSU_2014_42sh/src/lib
** 
** Made by raout_t
** Login   <thomas@epitech.net>
** 
** Started on Thu May 21 11:58:10 2015 raout_t
** Last update Thu May 21 11:58:24 2015 raout_t
*/

char		*my_strcpy(char *dest, char *src)
{
  int		i;

  i = 0;
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      i++;
    }
  dest[i] = '\0';
  return (dest);
}
