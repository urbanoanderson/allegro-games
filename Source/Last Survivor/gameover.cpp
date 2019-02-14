#include "gameover.hpp"

///==============================
///GAMEOVER
///==============================
void gameover(Background* BG, int player_score, int final_time, int flag)
{
  bool exit_screen = false;
  int gameover_time = milisegundos;

  //Highscores
  int colocacao = pontuacoes.Determine_Position(final_time, flag);
  string nome = (string) "AAAA";
  int pos_str = 0;
  BITMAP* ret = create_bitmap(text_length(c->font_highscores, "A")+5, text_height(c->font_highscores)/3);
  clear_to_color(ret, makecol(255,255,255));
  char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
  int pos_carac[4] = { 0, 0, 0, 0 };

  timer_fps = milisegundos - 16;

  ///GAME LOOP
  while(!exit_screen && !exit_program)
  {
    if(milisegundos - timer_fps >= 8)
    {
      ///INPUT
      keyboard_input();
      xbox_input();

      if((milisegundos - gameover_time >= 25) && (milisegundos - gameover_time <= 30))
       play_sample(c->VOICE_gameover, vol_SFX, 128, 1000, FALSE);

      if(colocacao == -1)
      {
        if((just_pressed_any_key() || xbox_just_pressed_any_button()) && (milisegundos - gameover_time >= 550))
         exit_screen = true;
      }
      else
      {
         if(just_pressed(KEY_UP) || xbox_just_pressed(DPAD_UP) || xbox_just_pressed(LSTICK_UP))
          { pos_carac[pos_str]++; play_sample(c->FX_click4, vol_SFX, 128, 1000, FALSE); }
         else if(just_pressed(KEY_DOWN) || xbox_just_pressed(DPAD_DOWN) || xbox_just_pressed(LSTICK_DOWN))
          { pos_carac[pos_str]--;  play_sample(c->FX_click4, vol_SFX, 128, 1000, FALSE); }

         if(just_pressed(KEY_LEFT) || xbox_just_pressed(DPAD_LEFT) || xbox_just_pressed(LSTICK_LEFT))
          { pos_str--; play_sample(c->FX_click4, vol_SFX, 128, 1000, FALSE); }
         else if(just_pressed(KEY_RIGHT) || xbox_just_pressed(DPAD_RIGHT) || xbox_just_pressed(LSTICK_RIGHT))
          { pos_str++; play_sample(c->FX_click4, vol_SFX, 128, 1000, FALSE); }

         if(just_pressed(KEY_ENTER) || xbox_just_pressed(BUTTON_START) || xbox_just_pressed(BUTTON_A))
          { exit_screen = true; play_sample(c->FX_click3, vol_SFX, 128, 1000, FALSE); }
      }

      ///UPDATE
      if(pos_str > 3)
        pos_str = 0;
      else if(pos_str < 0)
        pos_str = 3;

      if(pos_carac[pos_str] > 36)
        pos_carac[pos_str] = 0;
      else if(pos_carac[pos_str] < 0)
        pos_carac[pos_str] = 36;

      nome[pos_str] = caracteres[pos_carac[pos_str]];

      ///DRAW
      draw_sprite(buffer, BG->front, 0, 0);
      draw_sprite(buffer, c->game_timebar, SCREEN_W/2 - c->game_timebar->w/2, -2);
      textprintf_ex(buffer, c->font_score, 10, 10, makecol(255,255,255), -1, "SCORE: %d", player_score);
      textprintf_right_ex(buffer, c->font_score, SCREEN_W-10, 10, makecol(255,255,255), -1, "LEVEL: %d", ((final_time/1000)/30)+1);
      textprintf_centre_ex(buffer, c->font_time, SCREEN_W/2, 5, makecol(255,255,255), -1, "TIME %02d: %02d: '%02d", ((final_time/1000)/60)%60, (final_time/1000)%60, (final_time/100)%100);
      draw_sprite(buffer, c->game_gameover_msg, (SCREEN_W/2 - c->game_gameover_msg->w/2), (SCREEN_H/2 - c->game_gameover_msg->h/2));

      if(colocacao != -1)
      {
         textprintf_centre_ex(buffer, c->font_help, SCREEN_W/2, 500, makecol(255,255,255), -1, "CONGRATULATIONS! YOU BEAT ONE OF THE BEST TIMES!");
         textprintf_centre_ex(buffer, c->font_help, SCREEN_W/2, 515, makecol(255,255,255), -1, "ENTER YOUR INITIALS BELOW:");

         for(int i = 0; i < 5; i++){
         textprintf_ex(buffer, c->font_highscores, 320 + i*50 , 540, makecol(200,200,200), -1, "%c", nome[i]);
         textprintf_ex(buffer, c->font_highscores, 320 + i*50 + 1 , 540+1, makecol(255,255,255), -1, "%c", nome[i]);
         }

         if((milisegundos/100)%2 == 0)
         draw_sprite(buffer, ret, (318 + 50 * pos_str), 570);
      }

      draw_sprite(screen, buffer, 0, 0);
      if(usevsync) vsync();
      clear(buffer);

     timer_fps = milisegundos;
    }
  }

   if(colocacao != -1){
    if(nome == "    ")
     nome = (string)"XXXX";

    pontuacoes.Registrar_Recorde(nome, final_time, player_score, colocacao, flag);
    pontuacoes.Save();
   }

   stop_midi();
   destroy_bitmap(ret);

   fade_out_black(20);
}
