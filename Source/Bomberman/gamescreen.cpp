#include "gamescreen.h"

void gamescreen()
{
    LoadGamescreenContent();
    desenhar = true;
    bool exit_screen = false;

	///VARIÁVEIS===================
	Tilemap tilemap;
	Portal portal;
	Player player;
    int tempo_partida;
    float timer_tempo;
    std::list<Enemy> enemy_list;
    std::list<Enemy>::iterator enemy_it;
	///============================

    ///INICIALIZAÇÃO=============================
    FILE* entrada = fopen("Arquivos/entrada.in", "r");

    if(!entrada)
    {
      al_show_native_message_box(display, "ERROR", "Input file not found", NULL, NULL, ALLEGRO_MESSAGEBOX_ERROR);
      exit_program = true;
    }

    else
    {
        int playerI, playerJ;
        int minutos, segundos;
        int portalI, portalJ;
        int numenemies;

        fscanf(entrada, "%d %d", &playerI, &playerJ);
        fscanf(entrada, "%d %d", &minutos, &segundos);
        fscanf(entrada, "%d %d", &portalI, &portalJ);

        fscanf(entrada, "%d", &numenemies);
        for(int i = 0; i < numenemies; i++)
        {
            int enemyI, enemyJ;
            fscanf(entrada, "%d %d", &enemyI, &enemyJ);
            Enemy novo;
            novo.Initialize(enemyI, enemyJ);
            enemy_list.push_back(novo);
        }

        tempo_partida = minutos*60 + segundos;
        portal.Initialize(portalI, portalJ);
        tilemap.Initialize(entrada, portalI, portalJ);
        player.Initialize(MAP_X0 + playerI*TILESIZE + TILESIZE/2, MAP_Y0 + playerJ*TILESIZE + TILESIZE/2);
        al_play_sample(BGM_gamescreen, volBGM-0.2, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
        al_start_timer(timer_FPS);
        timer_tempo = al_get_time();
    }

	///==========================================

    ///GAMELOOP=============================================
	while(!exit_program && !exit_screen)
	{
	    ///=================================
		///UPDATE
		///=================================

		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		 exit_program = true;

		//Colocar Bombas
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN
        || ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN)
        {
            if(ev.keyboard.keycode == ALLEGRO_KEY_A
            || ev.joystick.button == PSX_SQUARE )
            {
                player.PutBomb(tilemap);
            }

            else if(ev.keyboard.keycode == ALLEGRO_KEY_S
            || ev.joystick.button == PSX_R2 || ev.joystick.button == PSX_CROSS )
            {
                player.DetonateRemoteBomb(tilemap);
            }

            else if(ev.keyboard.keycode == ALLEGRO_KEY_F1)
              debug_mode = !debug_mode;
        }

        else if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            al_get_keyboard_state(&keystate);

            if(al_get_num_joysticks() > 0)
            al_get_joystick_state(joy1, &joy1_state);

            //UPDATE DO PROJETO==============================

            if(al_key_down(&keystate, ALLEGRO_KEY_ESCAPE)
            || joy1_state.button[PSX_SELECT] )
            {
              exit_screen = true;
              screenstate = MAINMENU;
            }

            //Atualiza jogador
            player.Update(tilemap);

            //Atualiza lista de inimigos
            for(enemy_it = enemy_list.begin(); enemy_it != enemy_list.end(); enemy_it++)
            {
                (*enemy_it).Update(tilemap, player.GetExplosionList());

                //Remove da lista os inimigos que morreram
                if( (*enemy_it).GetActive() == false )
                {
                    enemy_it = enemy_list.erase(enemy_it);
                }

                //Se o inimigo está ativo, checa se encostou no jogador
                else
                {
                    if( !player.GetImortal() && (*enemy_it).GetBox().CheckCollision(player.GetBox()) == true)
                      player.Die();
                }
            }

            bool fim = portal.Update(tilemap, player.GetX(), player.GetY(), enemy_list.size());

            if(fim)
            {
                exit_screen = true;
                screenstate = VICTORY;
            }

            if(player.GetLives() <= 0)
            {
                exit_screen = true;
                screenstate = GAMEOVER;
            }

            //Acabou o tempo do jogador
            if(al_get_time() - timer_tempo >= 1.0)
            {
                tempo_partida--;

                if(tempo_partida <= 0)
                {
                    exit_screen = true;
                    screenstate = GAMEOVER;
                }

                timer_tempo = al_get_time();
            }

            desenhar = true;

            //================================================
        }

        ///=================================
		///DRAW
		///=================================
		if(desenhar && al_is_event_queue_empty(event_queue))
        {
          //=====================
          //DESENHO DO PROJETO
          al_draw_bitmap(game_barra_superior, 0, 0, 0);
          al_draw_textf(font_bomberman, al_map_rgb(200, 200, 200), 125, 30, ALLEGRO_ALIGN_LEFT, "%d", player.GetLives());
          al_draw_textf(font_bomberman, al_map_rgb(255, 255, 255), 127, 32, ALLEGRO_ALIGN_LEFT, "%d", player.GetLives());
          al_draw_textf(font_bomberman, al_map_rgb(200, 200, 200), SCREEN_W/2, 30, ALLEGRO_ALIGN_CENTER, "%02d:%02d", tempo_partida/60, tempo_partida%60);
          al_draw_textf(font_bomberman, al_map_rgb(255, 255, 255), SCREEN_W/2+2, 32, ALLEGRO_ALIGN_CENTER, "%02d:%02d", tempo_partida/60, tempo_partida%60);
          tilemap.Draw();
          portal.Draw(tilemap, enemy_list.size());

          player.Draw();

          //Desenha lista de inimigos
          for(enemy_it = enemy_list.begin(); enemy_it != enemy_list.end(); enemy_it++)
            (*enemy_it).Draw();

          desenhar = false;
          //=====================

		  al_flip_display();
		  al_clear_to_color(al_map_rgb(0,0,0));
        }
	}
	///FIM DO GAMELOOP======================================================

	///FINALIZAÇÃO===============
	al_stop_timer(timer_FPS);
	UnloadGamescreenContent();
	///=========================
}
