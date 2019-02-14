#include "content.h"

///BITMAPS===================
ALLEGRO_BITMAP* main_bg;
ALLEGRO_BITMAP* main_title;
ALLEGRO_BITMAP* main_balao;
ALLEGRO_BITMAP* main_dirigivel1;
ALLEGRO_BITMAP* main_dirigivel2;

ALLEGRO_BITMAP* game_tile[5];
ALLEGRO_BITMAP* game_brick_explosion;
ALLEGRO_BITMAP* game_portal;
ALLEGRO_BITMAP* game_barra_superior;
ALLEGRO_BITMAP* game_player_up;
ALLEGRO_BITMAP* game_player_down;
ALLEGRO_BITMAP* game_player_left;
ALLEGRO_BITMAP* game_player_right;
ALLEGRO_BITMAP* game_enemy_up;
ALLEGRO_BITMAP* game_enemy_down;
ALLEGRO_BITMAP* game_enemy_left;
ALLEGRO_BITMAP* game_enemy_right;
ALLEGRO_BITMAP* game_bomb;
ALLEGRO_BITMAP* game_upgrade_bomba_extra;
ALLEGRO_BITMAP* game_upgrade_fogo;
ALLEGRO_BITMAP* game_upgrade_patins;
ALLEGRO_BITMAP* game_upgrade_chuta_bomba;
ALLEGRO_BITMAP* game_upgrade_vida;
ALLEGRO_BITMAP* game_upgrade_bomba_relogio;
ALLEGRO_BITMAP* game_bomba_relogio;
ALLEGRO_BITMAP* game_upgrade_bomba_espinho;
ALLEGRO_BITMAP* game_bomba_espinho;

ALLEGRO_BITMAP* victory_yellow;
ALLEGRO_BITMAP* victory_green;
ALLEGRO_BITMAP* victory_blue;
ALLEGRO_BITMAP* victory_orange;
ALLEGRO_BITMAP* victory_floor;
ALLEGRO_BITMAP* victory_bomberman;

ALLEGRO_BITMAP* gameover_bg;
ALLEGRO_BITMAP* gameover_animation;
ALLEGRO_BITMAP* gameover_title;
///==========================

///FONTES====================
ALLEGRO_FONT* font_debug;
ALLEGRO_FONT* font_bomberman;
ALLEGRO_FONT* font_menu;
///==========================

///SONS======================
ALLEGRO_SAMPLE* BGM_mainmenu;
ALLEGRO_SAMPLE* SFX_menusound1;
ALLEGRO_SAMPLE* SFX_menusound2;

ALLEGRO_SAMPLE* BGM_gamescreen;
ALLEGRO_SAMPLE* SFX_put_bomb;
ALLEGRO_SAMPLE* SFX_explosion;
ALLEGRO_SAMPLE* SFX_pick_upgrade;

ALLEGRO_SAMPLE* BGM_victory;

ALLEGRO_SAMPLE* BGM_gameover;
///==========================


///=================================
///DEFAULT
///=================================
void LoadDefaultContent()
{
    ///BITMAPS
    game_bomb = al_load_bitmap("Sprites/GAMESCREEN/bomba.png");

    //al_convert_mask_to_alpha(sprite, al_map_rgb(255, 0, 255));

    ///FONTES
    font_debug = al_load_ttf_font("Fontes/debug.ttf", 10,  ALLEGRO_TTF_MONOCHROME);
    font_bomberman = al_load_ttf_font("Fontes/bomberman.ttf", 45,  ALLEGRO_TTF_MONOCHROME);
    font_menu = al_load_ttf_font("Fontes/menu.ttf", 30,  ALLEGRO_TTF_MONOCHROME);


    ///SONS
    SFX_menusound1 = al_load_sample("Sons/SFX/menusound1.wav");
	SFX_menusound2 = al_load_sample("Sons/SFX/menusound2.wav");
}

