#include "content.h"

///BITMAPS================================================
ALLEGRO_BITMAP* main_bg;

ALLEGRO_BITMAP* game_background;
ALLEGRO_BITMAP* game_ground;
ALLEGRO_BITMAP* game_player;
ALLEGRO_BITMAP* game_pipe;
///=======================================================

///FONTES=================================================
ALLEGRO_FONT* font_debug;
ALLEGRO_FONT* font_mensagem;
///========================================================

///SONS=====================================================
ALLEGRO_SAMPLE* BGM_mainmenu;
ALLEGRO_SAMPLE* BGM_gamescreen;
ALLEGRO_SAMPLE* SFX_ponto;
///=========================================================


///=================================
///DEFAULT
///=================================
void LoadDefaultContent()
{
    ///FONTES
    font_debug = al_load_ttf_font("Fontes/debug.ttf", 10,  ALLEGRO_TTF_MONOCHROME);
    font_mensagem = al_load_ttf_font("Fontes/mensagem.ttf", 28,  ALLEGRO_TTF_MONOCHROME);
}

void UnloadDefaultContent()
{
    //BITMAPS

    //FONTES
    al_destroy_font(font_debug);
    al_destroy_font(font_mensagem);

    //SONS
}

///=================================
///MAINMENU
///=================================
void LoadMainmenuContent()
{
    //BITMAPS
    main_bg = al_load_bitmap("Sprites/MAINMENU/background.png");

    //SONS
	BGM_mainmenu = al_load_sample("Sons/BGM/mainmenu.ogg");
}

void UnloadMainmenuContent()
{
    //BITMAPS
    al_destroy_bitmap(main_bg);

    //SONS
    al_destroy_sample(BGM_mainmenu);
}

///=================================
///GAMESCREEN
///=================================
void LoadGamescreenContent()
{
    //BITMAPS
    game_background = al_load_bitmap("Sprites/GAMESCREEN/background.png");
    game_ground = al_load_bitmap("Sprites/GAMESCREEN/ground.png");
    game_player = al_load_bitmap("Sprites/GAMESCREEN/player.png");
    game_pipe = al_load_bitmap("Sprites/GAMESCREEN/pipe.png");

	//SONS
	BGM_gamescreen = al_load_sample("Sons/BGM/gamescreen.ogg");
	SFX_ponto = al_load_sample("Sons/SFX/ponto.wav");
}

void UnloadGamescreenContent()
{
    //BITMAPS
    al_destroy_bitmap(game_background);
    al_destroy_bitmap(game_ground);
    al_destroy_bitmap(game_player);
    al_destroy_bitmap(game_pipe);

    //SONS
	al_destroy_sample(BGM_gamescreen);
	al_destroy_sample(SFX_ponto);
}
