#include "init.hpp"
#include "help.hpp"
#include "challenge.hpp"
#include "highscore_screen.hpp"
#include "gamescreen.hpp"
#include "optionscreen.hpp"

int main()
{
  if(!init())
   return -1;

  bool exit_screen = false;
  enum { ARCADE, CHALLENGE, HIGHSCORES, HELP, OPTIONS, EXIT };
  const char* optext[] = { "ARCADE", "CHALLENGE", "HIGHSCORES", "HELP", "OPTIONS", "EXIT", NULL };
  int option = ARCADE;
  float angle = 0.0;

  play_midi(c->SONG_mainmenu, TRUE);

  timer_fps = milisegundos - 16;

  ///GAMELOOP
  while(!exit_screen && !exit_program)
  {
      if(milisegundos - timer_fps >= 8)
      {
          ///INPUT
          keyboard_input();
          xbox_input();

		  if(just_pressed(KEY_DOWN) || xbox_just_pressed(DPAD_DOWN) || xbox_just_pressed(LSTICK_DOWN))
		  { option++;  play_sample(c->FX_click1, vol_SFX, 128, 1000, FALSE); }
		  else if(just_pressed(KEY_UP) || xbox_just_pressed(DPAD_UP) || xbox_just_pressed(LSTICK_UP))
		  { option--;  play_sample(c->FX_click1, vol_SFX, 128, 1000, FALSE); }

		  else if(just_pressed(KEY_ENTER) || xbox_just_pressed(BUTTON_A) || xbox_just_pressed(BUTTON_START))
		  {
		     play_sample(c->FX_click3, vol_SFX, 128, 1000, FALSE);

		     if(option == ARCADE)
			 { stop_midi(); gamescreen(ARCADE_MODE); play_midi(c->SONG_mainmenu, TRUE); }
			 else if(option == CHALLENGE)
             { challenge(&angle); }
			 else if(option == HELP)
             { help(&angle); }
             else if(option == HIGHSCORES)
             { highscore_screen(&angle); }
			 else if(option == OPTIONS)
             { optionscreen(&angle); }
             else if(option == EXIT)
			  exit_program = true;
		  }

          ///UPDATE
          angle += 0.35;

          if(midi_pos < 0)
           play_midi(c->SONG_mainmenu, TRUE);


          if(option > EXIT)
		   option = ARCADE;
		  else if(option < ARCADE)
           option = EXIT;

          ///DRAW
          pivot_sprite(buffer, c->main_BG, SCREEN_W/2, SCREEN_H/2, c->main_BG->w/2, c->main_BG->h/2, ftofix(angle));
          draw_sprite(buffer, c->main_logo, SCREEN_W/2 - c->main_logo->w/2, 50);

          for(int i = 0, lin = 280; optext[i] != NULL; i++, lin += (text_height(c->font_options) + 20))
          {
            textout_centre_ex(buffer, c->font_options, optext[i], SCREEN_W/2, lin, makecol(180,180,180), -1);
            textout_centre_ex(buffer, c->font_options, optext[i], SCREEN_W/2+1, lin+1, makecol(255,255,255), -1);

            if(option == i)
            {
              textout_centre_ex(buffer, c->font_options, optext[i], SCREEN_W/2, lin, makecol(255,255,0), -1);
              textout_centre_ex(buffer, c->font_options, optext[i], SCREEN_W/2+1, lin+1, makecol(255,250,120), -1);
              set_trans_blender(255,255,255,100);
              draw_trans_sprite(buffer, c->main_selection, 0, (lin-4));
            }
          }

          draw_sprite(screen, buffer, 0,0);
          if(usevsync) vsync();
          clear(buffer);

      timer_fps = milisegundos;
      }
  }

  deinit();
  return 0;
}
END_OF_MAIN();
