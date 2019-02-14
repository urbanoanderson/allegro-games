#include "Content.h"

void Load_Content()
{
   //Fontes
   font1 = load_font("Fontes/font1.pcx", NULL, NULL);
   font2 = load_font("Fontes/font2.pcx", NULL, NULL);

   //Sons
   SONG_gamescreen = load_midi("Sons/gamescreen.mid");
   SONG_mainmenu = load_midi("Sons/mainmenu.mid");
   SONG_victory = load_midi("Sons/victory.mid");
   SONG_gameover = load_midi("Sons/gameover.mid");
   FX_click = load_sample("Sons/click.wav");
   FX_buy = load_sample("Sons/buy.wav");
   FX_sell = load_sample("Sons/sell.wav");
   FX_error = load_sample("Sons/error.wav");
   FX_select = load_sample("Sons/select.wav");
   FX_upgrade = load_sample("Sons/upgrade.wav");
   FX_machinegun = load_sample("Sons/machinegun.wav");
   FX_cannon = load_sample("Sons/cannon.wav");

   //Bitmaps
   cursor = load_bitmap("Sprites/cursor.bmp", NULL);
   background = load_bitmap("Sprites/BG.bmp", NULL);
   frame = load_bitmap("Sprites/frame.bmp", NULL);
   barraca_ini = load_bitmap("Sprites/barraca_inicio.bmp", NULL);
   barraca_fim = load_bitmap("Sprites/barraca_fim.bmp", NULL);
   soldado = load_bitmap("Sprites/soldado.bmp", NULL);
   soldado_veneno = load_bitmap("Sprites/soldado_veneno.bmp", NULL);
   soldado_slow = load_bitmap("Sprites/soldado_slow.bmp", NULL);
   soldadof = load_bitmap("Sprites/soldadof.bmp", NULL);
   soldadof_veneno = load_bitmap("Sprites/soldadof_veneno.bmp", NULL);
   soldadof_slow = load_bitmap("Sprites/soldadof_slow.bmp", NULL);
   moto = load_bitmap("Sprites/moto.bmp", NULL);
   moto_veneno = load_bitmap("Sprites/moto_veneno.bmp", NULL);
   moto_slow = load_bitmap("Sprites/moto_slow.bmp", NULL);
   tank = load_bitmap("Sprites/tank.bmp", NULL);
   tank_slow = load_bitmap("Sprites/tank_slow.bmp", NULL);
   b_torre_h = load_bitmap("Sprites/b_torre_h.bmp", NULL);
   torre_normal = load_bitmap("Sprites/torre_normal.bmp", NULL);
   torre_slow = load_bitmap("Sprites/torre_slow.bmp", NULL);
   torre_antitanque = load_bitmap("Sprites/torre_antitanque.bmp", NULL);
   torre_veneno = load_bitmap("Sprites/torre_veneno.bmp", NULL);
   vender = load_bitmap("Sprites/vender.bmp", NULL);
   vender_h = load_bitmap("Sprites/vender_h.bmp", NULL);
   vender_desativado = load_bitmap("Sprites/vender_desativado.bmp", NULL);
   upgrade = load_bitmap("Sprites/upgrade.bmp", NULL);
   upgrade_h = load_bitmap("Sprites/upgrade_h.bmp", NULL);
   upgrade_desativado = load_bitmap("Sprites/upgrade_desativado.bmp", NULL);
   marca_upgrade = load_bitmap("Sprites/marca_upgrade.bmp", NULL);

   mainBG = load_bitmap("Sprites/mainBG.bmp", NULL);
   main_b_play = load_bitmap("Sprites/main_b_play.bmp", NULL);
   main_b_play_h = load_bitmap("Sprites/main_b_play_h.bmp", NULL);
   main_b_exit = load_bitmap("Sprites/main_b_exit.bmp", NULL);
   main_b_exit_h = load_bitmap("Sprites/main_b_exit_h.bmp", NULL);

   gameoverBG = load_bitmap("Sprites/gameover.bmp", NULL);
   victoryBG = load_bitmap("Sprites/victory.bmp", NULL);
}

void Unload_Content()
{
   destroy_font(font1);
   destroy_font(font2);
   destroy_midi(SONG_gamescreen);
   destroy_midi(SONG_mainmenu);
   destroy_midi(SONG_victory);
   destroy_midi(SONG_gameover);
   destroy_sample(FX_click);
   destroy_sample(FX_buy);
   destroy_sample(FX_sell);
   destroy_sample(FX_error);
   destroy_sample(FX_select);
   destroy_sample(FX_upgrade);
   destroy_sample(FX_machinegun);
   destroy_sample(FX_cannon);
   destroy_bitmap(cursor);
   destroy_bitmap(background);
   destroy_bitmap(frame);
   destroy_bitmap(barraca_ini);
   destroy_bitmap(barraca_fim);
   destroy_bitmap(soldado);
   destroy_bitmap(soldadof);
   destroy_bitmap(moto);
   destroy_bitmap(moto_veneno);
   destroy_bitmap(tank);
   destroy_bitmap(b_torre_h);
   destroy_bitmap(torre_normal);
   destroy_bitmap(torre_slow);
   destroy_bitmap(torre_antitanque);
   destroy_bitmap(torre_veneno);
   destroy_bitmap(vender);
   destroy_bitmap(vender_h);
   destroy_bitmap(vender_desativado);
   destroy_bitmap(upgrade);
   destroy_bitmap(upgrade_h);
   destroy_bitmap(upgrade_desativado);
   destroy_bitmap(marca_upgrade);

   destroy_bitmap(mainBG);
   destroy_bitmap(main_b_play);
   destroy_bitmap(main_b_play_h);
   destroy_bitmap(main_b_exit);
   destroy_bitmap(main_b_exit_h);

   destroy_bitmap(gameoverBG);
   destroy_bitmap(victoryBG);
}
