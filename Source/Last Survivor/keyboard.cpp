#include "keyboard.hpp"

int prev_keystate[KEY_MAX];

void keyboard_input()
{
   for(int i = 0; i < KEY_MAX; i++)
     prev_keystate[i] = key[i];

   poll_keyboard();
}

int is_pressed(int KEY)
{
  return(prev_keystate[KEY] == 1 && prev_keystate[KEY] == key[KEY]);
}

int just_pressed(int KEY)
{
  return(prev_keystate[KEY] == FALSE && key[KEY] == TRUE);
}

int just_pressed_any_key()
{
  int retorno = FALSE;
  int i;

  for(i = 0; i < KEY_MAX; i++)
   retorno = (retorno || key[i] > prev_keystate[i]);

  return retorno;
}

int just_released(int KEY)
{
  return(prev_keystate[KEY] == TRUE && key[KEY] == FALSE);
}
