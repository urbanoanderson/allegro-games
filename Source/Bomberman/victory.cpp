#include "victory.h"

void victory()
{
    ///INICIALIZAÇÃO=========
    LoadVictoryContent();
    desenhar = true;
    ///======================

	///VARIÁVEIS=============
	bool exit_screen = false;
	float timer_victory = al_get_time();
    bool pode_apertar = false;

	Animation anim_yellow;
	Animation anim_green;
	Animation anim_blue;
	Animation anim_orange;

	anim_yellow.Initialize(victory_yellow, 2, ALLEGRO_MSECS_TO_SECS(500), true);
	anim_green.Initialize(victory_green, 2, ALLEGRO_MSECS_TO_SECS(500), true);
	anim_blue.Initialize(victory_blue, 2, ALLEGRO_MSECS_TO_SECS(500), true);
	anim_orange.Initialize(victory_orange, 2, ALLEGRO_MSECS_TO_SECS(500), true);
	///======================

	al_play_sample(BGM_victory, volBGM, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
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
        || ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN)
		{
		    if(pode_apertar)
            {
		     exit_screen = true;
             screenstate = MAINMENU;
		    }
		}

		if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            anim_yellow.Update();
            anim_green.Update();
            anim_blue.Update();
            anim_orange.Update();

            if(al_get_time() - timer_victory >= 2.0)
            {
                pode_apertar = true;
            }

            desenhar = true;
        }


        ///=================================
		///DRAW
		///=================================
		if(desenhar && al_is_event_queue_empty(event_queue))
        {
          //=====================
          //DESENHO DO PROJETO

          anim_yellow.Draw(0, 0);
          anim_green.Draw(anim_green.Width() + 10, 0);
          anim_blue.Draw(2*anim_blue.Width() +13, 0);
          anim_orange.Draw(3*anim_orange.Width() +16 , 0);
          anim_yellow.Draw(4*anim_yellow.Width() +19, 0);
          anim_green.Draw(5*anim_green.Width() +22, 0);
          anim_blue.Draw(6*anim_blue.Width() +25, 0);
          anim_orange.Draw(7*anim_orange.Width()+28, 0);
		  al_draw_bitmap(victory_floor, 0, SCREEN_H-height(victory_floor), 0);
		  al_draw_bitmap(victory_bomberman, SCREEN_W/2 - width(victory_bomberman)/2, 75, 0);

		  desenhar = false;

		  //=====================

		  al_flip_display();
		  al_clear_to_color(al_map_rgb(0,0,0));
        }
	}

	///FINALIZAÇÃO
	al_stop_timer(timer_FPS);
	UnloadVictoryContent();
}
