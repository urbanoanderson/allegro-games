#ifndef INIT_HPP_INCLUDED
#define INIT_HPP_INCLUDED

#include <allegro.h>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <list>
#include <string>

using namespace std;

#include "content.hpp"
#include "keyboard.hpp"
#include "xbox.hpp"
#include "highscores.hpp"

enum GAMESCREEN_FLAGS{ ARCADE_MODE = 0, CHALLENGE1 = 1, CHALLENGE2 = 2, CHALLENGE3 = 3 };
enum CONFIG_OPTIONS{ SFX, BGM, VIDEO_MODE, VSYNC, SAVE_EXIT, DONT_SAVE };
enum VIDEOMODE { FULLSCREEN, WINDOWED };
enum CURRENT_SCREEN { MAINMENU, OPTIONSCREEN, GAMESCREEN };
enum DIRECTION { NONE = 0, LEFT = -1, RIGHT = 1, UP = -1, DOWN = 1 };

enum GAMEOBJECT_ID
{
  SPACESHIP, SHIELD,
  ENEMY_A, ENEMY_B, ENEMY_C, ENEMY_D, ENEMY_E, ENEMY_F, TOTAL_ENEMY_TYPES,
  PW_UP_SHIELD, PW_UP_SPEED, PW_UP_LIFE,
  EXPLOSION, EXPL_SHIELD, EXPL_SMALL, EXPL_MEDIUM, EXPL_LARGE,
  SHOT_LV0, SHOT_LV1, SHOT_LV2,
  SHOT_ENEMY_A, SHOT_ENEMY_B, SHOT_ENEMY_C, SHOT_ENEMY_D, SHOT_ENEMY_E, SHOT_ENEMY_F, TOTAL_ENEMY_SHOT_TYPES,
};

///**********************
///GLOBAIS
///**********************

///ALLEGRO
extern BITMAP* buffer;
extern volatile bool exit_program;
extern volatile int milisegundos;
extern volatile int player_time;
int randnum(int max);

///USER OPTIONS
extern int timer_fps;
extern int vol_SFX;
extern int vol_BGM;
extern bool usevsync;
extern bool video_mode;
///***********************

void fecha_programa();
void msec_counter();
void survival_counter();

int init();
void deinit();
int Load_user_configuration();
void Save_user_configuration();

#endif // INIT_HPP_INCLUDED
