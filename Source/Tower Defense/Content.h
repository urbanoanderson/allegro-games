#ifndef CONTENT_H_INCLUDED
#define CONTENT_H_INCLUDED

#include <allegro.h>

//----------------------------------------------
//GAMESCREEN

//FONTES
FONT* font1;
FONT* font2;

//SONS
MIDI* SONG_gamescreen;
MIDI* SONG_mainmenu;
MIDI* SONG_victory;
MIDI* SONG_gameover;
SAMPLE* FX_click;
SAMPLE* FX_buy;
SAMPLE* FX_sell;
SAMPLE* FX_error;
SAMPLE* FX_select;
SAMPLE* FX_upgrade;
SAMPLE* FX_machinegun;
SAMPLE* FX_cannon;

//BITMAPS
BITMAP* cursor;
BITMAP* background;
BITMAP* frame;
BITMAP* barraca_ini;
BITMAP* barraca_fim;

BITMAP* soldado;
BITMAP* soldado_veneno;
BITMAP* soldado_slow;
BITMAP* soldadof;
BITMAP* soldadof_veneno;
BITMAP* soldadof_slow;
BITMAP* moto;
BITMAP* moto_veneno;
BITMAP* moto_slow;
BITMAP* tank;
BITMAP* tank_slow;

BITMAP* b_torre_h;

BITMAP* torre_normal;
BITMAP* torre_slow;
BITMAP* torre_antitanque;
BITMAP* torre_veneno;

BITMAP* vender;
BITMAP* vender_h;
BITMAP* vender_desativado;
BITMAP* upgrade;
BITMAP* upgrade_h;
BITMAP* upgrade_desativado;
BITMAP* marca_upgrade;

//----------------------------------------------
//MAINMENU E OUTRAS TELAS
BITMAP* mainBG;
BITMAP* main_b_play;
BITMAP* main_b_play_h;
BITMAP* main_b_exit;
BITMAP* main_b_exit_h;

BITMAP* gameoverBG;
BITMAP* victoryBG;

//----------------------------------------------

void Load_Content();
void Unload_Content();

#endif // CONTENT_H_INCLUDED
