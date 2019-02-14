#include "help.hpp"

///************************************
///TELA DE AJUDA
///************************************
void help(float* angle)
{
    bool exit_screen = false;

    const char* texto[] =
    {
       "STORY",
       "IN THE YEAR 3000, ALIENS HAVE ATTACKED PLANET EARTH TO USE OUR",
       "RESOURCES. THE HUMAN RACE WAS ALMOST EXTINCT AND YOUR ONLY",
       "HOPE IS MAYBE ESCAPE BEFORE IS TOO LATE. BUT UNFORTUNATELY THIS",
       "MAY ALSO BE A SUICIDE MISSION...",
       "",
       "OBJECTIVE",
       "LAST SURVIVOR IS SPACE SHOOTING GAME. YOUR GOAL IS TO SURVIVE",
       "AS LONG AS YOU CAN. GOOD LUCK.",
       "",
       "CONTROLS",
       " - USE ARROW KEYS OR L-STICK ANALOG TO MOVE THE SHIP.",
       " - PRESS THE 'A' KEY OR 'A' BUTTON ON THE XBOX CONTROLLER TO SHOOT",
       "  OR HOLD IT TO CHARGE THE SHOT.",
       " - PRESS 'SPACE' KEY OR 'RB' BUTTON ON THE XBOX CONTROLLER TO",
       "  USE THE ENERGY SHIELD.",
       " - PRESS 'F12' KEY OR 'BACK' BUTTON ON THE XBOX CONTROLLER TO",
       "  CHANGE THE SONG DURING GAMEPLAY.",
       NULL
    };

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

          ///UPDATE
          *angle += 0.35;

          ///DRAW
          pivot_sprite(buffer, c->main_BG, SCREEN_W/2, SCREEN_H/2, c->main_BG->w/2, c->main_BG->h/2, ftofix(*angle));

          for(int i = 0, lin = 170; texto[i] != NULL; i++, lin += (text_height(c->font_help) + 5))
            textout_justify_ex(buffer, c->font_help, texto[i], 100, 500, lin, 10, makecol(255, 255, 255), -1);

          textout_ex(buffer, c->font_help, "Created by Anderson Urbano", 10, SCREEN_H - text_height(c->font_help), makecol(255, 255, 255), -1);
          textout_right_ex(buffer, c->font_help, "Version 1.09", SCREEN_W - 2, SCREEN_H - text_height(c->font_help), makecol(255, 255, 255), -1);
          textprintf_centre_ex(buffer, c->font_title_options, SCREEN_W/2, 30, makecol(200,200,200), -1, "HELP");
          textprintf_centre_ex(buffer, c->font_title_options, SCREEN_W/2+2, 30+2, makecol(255,250,120), -1, "HELP");
          draw_sprite(screen, buffer, 0,0);
          if(usevsync) vsync();
          clear(buffer);

      timer_fps = milisegundos;
      }
    }
}
