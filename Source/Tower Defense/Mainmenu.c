#include "Mainmenu.h"

void mainmenu()
{
   BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
   int exit_screen = FALSE;

   //Botões
   Button* playbutton = Create_Button(main_b_play, main_b_play_h, 220, 550);
   Button* exitbutton = Create_Button(main_b_exit, main_b_exit_h, 520, 550);

   set_volume(255, 255);
   play_midi(SONG_mainmenu, TRUE);

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
          Update_Button(playbutton);
          Update_Button(exitbutton);

          if(exitbutton->ativado)
           Exit_Game();

          if(playbutton->ativado)
          {
              exit_screen = TRUE;
              screen_state = GAMESCREEN;
          }

          //DRAW
          draw_sprite(buffer, mainBG, 0, 0);
          Draw_Button(playbutton, buffer);
          Draw_Button(exitbutton, buffer);

          if(mouse_on_screen())
          draw_sprite(buffer, cursor, mouse_x, mouse_y);

          draw_sprite(screen, buffer, 0, 0);
          clear(buffer);

          fps_timer = gametime;
       }
   }

   stop_midi();

   //FINALIZAÇÃO
   Destroy_Button(playbutton);
   Destroy_Button(exitbutton);
   destroy_bitmap(buffer);
}
