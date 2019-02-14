#include "gamescreen.hpp"

///==============================
///GAMESCREEN
///==============================
void gamescreen(int flag)
{
  rectfill(screen, 0, 0, SCREEN_W, SCREEN_H, makecol(0,0,0));
  textout_right_ex(screen, c->font_shield, "LOADING...", SCREEN_W - 30, SCREEN_H - 45, makecol(255, 255, 255), -1);
  if(!Load_Gamescreen_Content(c))
  {
    exit_program = true;
    return;
  }

  qtd_tiros_E = 0;

  bool exit_screen = false;

  ///-------------------------------------
  ///OBJETOS
  ///-------------------------------------
  list<GameObject*> lista_tiros;
  list<GameObject*> lista_inimigos;
  list<GameObject*> lista_explosoes;
  list<GameObject*>::iterator iter;
  list<GameObject*>::iterator iter2;

  Background* BG = new Background();
  Spaceship* ship = new Spaceship(&lista_tiros, flag);
  Shield* barreira = new Shield(ship);
  Power_up* powup = new Power_up();

  //Tempo de Sobrevivência do Jogador
  int gameover_extra_time = 0;

  int final_time;
  int player_score = 0;
  int player_level;

  //Variáveis
  int timer_gera_inimigos = milisegundos;
  int to_next_enemy = 2500;
  int qtd_inimigos = 0;
  int timer_ready_msg = milisegundos;
  bool play_ready_voice = true;
  bool play_go_voice = true;

   //probabilidade inicial dos inimigos
   int porcentagem[5];
   porcentagem[0] = 50;
   porcentagem[1] = 80;
   porcentagem[2] = 100;
   porcentagem[3] = 0;
   porcentagem[4] = 0;

  //Instala o Media Player
  Mediaplayer* media_player = create_mediaplayer();

  player_time = 0;
  install_int_ex(survival_counter, MSEC_TO_TIMER(1));

  timer_fps = milisegundos - 16;

  ///-------------------------------------
  ///GAME LOOP
  ///-------------------------------------
  while(!exit_screen && !exit_program)
  {
    if(milisegundos - timer_fps >= 8)
    {
      ///-----------------------------------------------
      ///INPUT
      ///-----------------------------------------------
      keyboard_input();
      xbox_input();

      ///ENTER (PAUSE)
      if(just_pressed(KEY_ENTER) || xbox_just_pressed(BUTTON_START))
      {
         if(ship->charge > SHOT_LV0)
          stop_sample(c->FX_charging);
         if(barreira->collidable)
          stop_sample(c->FX_barreira);
         if(qtd_tiros_E > 0)
          stop_sample(c->FX_tiro_E);

         int guarda_tempo = player_time;
         if(pausemenu(BG, media_player) == 1)
         { exit_screen = true; break;}
         player_time = guarda_tempo;

         if(ship->charge > SHOT_LV0)
          play_sample(c->FX_charging, vol_SFX, 128, 1000, TRUE);
         if(barreira->collidable)
          play_sample(c->FX_barreira, vol_SFX, 128, 1000, TRUE);
         if(qtd_tiros_E > 0)
          play_sample(c->FX_tiro_E, vol_SFX, 128, 1000, TRUE);
      }

      ///F12
      else if(just_pressed(KEY_F12) || xbox_just_pressed(BUTTON_BACK))
        mediaplayer_change_song(media_player);

      ///ENTRADAS DA NAVE
      ship->Input();
      barreira->Input();

      //É hora de gerar um novo inimigo
      if((milisegundos - timer_gera_inimigos >= to_next_enemy) && qtd_inimigos < 12)
      {
         int novo_ID = gera_id(player_level, porcentagem);

         if(novo_ID == ENEMY_A)
         {
           Enemy_A* novo = new Enemy_A();
           lista_inimigos.push_back(novo);
         }
         else if(novo_ID == ENEMY_B)
         {
           Enemy_B* novo = new Enemy_B();
           lista_inimigos.push_back(novo);
         }
         else if(novo_ID == ENEMY_C)
         {
           Enemy_C* novo = new Enemy_C();
           lista_inimigos.push_back(novo);
         }
         else if(novo_ID == ENEMY_D)
         {
           Enemy_D* novo = new Enemy_D();
           lista_inimigos.push_back(novo);
         }
         else if(novo_ID == ENEMY_E)
         {
           Enemy_E* novo = new Enemy_E();
           lista_inimigos.push_back(novo);
         }

         //Gera bomba aleatória
         if(randnum(5) == 0)
         {
           Enemy_F* novo = new Enemy_F();
           lista_inimigos.push_back(novo);
         }

         qtd_inimigos++;
         timer_gera_inimigos = milisegundos;

         to_next_enemy = 2000 - (player_level-1)*50;
         if(to_next_enemy < 500)
           to_next_enemy = 500;
      }

      ///------------------------------------------------------
      ///UPDATE
      ///-------------------------------------------------------
      BG->Update();
      powup->Update(ship, barreira);
      ship->Update();
      barreira->Update();

      player_level = (player_time/1000)/30 + 1;

      //Atualiza Lista de inimigos
      for(iter = lista_inimigos.begin(); iter != lista_inimigos.end(); iter++)
      {
        (*iter)->Update();

        //Insere Tiros do inimigos na lista
        if((*iter)->ativo)
        {
           Shot* novo_tiro = NULL;
           Homing_Shot* nov_tiro = NULL;
           Bomba* nova_bomba = NULL;

           if((*iter)->ID == ENEMY_A && (milisegundos - dynamic_cast<Enemy*>(*iter)->timer_tiro) >= dynamic_cast<Enemy*>(*iter)->to_next_shot)
           { novo_tiro = new Shot((*iter)->pos_x, (*iter)->pos_y, SHOT_ENEMY_A);
             dynamic_cast<Enemy*>(*iter)->timer_tiro = milisegundos; dynamic_cast<Enemy*>(*iter)->to_next_shot = rand()%3500;
           }
           else if((*iter)->ID == ENEMY_B && (milisegundos - dynamic_cast<Enemy*>(*iter)->timer_tiro) >= dynamic_cast<Enemy*>(*iter)->to_next_shot)
           { novo_tiro = new Shot((*iter)->pos_x+20, (*iter)->pos_y+15, SHOT_ENEMY_B);
             dynamic_cast<Enemy*>(*iter)->timer_tiro = milisegundos; dynamic_cast<Enemy*>(*iter)->to_next_shot = rand()%3500;
           }
           else if((*iter)->ID == ENEMY_C && (milisegundos - dynamic_cast<Enemy*>(*iter)->timer_tiro) >= dynamic_cast<Enemy*>(*iter)->to_next_shot)
           { novo_tiro = new Shot((*iter)->pos_x+25, (*iter)->pos_y+40, SHOT_ENEMY_C);
             dynamic_cast<Enemy*>(*iter)->timer_tiro = milisegundos;
           }
           else if((*iter)->ID == ENEMY_D && (milisegundos - dynamic_cast<Enemy*>(*iter)->timer_tiro) >= dynamic_cast<Enemy*>(*iter)->to_next_shot)
           { novo_tiro = new Shot((*iter)->pos_x+25, (*iter)->pos_y+10, SHOT_ENEMY_D);
             dynamic_cast<Enemy*>(*iter)->timer_tiro = milisegundos; dynamic_cast<Enemy*>(*iter)->to_next_shot = rand()%3500;
           }
           else if((*iter)->ID == ENEMY_E && (milisegundos - dynamic_cast<Enemy*>(*iter)->timer_tiro) >= dynamic_cast<Enemy*>(*iter)->to_next_shot)
           { nov_tiro = new Homing_Shot(ship, (*iter)->pos_x+25, (*iter)->pos_y+40, SHOT_ENEMY_E);
              dynamic_cast<Enemy*>(*iter)->timer_tiro = milisegundos; dynamic_cast<Enemy*>(*iter)->to_next_shot = 3500; qtd_tiros_E++;
           }
           else if((*iter)->ID == ENEMY_F && (milisegundos - dynamic_cast<Enemy*>(*iter)->timer_tiro) >= dynamic_cast<Enemy*>(*iter)->to_next_shot)
           {  nova_bomba = new Bomba((*iter)->pos_x-40, (*iter)->pos_y-10, SHOT_ENEMY_F);
              (*iter)->ativo = false;
           }

           if(novo_tiro != NULL)
           lista_tiros.push_back(novo_tiro);

           if(nov_tiro != NULL)
           lista_tiros.push_back(nov_tiro);

           if(nova_bomba != NULL)
           lista_tiros.push_back(nova_bomba);
        }
      }

      //Atualiza Lista de explosões
      for(iter = lista_explosoes.begin(); iter != lista_explosoes.end(); iter++)
        (*iter)->Update();

      //Atualiza Lista de tiros
      for(iter = lista_tiros.begin(); iter != lista_tiros.end(); iter++)
        (*iter)->Update();

      //Checa colisões entre os inimigos e as balas da nave
      for(iter = lista_inimigos.begin(); iter != lista_inimigos.end(); iter++)
      {
         for(iter2 = lista_tiros.begin(); iter2 != lista_tiros.end(); iter2++)
         {
             if((*iter2)->collidable){
              int colisao = (*iter)->CheckCollision((*iter2));

             if(colisao)
             {
               Explosion* nova_explosao;
               if((*iter2)->ID == SHOT_LV0){
                nova_explosao = new Explosion( ((*iter)->pos_x + (*iter2)->pos_x)/2, ((*iter)->pos_y + (*iter2)->pos_y)/2, EXPL_SMALL);
               lista_explosoes.push_back(nova_explosao);
               }
               else if((*iter2)->ID == SHOT_LV1){
                nova_explosao = new Explosion( ((*iter)->pos_x + (*iter2)->pos_x)/2, ((*iter)->pos_y + (*iter2)->pos_y)/2, EXPL_MEDIUM);
               lista_explosoes.push_back(nova_explosao);
               }
               else if((*iter2)->ID == SHOT_LV2){
                nova_explosao = new Explosion( ((*iter)->pos_x + (*iter2)->pos_x)/2, ((*iter)->pos_y + (*iter2)->pos_y)/2, EXPL_LARGE);
               lista_explosoes.push_back(nova_explosao);
               }
             }
           }
         }
      }

      //Checa colisões entre a nave e as balas dos inimigos
      for(iter = lista_tiros.begin(); iter != lista_tiros.end(); iter++)
      {
          int colisaoNave = ship->CheckCollision((*iter));
          int colisaoBarreira = barreira->CheckCollision((*iter));

          if(colisaoNave)
          {
            Explosion* nova_explosao = new Explosion( (ship->pos_x + (*iter)->pos_x)/2, (ship->pos_y + (*iter)->pos_y)/2, EXPL_LARGE);
            lista_explosoes.push_back(nova_explosao);
          }
          else if(colisaoBarreira)
          {
            Explosion* nova_explosao = new Explosion( (barreira->pos_x + (*iter)->pos_x)/2, (barreira->pos_y + (*iter)->pos_y)/2, EXPL_SHIELD);
            lista_explosoes.push_back(nova_explosao);
          }
      }

      //Libera os inimigos não ativos
      for(iter = lista_inimigos.begin(); iter != lista_inimigos.end(); )
      {
         if((*iter)->ativo == false ) {
           qtd_inimigos--; player_score += (*iter)->ID * 25;
           (*iter)->Destroy();
           delete (*iter);
           iter = lista_inimigos.erase(iter);
         }
         else
          iter++;
      }

      //Libera os tiros não ativos
      for(iter = lista_tiros.begin(); iter != lista_tiros.end(); )
      {
         if((*iter)->ativo == false ) {
          if((*iter)->ID >= SHOT_LV0 && (*iter)->ID <= SHOT_LV2)
            ship->qtd_tiros--;

           (*iter)->Destroy();
           delete (*iter);
           iter = lista_tiros.erase(iter);
         }
         else
          iter++;
      }

      //Libera as explosões não ativas
      for(iter = lista_explosoes.begin(); iter != lista_explosoes.end(); )
      {
         if((*iter)->ativo == false ) {
           (*iter)->Destroy();
           delete (*iter);
           iter = lista_explosoes.erase(iter);
         }
         else
          iter++;
      }


      //GAMEOVER
      if(ship->vidas <= 0)
      {

        stop_sample(c->FX_barreira);
        stop_sample(c->FX_charging);
        stop_sample(c->FX_tiro_E);

        if(ship->morreu == false)
        {
          ship->morreu = true;
          final_time = player_time;
          gameover_extra_time = milisegundos;
        }

        if(milisegundos - gameover_extra_time >= 400)
        {
         exit_screen = true;

         remove_int(survival_counter);
         gameover(BG, player_score, final_time, flag);
         destroy_media_player(media_player);
         media_player = NULL;
        }
      }


     ///-------------------------------------
     ///DRAW
     ///-------------------------------------
     if(!exit_screen)
     {
        BG->Draw();       //background
        powup->Draw();    //powerup
        ship->Draw();     //nave
        barreira->Draw(); //barreira

        //Lista de inimigos
         for(iter = lista_inimigos.begin(); iter != lista_inimigos.end(); iter++)
          (*iter)->Draw();

        //Lista de inimigos
         for(iter = lista_tiros.begin(); iter != lista_tiros.end(); iter++)
          (*iter)->Draw();

        //Lista de inimigos
         for(iter = lista_explosoes.begin(); iter != lista_explosoes.end(); iter++)
          (*iter)->Draw();

        if(milisegundos - timer_ready_msg >= 0300 && milisegundos - timer_ready_msg <= 1300)
         {
            textprintf_centre_ex(buffer, c->font_ready, SCREEN_W/2, SCREEN_H/3, makecol(255, 255, 0), -1, "READY?");

            if(play_ready_voice)
             { play_sample(c->VOICE_ready, vol_SFX, 128, 1000, FALSE); play_ready_voice = false; }
         }
        else if(milisegundos - timer_ready_msg > 1300 && milisegundos - timer_ready_msg < 2300)
        {
            textprintf_centre_ex(buffer, c->font_ready, SCREEN_W/2, SCREEN_H/3, makecol(255, 255, 0), -1, "GO!");

            if(play_go_voice)
             { play_sample(c->VOICE_go, vol_SFX, 128, 1000, FALSE); play_go_voice = false; }
        }


        draw_sprite(buffer, c->game_timebar, SCREEN_W/2 - c->game_timebar->w/2, -2);
        textprintf_ex(buffer, c->font_score, 10, 10, makecol(255,255,255), -1, "SCORE: %d", player_score);
        textprintf_right_ex(buffer, c->font_score, SCREEN_W-10, 10, makecol(255,255,255), -1, "LEVEL: %d", player_level);
        textprintf_centre_ex(buffer, c->font_time, SCREEN_W/2, 5, makecol(255,255,255), -1, "TIME %02d: %02d: ''%02d", ((player_time/1000)/60)%60, (player_time/1000)%60, (player_time/100)%100);

        //Medidor Barreira
        if(barreira->points > 0)
         masked_blit(c->game_shield_bar_pts, buffer, 0, 0, 29, 559, (c->game_shield_bar_pts->w * ((float)barreira->points/(float)barreira->max_points)), c->game_shield_bar_pts->h);
        draw_sprite(buffer, c->game_shield_bar, 15, 550);
        textout_ex(buffer, c->font_shield, "SHIELD", 30, 543, makecol(240,240,0), -1);

        draw_sprite(screen, buffer, 0, 0);
        if(usevsync) vsync();
        clear(buffer);
      }

     timer_fps = milisegundos;
    }
  }

  ///FINALIZAÇÃO
  for(iter = lista_inimigos.begin(); iter != lista_inimigos.end();) {
    (*iter)->Destroy();
    delete (*iter);
    iter = lista_inimigos.erase(iter);
  }

   for(iter = lista_tiros.begin(); iter != lista_tiros.end();) {
    (*iter)->Destroy();
    delete (*iter);
    iter = lista_tiros.erase(iter);
  }

   for(iter = lista_explosoes.begin(); iter != lista_explosoes.end();) {
    (*iter)->Destroy();
    delete (*iter);
    iter = lista_explosoes.erase(iter);
  }

  ship->Destroy();
  delete ship;
  barreira->Destroy();
  delete barreira;
  powup->Destroy();
  delete powup;
  delete BG;

  if(media_player)
   destroy_media_player(media_player);
  Unload_Gamescreen_Content(c);
}


int gera_id(int player_level, int porcentagem[5])
{
   if(player_level == 2)
   {
     porcentagem[0] = 35;
     porcentagem[1] = 60;
     porcentagem[2] = 75;
     porcentagem[3] = 100;
   }

   else if(player_level >= 3)
   {
     porcentagem[0] = 30;
     porcentagem[1] = 50;
     porcentagem[2] = 60;
     porcentagem[3] = 80;
     porcentagem[4] = 100;
   }

   int random = rand() % 100;

   if(random >= 0 && random < porcentagem[0])
    return ENEMY_A;
   else if(random >= porcentagem[0] && random < porcentagem[1])
    return ENEMY_B;
   else if(random >= porcentagem[1] && random < porcentagem[2])
    return ENEMY_C;
   else if(random >= porcentagem[2] && random < porcentagem[3])
    return ENEMY_D;
   else
    return ENEMY_E;
}
