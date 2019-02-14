#include "highscore_screen.hpp"

///************************************
///TELA DE HIGHSCORES
///************************************
void highscore_screen(float* angle)
{
    bool exit_screen = false;
    int page = ARCADE_MODE;

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

          else if(just_pressed(KEY_LEFT) || xbox_just_pressed(DPAD_LEFT) || xbox_just_pressed(LSTICK_LEFT))
           { page--; play_sample(c->FX_click4, vol_SFX, 128, 1000, FALSE); }

          else if(just_pressed(KEY_RIGHT) || xbox_just_pressed(DPAD_RIGHT) || xbox_just_pressed(LSTICK_RIGHT))
           { page++; play_sample(c->FX_click4, vol_SFX, 128, 1000, FALSE); }

          ///UPDATE
          *angle += 0.35;

          if(page > CHALLENGE3)
            page = ARCADE_MODE;
          else if(page < ARCADE_MODE)
            page = CHALLENGE3;

          ///DRAW
          pivot_sprite(buffer, c->main_BG, SCREEN_W/2, SCREEN_H/2, c->main_BG->w/2, c->main_BG->h/2, ftofix(*angle));
          textprintf_centre_ex(buffer, c->font_title_options, SCREEN_W/2, 40, makecol(200,200,200), -1, "HIGHSCORES");
          textprintf_centre_ex(buffer, c->font_title_options, SCREEN_W/2+2, 40+2, makecol(255,250,120), -1, "HIGHSCORES");
          draw_sprite(buffer, c->main_arrow, 15, SCREEN_H/2);
          draw_sprite_h_flip(buffer, c->main_arrow, SCREEN_W -c->main_arrow->w - 15, SCREEN_H/2);

          if(page == ARCADE_MODE)
          {
             textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 210, makecol(200,200,50), -1, "ARCADE");
             textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 210+1, makecol(255,255,0), -1, "ARCADE");
             textprintf_ex(buffer, c->font_options, SCREEN_W/5, 260, makecol(255,255,0), -1, "NAME     TIME     SCORE");
             for(int i = 4; i >= 0; i--)
             {
              textprintf_ex(buffer, c->font_options, SCREEN_W/5-50, 500 - 50*i, makecol(255,255,255), -1, "%d.", (5-i));
              if(pontuacoes.scores_arcade[i] != -1)
              textprintf_ex(buffer, c->font_options, SCREEN_W/5,   500 - 50*i, makecol(255,255,255), -1, "%s", pontuacoes.nomes_arcade[i].c_str());
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 110, 500 - 50*i, makecol(255,255,255), -1, "-----");
              if(pontuacoes.scores_arcade[i] != -1)
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 200, 500 - 50*i, makecol(255,255,255), -1, "%02d:%02d:''%02d", ((pontuacoes.times_arcade[i]/1000)/60)%60, ((pontuacoes.times_arcade[i]/1000)%60), (pontuacoes.times_arcade[i]/100)%100);
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 360, 500 - 50*i, makecol(255,255,255), -1, "-----");
              if(pontuacoes.scores_arcade[i] != -1)
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 450, 500 - 50*i, makecol(255,255,255), -1, "%d", pontuacoes.scores_arcade[i]);
            }
          }

          else if(page == CHALLENGE1)
          {
             textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 210, makecol(200,200,50), -1, "NO SHOOTING");
             textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 210+1, makecol(255,255,0), -1, "NO SHOOTING");
             textprintf_ex(buffer, c->font_options, SCREEN_W/5, 260, makecol(255,255,0), -1, "NAME     TIME     SCORE");
             for(int i = 4; i >= 0; i--)
             {
              textprintf_ex(buffer, c->font_options, SCREEN_W/5-50, 500 - 50*i, makecol(255,255,255), -1, "%d.", (5-i));
              if(pontuacoes.scores_challenge1[i] != -1)
              textprintf_ex(buffer, c->font_options, SCREEN_W/5,   500 - 50*i, makecol(255,255,255), -1, "%s", pontuacoes.nomes_challenge1[i].c_str());
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 110, 500 - 50*i, makecol(255,255,255), -1, "-----");
              if(pontuacoes.scores_challenge1[i] != -1)
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 200, 500 - 50*i, makecol(255,255,255), -1, "%02d:%02d:''%02d", ((pontuacoes.times_challenge1[i]/1000)/60)%60, ((pontuacoes.times_challenge1[i]/1000)%60), (pontuacoes.times_challenge1[i]/100)%100);
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 360, 500 - 50*i, makecol(255,255,255), -1, "-----");
              if(pontuacoes.scores_challenge1[i] != -1)
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 450, 500 - 50*i, makecol(255,255,255), -1, "%d", pontuacoes.scores_challenge1[i]);
            }
          }

          else if(page == CHALLENGE2)
          {
             textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 210, makecol(200,200,50), -1, "NO SHIELD");
             textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 210+1, makecol(255,255,0), -1, "NO SHIELD");
             textprintf_ex(buffer, c->font_options, SCREEN_W/5, 260, makecol(255,255,0), -1, "NAME     TIME     SCORE");
             for(int i = 4; i >= 0; i--)
             {
              textprintf_ex(buffer, c->font_options, SCREEN_W/5-50, 500 - 50*i, makecol(255,255,255), -1, "%d.", (5-i));
              if(pontuacoes.scores_challenge2[i] != -1)
              textprintf_ex(buffer, c->font_options, SCREEN_W/5,   500 - 50*i, makecol(255,255,255), -1, "%s", pontuacoes.nomes_challenge2[i].c_str());
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 110, 500 - 50*i, makecol(255,255,255), -1, "-----");
              if(pontuacoes.scores_challenge2[i] != -1)
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 200, 500 - 50*i, makecol(255,255,255), -1, "%02d:%02d:''%02d", ((pontuacoes.times_challenge2[i]/1000)/60)%60, ((pontuacoes.times_challenge2[i]/1000)%60), (pontuacoes.times_challenge2[i]/100)%100);
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 360, 500 - 50*i, makecol(255,255,255), -1, "-----");
              if(pontuacoes.scores_challenge2[i] != -1)
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 450, 500 - 50*i, makecol(255,255,255), -1, "%d", pontuacoes.scores_challenge2[i]);
            }
          }

          else if(page == CHALLENGE3)
          {
             textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 210, makecol(200,200,50), -1, "CHUCK NORRIS");
             textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 210+1, makecol(255,255,0), -1, "CHUCK NORRIS");
             textprintf_ex(buffer, c->font_options, SCREEN_W/5, 260, makecol(255,255,0), -1, "NAME     TIME     SCORE");
             for(int i = 4; i >= 0; i--)
             {
              textprintf_ex(buffer, c->font_options, SCREEN_W/5-50, 500 - 50*i, makecol(255,255,255), -1, "%d.", (5-i));
              if(pontuacoes.scores_challenge3[i] != -1)
              textprintf_ex(buffer, c->font_options, SCREEN_W/5,   500 - 50*i, makecol(255,255,255), -1, "%s", pontuacoes.nomes_challenge3[i].c_str());
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 110, 500 - 50*i, makecol(255,255,255), -1, "-----");
              if(pontuacoes.scores_challenge3[i] != -1)
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 200, 500 - 50*i, makecol(255,255,255), -1, "%02d:%02d:''%02d", ((pontuacoes.times_challenge3[i]/1000)/60)%60, ((pontuacoes.times_challenge3[i]/1000)%60), (pontuacoes.times_challenge3[i]/100)%100);
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 360, 500 - 50*i, makecol(255,255,255), -1, "-----");
              if(pontuacoes.scores_challenge3[i] != -1)
              textprintf_ex(buffer, c->font_options, SCREEN_W/5 + 450, 500 - 50*i, makecol(255,255,255), -1, "%d", pontuacoes.scores_challenge3[i]);
            }
          }

          draw_sprite(screen, buffer, 0,0);
          if(usevsync) vsync();
          clear(buffer);

      timer_fps = milisegundos;
      }
    }
}