void UnloadDefaultContent()
{
    //BITMAPS
    al_destroy_bitmap(game_bomb);

    //FONTES
    al_destroy_font(font_debug);
    al_destroy_font(font_bomberman);
    al_destroy_font(font_menu);

    //SONS
    al_destroy_sample(SFX_menusound1);
    al_destroy_sample(SFX_menusound2);
}

///=================================
///MAINMENU
///=================================
void LoadMainmenuContent()
{
    //BITMAPS
    main_bg = al_load_bitmap("Sprites/MAINMENU/bg.png");
    main_title = al_load_bitmap("Sprites/MAINMENU/title.png");
    main_balao = al_load_bitmap("Sprites/MAINMENU/balao.png");
    main_dirigivel1 = al_load_bitmap("Sprites/MAINMENU/dirigivel1.png");
    main_dirigivel2 = al_load_bitmap("Sprites/MAINMENU/dirigivel2.png");

    //SONS
	BGM_mainmenu = al_load_sample("Sons/BGM/mainmenu.ogg");
}

void UnloadMainmenuContent()
{
    //BITMAPS
    al_destroy_bitmap(main_bg);
    al_destroy_bitmap(main_title);
    al_destroy_bitmap(main_balao);
    al_destroy_bitmap(main_dirigivel1);
    al_destroy_bitmap(main_dirigivel2);

    //SONS
    al_destroy_sample(BGM_mainmenu);
}

///=================================
///GAMESCREEN
///=================================
void LoadGamescreenContent()
{
    //BITMAPS
    game_tile[0] = al_load_bitmap("Sprites/GAMESCREEN/tiles/grass.png");
    game_tile[1] = al_load_bitmap("Sprites/GAMESCREEN/tiles/brick.png");
    game_tile[2] = al_load_bitmap("Sprites/GAMESCREEN/tiles/block.png");
    game_tile[3] = al_load_bitmap("Sprites/GAMESCREEN/tiles/wall.png");
    game_tile[4] = game_tile[0];
    game_brick_explosion = al_load_bitmap("Sprites/GAMESCREEN/tiles/brick explosion.png");
    game_portal = al_load_bitmap("Sprites/GAMESCREEN/portal.png");
    game_barra_superior = al_load_bitmap("Sprites/GAMESCREEN/barra superior.png");
    game_player_up = al_load_bitmap("Sprites/GAMESCREEN/player up.png");
    game_player_down = al_load_bitmap("Sprites/GAMESCREEN/player down.png");
    game_player_left = al_load_bitmap("Sprites/GAMESCREEN/player left.png");
    game_player_right = al_load_bitmap("Sprites/GAMESCREEN/player right.png");
    game_enemy_up = al_load_bitmap("Sprites/GAMESCREEN/enemy up.png");
    game_enemy_down = al_load_bitmap("Sprites/GAMESCREEN/enemy down.png");
    game_enemy_left = al_load_bitmap("Sprites/GAMESCREEN/enemy left.png");
    game_enemy_right = al_load_bitmap("Sprites/GAMESCREEN/enemy right.png");
    game_upgrade_bomba_extra = al_load_bitmap("Sprites/GAMESCREEN/upgrades/bomba extra.png");
    game_upgrade_fogo = al_load_bitmap("Sprites/GAMESCREEN/upgrades/fogo.png");
    game_upgrade_patins = al_load_bitmap("Sprites/GAMESCREEN/upgrades/patins.png");
    game_upgrade_chuta_bomba = al_load_bitmap("Sprites/GAMESCREEN/upgrades/chuta bomba.png");
    game_upgrade_vida = al_load_bitmap("Sprites/GAMESCREEN/upgrades/vida.png");
    game_upgrade_bomba_relogio = al_load_bitmap("Sprites/GAMESCREEN/upgrades/bomba relogio.png");
    game_bomba_relogio = al_load_bitmap("Sprites/GAMESCREEN/bomba relogio.png");
    game_upgrade_bomba_espinho = al_load_bitmap("Sprites/GAMESCREEN/upgrades/bomba espinho.png");
    game_bomba_espinho = al_load_bitmap("Sprites/GAMESCREEN/bomba espinho.png");

	//SONS
	BGM_gamescreen = al_load_sample("Sons/BGM/gamescreen.ogg");
	SFX_put_bomb = al_load_sample("Sons/SFX/put bomb.wav");
	SFX_explosion = al_load_sample("Sons/SFX/explosion.wav");
	SFX_pick_upgrade = al_load_sample("Sons/SFX/pick upgrade.wav");
}

