#include "Gamescreen.h"

void gamescreen()
{
   //Fade entre telas
   fade_out(40);
   set_trans_blender(255,255,255,128);

   BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
   int exit_screen = FALSE;
   int gameState = FIM_DO_TURNO;
   int timer_espera = gametime;
   int bip = 0;
   int prev_esc_state;

   //Botões
   TowerButton* b_normal = Create_TowerButton(torre_normal, 704, 667, TORRE_NORMAL);
   TowerButton* b_slow = Create_TowerButton(torre_slow, 784, 667, TORRE_SLOW);
   TowerButton* b_antitanque = Create_TowerButton(torre_antitanque, 864, 667, TORRE_ANTITANQUE);
   TowerButton* b_veneno = Create_TowerButton(torre_veneno, 944, 667, TORRE_VENENO);
   Button_Venda* b_vender = Create_Button_Venda(60, 667);
   Button_Upgrade* b_upgrade = Create_Button_Upgrade(60 + vender->w + 20, 667);
   int usando_botao = FALSE;

   Stage* stage = Create_Stage();
   Enemy_List* e_list = Create_Enemy_List();
   Initialize_Matrix();
   Program_Insertions_In_Enemy_List(e_list, stage->turnos_sol[0], stage->turnos_solf[0], stage->turnos_moto[0], stage->turnos_tank[0], 400);

   set_volume(255, 180);
   play_midi(SONG_gamescreen, TRUE);

   fps_timer = gametime - 9;

   while(!exit_program && !exit_screen)
   {
          //INPUT
          prev_esc_state = key[KEY_ESC];
          poll_keyboard();

          if(prev_esc_state == 0 && key[KEY_ESC] != 0)
          {
              screen_state = MAINMENU;
              exit_screen = TRUE;
          }

          //UPDATE
          Update_TowerButton(b_normal, stage, &usando_botao);
          Update_TowerButton(b_slow, stage, &usando_botao);
          Update_TowerButton(b_antitanque, stage, &usando_botao);
          Update_TowerButton(b_veneno, stage, &usando_botao);
          Update_Button_Venda(b_vender, stage);
          Update_Button_Upgrade(b_upgrade, stage);

          Update_Tower_Matrix(e_list, stage);

          //Seleciona torre
            if(mouse_b == 1
            && mouse_x >= X0 && mouse_x <= X0 + TILESIZE*NUMTILESJ
            && mouse_y >= Y0 && mouse_y <= Y0 + TILESIZE*NUMTILESI )
            {
                selecao = mtx[(mouse_y - Y0)/TILESIZE][(mouse_x - X0)/TILESIZE];

                if(selecao && bip == 0)
                 play_sample(FX_select, 255, 128, 1000, FALSE);

                bip++;
            }
            else if(mouse_b == 0)
              bip = 0;

          if(gameState == JOGANDO)
          {
            Try_to_Insert_In_Enemy_List(e_list, stage);
            Update_Enemy_List(e_list, stage);

            //Se acabaram os inimigos
            if(Remain_Units_To_Insert(e_list) <= 0 && e_list->numenemies <= 0)
            {
               stage->turno_atual++;

                //Se era o último turno
                if(stage->turno_atual > stage->turnos)
                {
                  stage->turno_atual--;
                  exit_screen = TRUE;
                  screen_state = VITORIA;
                }


                else
                {
                 Program_Insertions_In_Enemy_List(e_list, stage->turnos_sol[stage->turno_atual-1], stage->turnos_solf[stage->turno_atual-1], stage->turnos_moto[stage->turno_atual-1], stage->turnos_tank[stage->turno_atual-1], 400);
                 gameState = FIM_DO_TURNO;
                 timer_espera = gametime;
                }
            }

            //Gameover se acabarem as vidas
            if(stage->vidas <= 0)
            {
               exit_screen = TRUE;
               screen_state = GAMEOVER;
            }
          }

          else if(gameState == FIM_DO_TURNO)
          {
              //Espera 3 segundos antes do próximo turno
              if(gametime - timer_espera >= 3200)
                gameState = JOGANDO;
          }

          //DRAW
          draw_sprite(buffer, background, X0, Y0);
          Draw_Tilemap(stage->map, buffer);
          Draw_Enemy_List(e_list, buffer);
          Draw_Bases(stage->map, buffer);

          //Mostra raio de ação graficamente
          if(selecao != NULL && !b_normal->ativado && !b_slow->ativado && !b_antitanque->ativado && !b_veneno->ativado){
             circle(buffer, (int)selecao->x, (int)selecao->y, (int)selecao->raio, makecol(145, 215, 230));  //Mostra raio visualmente
             circle(buffer, (int)selecao->x, (int)selecao->y, (int)selecao->raio+1, makecol(120, 200, 220));
          }

          Draw_Tower_Matrix(buffer);
          draw_sprite(buffer, frame, 0, 0);

          //Botões
          Draw_TowerButton(b_normal, buffer);
          Draw_TowerButton(b_slow, buffer);
          Draw_TowerButton(b_antitanque, buffer);
          Draw_TowerButton(b_veneno, buffer);
          Draw_Button_Venda(b_vender, buffer);
          Draw_Button_Upgrade(b_upgrade, buffer);
          textprintf_centre_ex(buffer, font2, 735, 658, makecol(255,255,255), -1, "NORMAL");
          textprintf_centre_ex(buffer, font2, 735, 714, makecol(255,255,0), -1, "$%d", TNPRECO);
          textprintf_centre_ex(buffer, font2, 815, 658, makecol(255,255,255), -1, "SLOW");
          textprintf_centre_ex(buffer, font2, 815, 714, makecol(255,255,0), -1, "$%d", TSPRECO);
          textprintf_centre_ex(buffer, font2, 895, 658, makecol(255,255,255), -1, "ANTITANQUE");
          textprintf_centre_ex(buffer, font2, 895, 714, makecol(255,255,0), -1, "$%d", TAPRECO);
          textprintf_centre_ex(buffer, font2, 975, 658, makecol(255,255,255), -1, "VENENO");
          textprintf_centre_ex(buffer, font2, 975, 714, makecol(255,255,0), -1, "$%d", TVPRECO);

          textprintf_ex(buffer, font1, 60, 10, makecol(255,255,255), -1, "$%d", stage->dinheiro);
          textprintf_centre_ex(buffer, font1, SCREEN_W/2-20, 10, makecol(255,255,255), -1, "TURNO: %d/%d", stage->turno_atual, stage->turnos);
          textprintf_right_ex(buffer, font1, SCREEN_W-68, 10, makecol(255,255,255), -1, "VIDAS: %d", stage->vidas);

           if(selecao != NULL && !b_normal->ativado && !b_slow->ativado && !b_antitanque->ativado && !b_veneno->ativado)
           {
             //Imprime informações
             if(selecao->ID == TORRE_NORMAL){
               textprintf_ex(buffer, font2, 300, 660, makecol(255,255,255), -1, "Torre Normal");
               textprintf_ex(buffer, font2, 300, 708, makecol(255,255,255), -1, "Venda $%d", (TNPRECO/2 + ((selecao->level-1)*TNPRECOUP)/2));
             }
             else if(selecao->ID == TORRE_SLOW){
               textprintf_ex(buffer, font2, 300, 660, makecol(255,255,255), -1, "Torre Slow");
               textprintf_ex(buffer, font2, 300, 708, makecol(255,255,255), -1, "Venda $%d", (TSPRECO/2 + ((selecao->level-1)*TSPRECOUP)/2));
             }
             else if(selecao->ID == TORRE_ANTITANQUE){
               textprintf_ex(buffer, font2, 300, 660, makecol(255,255,255), -1, "Torre Antitanque");
               textprintf_ex(buffer, font2, 300, 708, makecol(255,255,255), -1, "Venda $%d", (TAPRECO/2 + ((selecao->level-1)*TAPRECOUP)/2));
             }
             else if(selecao->ID == TORRE_VENENO){
               textprintf_ex(buffer, font2, 300, 660, makecol(255,255,255), -1, "Torre Veneno");
               textprintf_ex(buffer, font2, 300, 708, makecol(255,255,255), -1, "Venda $%d", (TVPRECO/2 + ((selecao->level-1)*TVPRECOUP)/2));
             }

             textprintf_ex(buffer, font2, 300, 672, makecol(255,255,255), -1, "Level %d", selecao->level);
             textprintf_ex(buffer, font2, 300, 684, makecol(255,255,255), -1, "Raio %d", (int)selecao->raio);

             if(selecao->ID == TORRE_SLOW)
              textprintf_ex(buffer, font2, 300, 696, makecol(255,255,255), -1, "Slow %.0f%%", 100*selecao->dano);
             else
              textprintf_ex(buffer, font2, 300, 696, makecol(255,255,255), -1, "Dano/s %.2f", (selecao->dano) / (selecao->to_next_shot/1000.0));

             if(selecao->level < 3)
             {
               if(selecao->ID == TORRE_NORMAL)
                textprintf_ex(buffer, font2, 370, 708, makecol(255,255,255), -1, "/ Upgrade: $%d", TNPRECOUP);
               else if(selecao->ID == TORRE_SLOW)
                textprintf_ex(buffer, font2, 370, 708, makecol(255,255,255), -1, "/ Upgrade: $%d", TSPRECOUP);
               else if(selecao->ID == TORRE_ANTITANQUE)
                textprintf_ex(buffer, font2, 370, 708, makecol(255,255,255), -1, "/ Upgrade: $%d", TAPRECOUP);
               else if(selecao->ID == TORRE_VENENO)
                textprintf_ex(buffer, font2, 370, 708, makecol(255,255,255), -1, "/ Upgrade: $%d", TVPRECOUP);
             }
           }

          if(gameState == FIM_DO_TURNO && (gametime/400)%2 == 0)
            textprintf_centre_ex(buffer, font1, SCREEN_W/2, SCREEN_H/2, makecol(255,255,0), -1, "PREPARE-SE!");

          if(mouse_on_screen())
          draw_sprite(buffer, cursor, mouse_x, mouse_y);

          draw_sprite(screen, buffer, 0, 0);
          clear(buffer);
          vsync();
   }

   stop_midi();

   //FINALIZAÇÃO
   Destroy_Tower_Matrix();
   Destroy_Enemy_List(e_list);
   Destroy_Stage(stage);
   Destroy_TowerButton(b_normal);
   Destroy_TowerButton(b_slow);
   Destroy_TowerButton(b_antitanque);
   Destroy_TowerButton(b_veneno);
   Destroy_Button_Venda(b_vender);
   Destroy_Button_Upgrade(b_upgrade);
   destroy_bitmap(buffer);

   //Fade entre telas
      fade_out(40);
      set_trans_blender(255,255,255,128);
}
