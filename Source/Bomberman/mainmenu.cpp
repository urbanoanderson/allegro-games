#include "mainmenu.h"

void mainmenu()
{
    ///INICIALIZAÇÃO=========
    LoadMainmenuContent();
    desenhar = true;
    ///======================

	///VARIÁVEIS=============
	bool exit_screen = false;
	bool option = 0;
	Animation anim_bomba;
	anim_bomba.Initialize(game_bomb, 4, ALLEGRO_MSECS_TO_SECS(150), true);
	Animation anim_dirigivel;
	anim_dirigivel.Initialize(main_dirigivel2, 16, ALLEGRO_MSECS_TO_SECS(80), true);

	ALLEGRO_COLOR colorFundo = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR colorFrente = al_map_rgb(255, 255, 255);

	int altura1 = 560;
	int altura2 = 630;

	float balao_x = 100, balao_speed = 0.8;
	float balao_y = 100;
	int dir_y = 1;
	float dirigivel1_x = 225, dirigivel1_speed = 0.6;
	float dirigivel2_x = 675, dirigivel2_speed = 0.7;
	///======================

	al_play_sample(BGM_mainmenu, volBGM/3, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
	al_start_timer(timer_FPS);

    ///=============================
    ///GAMELOOP
    ///=============================
	while(!exit_program && ! exit_screen)
	{
	    ///=================================
		///UPDATE
		///=================================

		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		 exit_program = true;

		if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            anim_bomba.Update();
            anim_dirigivel.Update();

            balao_y += dir_y*0.2;
            if(balao_y <= 95 || balao_y >= 105)
             dir_y *= -1;

            balao_x += balao_speed;
            dirigivel1_x += dirigivel1_speed;
            dirigivel2_x -= dirigivel2_speed;

            if(balao_x > SCREEN_W + 300)
             balao_x = -width(main_balao);
            if(dirigivel1_x > SCREEN_W + 200)
             dirigivel1_x = -width(main_dirigivel1);
            if(dirigivel2_x + anim_dirigivel.Width() < -100)
             dirigivel2_x = SCREEN_W;

            desenhar = true;
        }

		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN
        || ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN
        || ev.type == ALLEGRO_EVENT_JOYSTICK_AXIS )
		{
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			   exit_program = true;

            else if( ev.keyboard.keycode == ALLEGRO_KEY_UP
            || ev.keyboard.keycode == ALLEGRO_KEY_DOWN
            || (ev.joystick.axis == 1 && ev.joystick.pos != 0))
            {
               option = !option;
               al_play_sample(SFX_menusound1, volSFX, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            }

            else if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER
            || ev.joystick.button == PSX_START
            || ev.joystick.button == PSX_SQUARE
            || ev.joystick.button == PSX_CROSS )
            {
               al_play_sample(SFX_menusound2, volSFX, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
               if(option == 1)
                exit_program = true;
               else
               {
                exit_screen = true;
                screenstate = GAMESCREEN;
               }
			}
		}

        ///=================================
		///DRAW
		///=================================
		if(desenhar && al_is_event_queue_empty(event_queue))
        {
          //=====================
          //DESENHO DO PROJETO

		  al_draw_bitmap(main_bg, 0, 0, 0);
		  al_draw_bitmap(main_balao, balao_x, balao_y, 0);
		  al_draw_bitmap(main_dirigivel1, dirigivel1_x, 475, 0);
		  anim_dirigivel.Draw(dirigivel2_x, 275);
          al_draw_scaled_bitmap(main_title, 0, 0, width(main_title), height(main_title), 125, 25, 650, 450, 0);

          al_draw_text(font_menu, colorFundo, SCREEN_W/2, altura1, ALLEGRO_ALIGN_CENTER, "PLAY");
          al_draw_text(font_menu, colorFrente, SCREEN_W/2+2, altura1+2, ALLEGRO_ALIGN_CENTER, "PLAY");
          al_draw_text(font_menu, colorFundo, SCREEN_W/2, altura2, ALLEGRO_ALIGN_CENTER, "EXIT");
          al_draw_text(font_menu, colorFrente, SCREEN_W/2+2, altura2+2, ALLEGRO_ALIGN_CENTER, "EXIT");

		  if(option == 0)
		    anim_bomba.Draw(360, altura1+10, 1.0, 1.0, 0.0, al_map_rgb(255,255,255));
		  else
            anim_bomba.Draw(360, altura2+10, 1.0, 1.0, 0.0, al_map_rgb(255,255,255));

		  desenhar = false;

		  //=====================

		  al_flip_display();
		  al_clear_to_color(al_map_rgb(0,0,0));
        }
	}

	///FINALIZAÇÃO
	al_stop_timer(timer_FPS);
	UnloadMainmenuContent();
}
