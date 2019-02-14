#include "Keyboard.h"

void Receive_Keyboard_Input()
{
   int i;
   for(i = 0; i < KEY_MAX; i++)
     prev_keys[i] = key[i];

   poll_keyboard();
}

int Pressed_Any_Key()
{
   int i;
   for(i = 0; i < KEY_MAX; i++)
   {
      if(Pressed(i))
       return TRUE;
   }

   return FALSE;
}

int Pressed(int Key)
{
    return(prev_keys[Key] == 0 && key[Key] != 0);
}

int Holding(int Key)
{
    return(prev_keys[Key] != 0 && key[Key] != 0);
}

int Released(int Key)
{
    return(prev_keys[Key] != 0 && key[Key] == 0);
}
