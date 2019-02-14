#ifndef CONTENT_HPP_INCLUDED
#define CONTENT_HPP_INCLUDED

#include <allegro.h>
#include "datafile_fonts.h"
#include "datafile_music.h"
#include "datafile_sfx.h"
#include "datafile_menu.h"
#include "datafile_graphics.h"

#define MAX_BG 4
#define MAX_PLANETAS 5

typedef struct content
{
  DATAFILE* datafile_fonts;
  DATAFILE* datafile_graphics;
  DATAFILE* datafile_music;
  DATAFILE* datafile_sfx;
  DATAFILE* datafile_menu;

  ///==================================
  ///BITMAPS
  ///==================================

  //MAINMENU
  BITMAP* main_BG;
  BITMAP* main_logo;
  BITMAP* main_selection;
  BITMAP* main_arrow;

  //GAMESCREEN
  BITMAP* pause_window;
  BITMAP* pause_b_mainmenu;
  BITMAP* pause_b_resume;
  BITMAP* pause_b_h;
  BITMAP* game_timebar;
  BITMAP* game_nave;
  BITMAP* game_imortal;
  BITMAP* game_barreira;
  BITMAP* game_life_counter;
  BITMAP* game_shot_lv0;
  BITMAP* game_shot_lv1;
  BITMAP* game_shot_lv2;
  BITMAP* game_charging1;
  BITMAP* game_charging2;
  BITMAP* game_shield_bar;
  BITMAP* game_shield_bar_pts;
  BITMAP* game_enemyA;
  BITMAP* game_enemyA_tiro;
  BITMAP* game_enemyB;
  BITMAP* game_enemyB_dano;
  BITMAP* game_enemyB_tiro;
  BITMAP* game_enemyC;
  BITMAP* game_enemyC_dano;
  BITMAP* game_enemyC_tiro;
  BITMAP* game_enemyD;
  BITMAP* game_enemyD_dano;
  BITMAP* game_enemyD_tiro;
  BITMAP* game_enemyE;
  BITMAP* game_enemyE_dano;
  BITMAP* game_enemyE_tiro;
  BITMAP* game_enemyF;
  BITMAP* game_enemyF_dano;
  BITMAP* game_enemyF_warning;
  BITMAP* game_enemyF_tiro;
  BITMAP* game_explosion_small;
  BITMAP* game_explosion_medium;
  BITMAP* game_explosion_large;
  BITMAP* game_explosion_shield;
  BITMAP* game_teleport;
  BITMAP* game_powerup_extra_life;
  BITMAP* game_powerup_shield_recharge;
  BITMAP* game_powerup_speed_boost;
  BITMAP* game_gameover_msg;
  BITMAP* game_BG[MAX_BG];
  BITMAP* game_planetas[MAX_PLANETAS];

  ///==================================
  ///SONS
  ///==================================

  //DEFAULT
  SAMPLE* FX_click1;
  SAMPLE* FX_click2;
  SAMPLE* FX_click3;
  SAMPLE* FX_click4;
  SAMPLE* FX_transition;

  //MAINMENU
  MIDI* SONG_mainmenu;

  //GAMESCREEN
  SAMPLE* FX_pause;
  SAMPLE* FX_tiro_lv0;
  SAMPLE* FX_tiro_lv1;
  SAMPLE* FX_tiro_lv2;
  SAMPLE* FX_tiro_A;
  SAMPLE* FX_tiro_E;
  SAMPLE* FX_warning_F;
  SAMPLE* FX_powerup;
  SAMPLE* FX_explosao_small;
  SAMPLE* FX_explosao_medium;
  SAMPLE* FX_explosao_large;
  SAMPLE* FX_explosao_shield;
  SAMPLE* FX_barreira;
  SAMPLE* FX_charging;
  SAMPLE* FX_fullcharge;
  SAMPLE* VOICE_gameover;
  SAMPLE* VOICE_ready;
  SAMPLE* VOICE_go;
  MIDI* soundtrack[12];

  ///==================================
  ///FONTES
  ///==================================

  //DEFAULT
  FONT* font_title_options;
  FONT* font_help;
  FONT* font_options;
  FONT* font_pause;
  FONT* font_score;
  FONT* font_shield;
  FONT* font_time;
  FONT* font_highscores;
  FONT* font_ready;

}Content;

extern Content* c;

Content* create_content();
void destroy_content(Content* c);

int Load_Gamescreen_Content(Content* c);
void Unload_Gamescreen_Content(Content* c);


#endif // CONTENT_H_INCLUDED