void UnloadGamescreenContent()
{
    //BITMAPS
    al_destroy_bitmap(game_tile[0]);
    al_destroy_bitmap(game_tile[1]);
    al_destroy_bitmap(game_tile[2]);
    al_destroy_bitmap(game_tile[3]);
    al_destroy_bitmap(game_brick_explosion);
    al_destroy_bitmap(game_portal);
    al_destroy_bitmap(game_barra_superior);
    al_destroy_bitmap(game_player_up);
    al_destroy_bitmap(game_player_down);
    al_destroy_bitmap(game_player_left);
    al_destroy_bitmap(game_player_right);
    al_destroy_bitmap(game_enemy_up);
    al_destroy_bitmap(game_enemy_down);
    al_destroy_bitmap(game_enemy_left);
    al_destroy_bitmap(game_enemy_right);
    al_destroy_bitmap(game_upgrade_bomba_extra);
    al_destroy_bitmap(game_upgrade_fogo);
    al_destroy_bitmap(game_upgrade_patins);
    al_destroy_bitmap(game_upgrade_chuta_bomba);
    al_destroy_bitmap(game_upgrade_vida);
    al_destroy_bitmap(game_upgrade_bomba_relogio);
    al_destroy_bitmap(game_bomba_relogio);
    al_destroy_bitmap(game_upgrade_bomba_espinho);
    al_destroy_bitmap(game_bomba_espinho);

    //SONS
	al_destroy_sample(BGM_gamescreen);
    al_destroy_sample(SFX_put_bomb);
    al_destroy_sample(SFX_explosion);
    al_destroy_sample(SFX_pick_upgrade);
}

///=================================
///GAMEOVER
///=================================
void LoadGameoverContent()
{
    //BITMAPS
    gameover_bg = al_load_bitmap("Sprites/GAMEOVER/bg.png");
    gameover_title = al_load_bitmap("Sprites/GAMEOVER/title.png");
    gameover_animation = al_load_bitmap("Sprites/GAMEOVER/animation.png");

    //SONS
    BGM_gameover = al_load_sample("Sons/BGM/gameover.ogg");
}

void UnloadGameoverContent()
{
    //BITMAPS
    al_destroy_bitmap(gameover_bg);
    al_destroy_bitmap(gameover_animation);
    al_destroy_bitmap(gameover_title);

    //SONS
    al_destroy_sample(BGM_gameover);
}

///=================================
///VICTORY
///=================================
void LoadVictoryContent()
{
    //BITMAPS
    victory_yellow = al_load_bitmap("Sprites/VICTORY/yellow.png");
    victory_green = al_load_bitmap("Sprites/VICTORY/green.png");
    victory_blue = al_load_bitmap("Sprites/VICTORY/blue.png");
    victory_orange = al_load_bitmap("Sprites/VICTORY/orange.png");
    victory_floor = al_load_bitmap("Sprites/VICTORY/floor.png");
    victory_bomberman = al_load_bitmap("Sprites/VICTORY/bomberman.png");

    //SONS
    BGM_victory = al_load_sample("Sons/BGM/victory.ogg");
}

void UnloadVictoryContent()
{
    //BITMAPS
    al_destroy_bitmap(victory_yellow);
    al_destroy_bitmap(victory_green);
    al_destroy_bitmap(victory_blue);
    al_destroy_bitmap(victory_orange);
    al_destroy_bitmap(victory_floor);
    al_destroy_bitmap(victory_bomberman);

    //SONS
    al_destroy_sample(BGM_victory);
}
