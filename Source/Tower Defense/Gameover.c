#include "Gameover.h"

void gameover()
{
   BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
   int exit_screen = FALSE;
   int timer_espera = gametime;

   set_volume(255, 255);
   play_midi(SONG_gameover, FALSE);

   fps_timer = gametime - 9;

   while(!exit_program && !exit_screen)
   {
       if(gametime - fps_timer >= 8)
       {
          //INPUT
          Receive_Keyboard_Input();

          if(Pressed(KEY_ESC))
           Exit_Game();

          //UPDATE
          if(gametime - timer_espera >= 4000 || mouse_b == 1 || Pressed_Any_Key())
          {
             exit_screen = TRUE;
             screen_state = MAINMENU;
          }

          //DRAW
          draw_sprite(buffer, gameoverBG, 0, 0);

          if(mouse_on_screen())
          draw_sprite(buffer, cursor, mouse_x, mouse_y);

          draw_sprite(screen, buffer, 0, 0);
          clear(buffer);

          fps_timer = gametime;
       }
   }

   stop_midi();

   //FINALIZAÇÃO
   destroy_bitmap(buffer);

   //Fade entre telas
      fade_out(40);
      set_trans_blender(255,255,255,128);
}
