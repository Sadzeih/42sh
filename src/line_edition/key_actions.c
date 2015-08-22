/*
** key_actions.c for 42sh in /home/guervi-a/rendu/Sys_Unix/PSU_2014_42sh
** 
** Made by Alexis Guerville
** Login   <guervi_a@epitech.net>
** 
** Started on  Fri May 15 17:59:00 2015 Alexis Guerville
** Last update Sat May 23 08:33:17 2015 Alexis Guerville
*/

#include	"line.h"
#include	"history.h"

extern t_line	*g_line;

void		init_keys(void)
{
  g_line->keys[0] = K_LEFT;
  g_line->keys[1] = K_RIGHT;
  g_line->keys[2] = K_DEL;
  g_line->keys[3] = K_UP;
  g_line->keys[4] = K_DOWN;
  g_line->keys[5] = CTRL_A;
  g_line->keys[6] = CTRL_E;
  g_line->keys[7] = CTRL_B;
  g_line->keys[8] = ALT_B;
  g_line->keys[9] = CTRL_F;
  g_line->keys[10] = ALT_F;
  g_line->keys[11] = CTRL_U;
  g_line->keys[12] = CTRL_K;
  g_line->keys[13] = CTRL_W;
  g_line->keys[14] = CTRL_L;
}

void		init_actions(int (*key_actions[15])(void))
{
  key_actions[0] = &move_left;
  key_actions[1] = &move_right;
  key_actions[2] = &del_char;
  key_actions[3] = &history_up;
  key_actions[4] = &history_down;
  key_actions[5] = &move_start;
  key_actions[6] = &move_end;
  key_actions[7] = &move_left;
  key_actions[8] = &move_start_word;
  key_actions[9] = &move_right;
  key_actions[10] = &move_end_word;
  key_actions[11] = &clear_line;
  key_actions[12] = &clear_end_line;
  key_actions[13] = &clear_start_line;
  key_actions[14] = &clear_scrn;
}
