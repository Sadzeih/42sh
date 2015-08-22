/*
** aliases_tools.c for aliases_tools.c in /home/thomas/rendu/PSU/PSU_2014_42sh/src/lib
** 
** Made by raout_t
** Login   <thomas@epitech.net>
** 
** Started on Sun May 24 01:53:57 2015 raout_t
** Last update Sun May 24 16:15:19 2015 raout_t
*/

#include		<stdlib.h>
#include		"lib.h"
#include		"aliases.h"

extern	t_aliases	*g_aliases;

int			my_strstrcmp(char **src, char **dest)
{
  int			i;

  i = 0;
  while (src[i] != NULL && dest[i] != NULL)
    {
      if ((my_strcmp(src[i], dest[i])) == 0)
	i++;
      else
	return (1);
    }
  if (src[i] == NULL && dest[i] == NULL)
    return (0);
  return (1);
}

char			*my_strcat_char(char *top, char *tail, char border)
{
  int			i;
  int			j;
  char			*final;

  if (top == NULL || tail == NULL)
    return (NULL);
  i = my_strlen(top);
  j = my_strlen(tail);
  if ((final = malloc(sizeof(char) * (i + j + 2))) == NULL)
    return (NULL);
  i = 0;
  j = 0;
  while (top[i])
    {
      final[i] = top[i];
      i++;
    }
  final[i++] = border;
  while (tail[j])
    final[i++] = tail[j++];
  final [i] = '\0';
  return (final);
}

char			**str_to_tab(char *str)
{
  char			**tab;

  if ((tab = malloc(sizeof(char *) * 2)) == NULL)
    return (NULL);
  if ((tab[0] = my_strdup(str)) == NULL)
    return (NULL);
  tab[1] = NULL;
  return (tab);
}

int			search_alias(char *str)
{
  t_aliases		*tmp;

  tmp = g_aliases;
  while (tmp != NULL)
    {
      if (my_strcmp(str, tmp->alias) == 0)
	return (0);
      tmp = tmp->next;
    }
  return (0);
}
