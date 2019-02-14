#include "challenge.hpp"

void challenge(float* angle)
{
    bool exit_screen = false;

    enum { NO_SHOOTING, NO_SHIELD, CHUCK_NORRIS, BACK };
    const char* optext[] = { "NO SHOOTING", "NO SHIELD", "CHUCK NORRIS", "BACK", NULL };
    int option = NO_SHOOTING;
    set_trans_blender(255, 255, 255, 100);

    timer_fps = milisegundos - 16;

    ///GAMELOOP
    while(!exit_screen && !exit_program)
    {
      if(milisegundos - timer_fps >= 8)
      {
          ///INPUT
          keyboard_input();
          xbox_input();

		  if(just_pressed(KEY_ESC) || xbox_just_pressed(BUTTON_B))
           exit_screen = true;
          else if(just_pressed(KEY_UP) || xbox_just_pressed(LSTICK_UP) || xbox_just_pressed(DPAD_UP))
          { option--; play_sample(c->FX_click1, vol_SFX, 128, 1000, FALSE); }
          else if(just_pressed(KEY_DOWN) || xbox_just_pressed(LSTICK_DOWN) || xbox_just_pressed(DPAD_DOWN))
          { option++; play_sample(c->FX_click1, vol_SFX, 128, 1000, FALSE); }

          if(just_pressed(KEY_ENTER) || xbox_just_pressed(BUTTON_START) || xbox_just_pressed(BUTTON_A))
          {
             exit_screen = true;
             play_sample(c->FX_click3, vol_SFX, 128, 1000, FALSE);

             if(option == NO_SHOOTING)
              gamescreen(CHALLENGE1);
             else if(option == NO_SHIELD)
              gamescreen(CHALLENGE2);
             else if(option == CHUCK_NORRIS)
              gamescreen(CHALLENGE3);
          }

          ///UPDATE
          *angle += 0.35;

          if(option > 3)
            option = 0;
          else if(option < 0)
            option = 3;

          ///DRAW
          pivot_sprite(buffer, c->main_BG, SCREEN_W/2, SCREEN_H/2, c->main_BG->w/2, c->main_BG->h/2, ftofix(*angle));
          draw_sprite(buffer, c->main_logo, SCREEN_W/2 - c->main_logo->w/2, 50);

        if(!exit_screen)
        {
          for(int i = 0, lin = 350; optext[i] != NULL; i++, lin += (text_height(c->font_options) + 15))
          {
            textout_centre_ex(buffer, c->font_options, optext[i], SCREEN_W/2, lin, makecol(180,180,180), -1);
            textout_centre_ex(buffer, c->font_options, optext[i], SCREEN_W/2+1, lin+1, makecol(255,255,255), -1);

            if(option == i)
            {
              textout_centre_ex(buffer, c->font_options, optext[i], SCREEN_W/2, lin, makecol(255,255,0), -1);
              textout_centre_ex(buffer, c->font_options, optext[i], SCREEN_W/2+1, lin+1, makecol(255,250,120), -1);
              draw_trans_sprite(buffer, c->main_selection, 0, (lin-4));
            }
          }
        }

          draw_sprite(screen, buffer, 0,0);
          if(usevsync) vsync();
          clear(buffer);

      timer_fps = milisegundos;
      }
    }
}
