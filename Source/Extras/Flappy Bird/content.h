#ifndef CONTENT_H_INCLUDED
#define CONTENT_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

///BITMAPS================================================
extern ALLEGRO_BITMAP* main_bg;

extern ALLEGRO_BITMAP* game_background;
extern ALLEGRO_BITMAP* game_ground;
extern ALLEGRO_BITMAP* game_player;
extern ALLEGRO_BITMAP* game_pipe;
///=======================================================

///FONTES=================================================
extern ALLEGRO_FONT* font_debug;
extern ALLEGRO_FONT* font_mensagem;
///========================================================

///SONS=====================================================
extern ALLEGRO_SAMPLE* BGM_mainmenu;
extern ALLEGRO_SAMPLE* BGM_gamescreen;
extern ALLEGRO_SAMPLE* SFX_ponto;
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
