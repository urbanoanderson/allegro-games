#include "pause.hpp"


///=======================================================
///MENU DE PAUSA
///=======================================================
int pausemenu(Background* BG, Mediaplayer* m)
{
  bool exit_screen = false;
  bool option = 0;

  play_sample(c->FX_pause, vol_SFX, 128, 1000, FALSE);
  set_volume(vol_SFX, vol_BGM - vol_BGM/3);

  timer_fps = milisegundos - 16;

  ///GAME LOOP
  while(!exit_screen && !exit_program)
  {
    if(milisegundos - timer_fps >= 8)
    {
      ///INPUT
      keyboard_input();
      xbox_input();

      if(just_pressed(KEY_DOWN) || xbox_just_pressed(DPAD_DOWN) || xbox_just_pressed(LSTICK_DOWN))
       { option = (!option); play_sample(c->FX_click1, vol_SFX, 128, 1000, FALSE); rest(30); }
      else if(just_pressed(KEY_UP) || xbox_just_pressed(DPAD_UP) || xbox_just_pressed(LSTICK_UP))
       { option = (!option); play_sample(c->FX_click1, vol_SFX, 128, 1000, FALSE); rest(30); }
      else if(just_pressed(KEY_ENTER) || xbox_just_pressed(BUTTON_A) || xbox_just_pressed(BUTTON_START))
       exit_screen = true;
      else if(just_pressed(KEY_F12) || xbox_just_pressed(BUTTON_BACK))
       mediaplayer_change_song(m);

      ///UPDATE

      ///DRAW
      BG->Draw();
      draw_sprite(buffer, c->pause_window, SCREEN_W/2 - c->pause_window->w/2, SCREEN_H/2 - c->pause_window->h/2);
      draw_sprite(buffer, c->pause_b_resume, SCREEN_W/2 - c->pause_b_resume->w/2, 200);
      draw_sprite(buffer, c->pause_b_mainmenu, SCREEN_W/2 - c->pause_b_mainmenu->w/2, 350);
      draw_sprite(buffer, c->pause_b_h, SCREEN_W/2 - c->pause_b_h->w/2, 200 + 150*option);
      textout_centre_ex(buffer, c->font_pause, "PAUSE", SCREEN_W/2, 110, makecol(255,255,255 ), -1);
      draw_sprite(screen, buffer, 0, 0);
      if(usevsync) vsync();
      clear(buffer);

     timer_fps = milisegundos;
    }
  }

  set_volume(vol_SFX, vol_BGM);

  if(!option)
   play_sample(c->FX_pause, vol_SFX, 128, 1000, FALSE);
  else
  { play_sample(c->FX_click3, vol_SFX, 128, 1000, FALSE); stop_midi(); rest(500); }

  return option;
}
