#include "optionscreen.hpp"

///************************************
///OPTIONSCREEN
///************************************
void optionscreen(float* angle)
{
    bool exit_screen = false;
	char opcoes[6][20] = { "VOLUME SFX", "VOLUME BGM", "VIDEO MODE", "VSYNC", "SAVE AND EXIT", "EXIT WITHOUT SAVING" };
	char vmodestr[3][15] = { "FULLSCREEN", "WINDOWED" };
	char vsyncstr[2][5] = { "OFF", "ON" };
	int escolha = SFX;
	set_trans_blender(255,255,255,100);

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
		  {
		    escolha++;
		    if(escolha > DONT_SAVE)
		     escolha = SFX;
		    play_sample(c->FX_click1, vol_SFX, 128, 1000, FALSE);
		  }
		  else if(just_pressed(KEY_UP) || xbox_just_pressed(DPAD_UP) || xbox_just_pressed(LSTICK_UP))
		  {
		    escolha--;
		    if(escolha < SFX)
		     escolha = DONT_SAVE;
		    play_sample(c->FX_click1, vol_SFX, 128, 1000, FALSE);
		  }

          ///LEFT ARROW
		  else if(just_pressed(KEY_LEFT) || xbox_just_pressed(DPAD_LEFT) || xbox_just_pressed(LSTICK_LEFT))
		  {
		    play_sample(c->FX_click1, vol_SFX, 128, 1000, FALSE);

		    if(escolha == SFX)
            {
               vol_SFX -= 51;
               if(vol_SFX < 0)
                 vol_SFX = 0;
                 set_volume(vol_SFX, vol_BGM);
            }

            else if(escolha == BGM)
            {
               vol_BGM -= 51;
               if(vol_BGM < 0)
                 vol_BGM = 0;
                 set_volume(vol_SFX, vol_BGM);
            }

            else if(escolha == VSYNC)
            {
              usevsync = (!usevsync);
            }

            else if(escolha == VIDEO_MODE)
            {
              video_mode = (!video_mode);
              set_gfx_mode(video_mode + 1, SCREEN_W, SCREEN_H, 0, 0);
            }
		  }

		  ///RIGHT ARROW
		  else if(just_pressed(KEY_RIGHT) || xbox_just_pressed(DPAD_RIGHT) || xbox_just_pressed(LSTICK_RIGHT))
		  {
		    play_sample(c->FX_click1, vol_SFX, 128, 1000, FALSE);

		    if(escolha == SFX)
            {
               vol_SFX += 51;
               if(vol_SFX > 255)
                 vol_SFX = 255;
                 set_volume(vol_SFX, vol_BGM);
            }

            else if(escolha == BGM)
            {
               vol_BGM += 51;
               if(vol_BGM > 255)
                 vol_BGM = 255;
                 set_volume(vol_SFX, vol_BGM);
            }

            else if(escolha == VSYNC)
            {
              usevsync = (!usevsync);
            }

            else if(escolha == VIDEO_MODE)
            {
              video_mode = (!video_mode);
              if(video_mode == WINDOWED)
                set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0);
              else
                set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, SCREEN_W, SCREEN_H, 0, 0);
            }
		  }

		  else if((just_pressed(KEY_ENTER) || xbox_just_pressed(BUTTON_A) || xbox_just_pressed(BUTTON_START))
             && (escolha == SAVE_EXIT || escolha == DONT_SAVE))
          {
             exit_screen = true;
             play_sample(c->FX_click3, vol_SFX, 128, 1000, FALSE);

             if(escolha == SAVE_EXIT)
              Save_user_configuration();
          }

          else if(just_pressed(KEY_ESC) || xbox_just_pressed(BUTTON_B))
            exit_screen = true;

          ///UPDATE
          *angle += 0.35;

          ///DRAW
          pivot_sprite(buffer, c->main_BG, SCREEN_W/2, SCREEN_H/2, c->main_BG->w/2, c->main_BG->h/2, ftofix(*angle));
          textprintf_centre_ex(buffer, c->font_title_options, SCREEN_W/2, 75, makecol(200,200,200), -1, "OPTIONS");
          textprintf_centre_ex(buffer, c->font_title_options, SCREEN_W/2+2, 75+2, makecol(255,250,120), -1, "OPTIONS");

          for(int i = 0; i < 6; i++)
		  {
		    //Se não está selecionado
		    if(escolha != i)
            {
              if(i == SFX)
              {
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 251 + i*50, makecol(180,180,180), -1, "%s: %d", opcoes[i], vol_SFX/51);
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 250 + i*50, makecol(255,255,255), -1, "%s: %d", opcoes[i], vol_SFX/51);
              }
              else if(i == BGM)
              {
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 251 + i*50, makecol(180,180,180), -1, "%s: %d", opcoes[i], vol_BGM/51);
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 250 + i*50, makecol(255,255,255), -1, "%s: %d", opcoes[i], vol_BGM/51);
              }
              else if(i == VIDEO_MODE)
              {
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 251 + i*50, makecol(180,180,180), -1, "%s: %s", opcoes[i], vmodestr[video_mode]);
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 250 + i*50, makecol(255,255,255), -1, "%s: %s", opcoes[i], vmodestr[video_mode]);
              }
              else if(i == VSYNC)
              {
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 251 + i*50, makecol(180,180,180), -1, "%s: %s", opcoes[i], vsyncstr[usevsync]);
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 250 + i*50, makecol(255,255,255), -1, "%s: %s", opcoes[i], vsyncstr[usevsync]);
              }
              else
              {
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 251 + i*50, makecol(180,180,180), -1, "%s", opcoes[i]);
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 250 + i*50, makecol(255,255,255), -1, "%s", opcoes[i]);
              }
            }

            //Se está selecionado
            else
            {
              if(i == SFX)
              {
                textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 250 + i*50, makecol(255,255,0), -1, "%s: %d", opcoes[i], vol_SFX/51);
			    textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 251 + i*50, makecol(255,250,120), -1, "%s: %d", opcoes[i], vol_SFX/51);
              }
              else if(i == BGM)
              {
                textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 250 + i*50, makecol(255,255,0), -1, "%s: %d", opcoes[i], vol_BGM/51);
			    textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 251 + i*50, makecol(255,250,120), -1, "%s: %d", opcoes[i], vol_BGM/51);
              }
              else if(i == VIDEO_MODE)
              {
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 251 + i*50, makecol(255,255,0), -1, "%s: %s", opcoes[i], vmodestr[video_mode]);
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 250 + i*50, makecol(255,250,120), -1, "%s: %s", opcoes[i], vmodestr[video_mode]);
              }
              else if(i == VSYNC)
              {
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 251 + i*50, makecol(255,255,0), -1, "%s: %s", opcoes[i], vsyncstr[usevsync]);
               textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 250 + i*50, makecol(255,250,120), -1, "%s: %s", opcoes[i], vsyncstr[usevsync]);
              }
              else
              {
                textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2, 250 + i*50, makecol(255,255,0), -1, "%s", opcoes[i]);
			    textprintf_centre_ex(buffer, c->font_options, SCREEN_W/2+1, 251 + i*50, makecol(255,250,120), -1, "%s", opcoes[i]);
              }
			 draw_trans_sprite(buffer, c->main_selection, 0, 250 + 50 * i - 4);
            }
		  }

          draw_sprite(screen, buffer, 0,0);
          if(usevsync) vsync();
           clear(buffer);

      timer_fps = milisegundos;
      }
    }
}
