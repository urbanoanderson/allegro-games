#include "gameover.h"

void gameover()
{
    ///INICIALIZAÇÃO=========
    LoadGameoverContent();
    desenhar = true;
    ///======================

	///VARIÁVEIS=============
	bool exit_screen = false;
	float timer_gameover = al_get_time();
	bool pode_apertar = false;
	Animation anim_boneco;

	anim_boneco.Initialize(gameover_animation, 4, ALLEGRO_MSECS_TO_SECS(150), true);
	///======================

	al_play_sample(BGM_gameover, volBGM, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
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

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN
        || ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN )
		{
		    if(pode_apertar)
            {
		      exit_screen = true;
              screenstate = MAINMENU;
            }
		}

		if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            if(al_get_time() - timer_gameover >= 5.0)
            {
                pode_apertar = true;
            }

            anim_boneco.Update();

            desenhar = true;
        }


        ///=================================
		///DRAW
		///=================================
		if(desenhar && al_is_event_queue_empty(event_queue))
        {
          //=====================
          //DESENHO DO PROJETO

		  al_draw_bitmap(gameover_bg, 0, 0, 0);
		  al_draw_bitmap(gameover_title, SCREEN_W/2 - width(gameover_title)/2, 150, 0);
		  anim_boneco.Draw(SCREEN_W/2, SCREEN_H/2+50, 1.2, 1.2, 0.0, al_map_rgb(255,255,255));

		  desenhar = false;

		  //=====================

		  al_flip_display();
		  al_clear_to_color(al_map_rgb(0,0,0));
        }
	}

	///FINALIZAÇÃO
	al_stop_timer(timer_FPS);
	UnloadGameoverContent();
}
