#ifndef CONTENT_H_INCLUDED
#define CONTENT_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

///BITMAPS================================================
extern ALLEGRO_BITMAP* main_bg;
extern ALLEGRO_BITMAP* main_title;
extern ALLEGRO_BITMAP* main_balao;
extern ALLEGRO_BITMAP* main_dirigivel1;
extern ALLEGRO_BITMAP* main_dirigivel2;

extern ALLEGRO_BITMAP* game_tile[5];
extern ALLEGRO_BITMAP* game_brick_explosion;
extern ALLEGRO_BITMAP* game_portal;
extern ALLEGRO_BITMAP* game_barra_superior;
extern ALLEGRO_BITMAP* game_player_up;
extern ALLEGRO_BITMAP* game_player_down;
extern ALLEGRO_BITMAP* game_player_left;
extern ALLEGRO_BITMAP* game_player_right;
extern ALLEGRO_BITMAP* game_enemy_up;
extern ALLEGRO_BITMAP* game_enemy_down;
extern ALLEGRO_BITMAP* game_enemy_left;
extern ALLEGRO_BITMAP* game_enemy_right;
extern ALLEGRO_BITMAP* game_bomb;
extern ALLEGRO_BITMAP* game_upgrade_bomba_extra;
extern ALLEGRO_BITMAP* game_upgrade_fogo;
extern ALLEGRO_BITMAP* game_upgrade_patins;
extern ALLEGRO_BITMAP* game_upgrade_chuta_bomba;
extern ALLEGRO_BITMAP* game_upgrade_vida;
extern ALLEGRO_BITMAP* game_upgrade_bomba_relogio;
extern ALLEGRO_BITMAP* game_bomba_relogio;
extern ALLEGRO_BITMAP* game_upgrade_bomba_espinho;
extern ALLEGRO_BITMAP* game_bomba_espinho;

extern ALLEGRO_BITMAP* victory_yellow;
extern ALLEGRO_BITMAP* victory_green;
extern ALLEGRO_BITMAP* victory_blue;
extern ALLEGRO_BITMAP* victory_orange;
extern ALLEGRO_BITMAP* victory_floor;
extern ALLEGRO_BITMAP* victory_bomberman;

extern ALLEGRO_BITMAP* gameover_bg;
extern ALLEGRO_BITMAP* gameover_animation;
extern ALLEGRO_BITMAP* gameover_title;
///=======================================================

///FONTES=================================================
extern ALLEGRO_FONT* font_debug;
extern ALLEGRO_FONT* font_bomberman;
extern ALLEGRO_FONT* font_menu;
///========================================================

///SONS=====================================================
extern ALLEGRO_SAMPLE* BGM_mainmenu;
extern ALLEGRO_SAMPLE* SFX_menusound1;
extern ALLEGRO_SAMPLE* SFX_menusound2;

extern ALLEGRO_SAMPLE* BGM_gamescreen;
extern ALLEGRO_SAMPLE* SFX_put_bomb;
extern ALLEGRO_SAMPLE* SFX_explosion;
extern ALLEGRO_SAMPLE* SFX_pick_upgrade;

extern ALLEGRO_SAMPLE* BGM_victory;

extern ALLEGRO_SAMPLE* BGM_gameover;
///=========================================================


void LoadDefaultContent();
void UnloadDefaultContent();
void LoadMainmenuContent();
void UnloadMainmenuContent();
void LoadGamescreenContent();
void UnloadGamescreenContent();
void LoadGameoverContent();
void UnloadGameoverContent();
void LoadVictoryContent();
void UnloadVictoryContent();

#endif
