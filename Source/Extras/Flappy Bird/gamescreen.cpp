#include "gamescreen.h"

void gamescreen()
{
    LoadGamescreenContent();

    ///VARIÁVEIS=============
	bool exit_screen = false;
	float bg_x = 0, bgceu_x = 0;
	Player player;
	PipeList pipes;

	///INICIALIZAÇÃO=========
    pipes.Initialize();
    player.Initialize();
    desenhar = true;
    ///======================

	//Tocando a música de fundo
	ALLEGRO_SAMPLE_INSTANCE* BGM_gamescreen_instance = al_create_sample_instance(BGM_gamescreen);
	al_set_sample_instance_playmode(BGM_gamescreen_instance, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_gain(BGM_gamescreen_instance, regVolume(volBGM));
	al_attach_sample_instance_to_mixer(BGM_gamescreen_instance, al_get_default_mixer());
	al_play_sample_instance(BGM_gamescreen_instance);

	al_start_timer(timer_FPS);

	while(!exit_program && ! exit_screen)
	{
	    ///=================================
		///UPDATE
		///=================================

		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		 exit_program = true;

        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN
        || ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN )
		{
		    //ESC sai do jogo
		    if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			   exit_program = true;

            //Ativar debug
            else if(ev.keyboard.keycode == ALLEGRO_KEY_F1)
              DEBUG = !DEBUG;

            //Botão mudo
            else if(ev.keyboard.keycode == ALLEGRO_KEY_F2)
            {
                if(volBGM > 0.0)
                 { volBGM = 0.0;  volSFX = 0.0; }
                else
                 { volBGM = 1.0;  volSFX = 1.0; }

                 al_set_sample_instance_gain(BGM_gamescreen_instance, regVolume(volBGM));
            }

            //PULAR
            else if(ev.keyboard.keycode == ALLEGRO_KEY_A)
              player.Jump();

            //Reiniciar jogo
            else if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                if(!player.GetAlive())
                {
                    player.Initialize();
                    pipes.ResetPipes();
                }
            }
		}

        else if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            al_get_keyboard_state(&keystate);

            if(al_get_num_joysticks() > 0)
            al_get_joystick_state(joy1, &joy1_state);

            ///UPDATE DO PROJETO==============================

            //Background
            bg_x -= BACKGROUND_SPEED;
            if(bg_x < -width(game_background))
             bg_x = 0.0;
            bgceu_x -= (BACKGROUND_SPEED-0.8);
            if(bgceu_x < -width(game_background))
             bgceu_x = 0.0;

            //Player
            player.Update();

            //Cnos
            pipes.Update(&player);

            desenhar = true;
        }

		///=================================
		///DRAW
		///=================================
		if(desenhar && al_is_event_queue_empty(event_queue))
        {
            ///=====================
            ///DESENHO DO PROJETO

            //Background
            al_draw_bitmap(game_background, bgceu_x, 0, 0);
            al_draw_bitmap(game_background, bgceu_x+width(game_background), 0, 0);
            al_draw_bitmap(game_ground, bg_x, SCREEN_H-height(game_ground), 0);
            al_draw_bitmap(game_ground, bg_x+width(game_ground), SCREEN_H-height(game_ground), 0);

            //Canos
            pipes.Draw();

            //Player
            player.Draw();

            //Score
            al_draw_textf(font_mensagem, al_map_rgb(0,0,0), 10, 10, ALLEGRO_ALIGN_LEFT, "SCORE: %d", player.GetScore());

            //Mensagem ao morrer
            if(!player.GetAlive()){
                al_draw_textf(font_mensagem, al_map_rgb(0,0,0), SCREEN_W/2, SCREEN_H/2-50, ALLEGRO_ALIGN_CENTER, "- GAME OVER -");
                al_draw_textf(font_mensagem, al_map_rgb(0,0,0), SCREEN_W/2, SCREEN_H/2-20, ALLEGRO_ALIGN_CENTER, "Press ENTER to try again");
            }

            desenhar = false;
            ///=====================

            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
	}

    ///FINALIZAÇÃO
	al_stop_timer(timer_FPS);
	al_destroy_sample_instance(BGM_gamescreen_instance);
	UnloadGamescreenContent();
}
