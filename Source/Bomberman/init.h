#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_physfs.h>
#include <physfs.h>

#include <list>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "content.h"

#define DEBUG 1
extern bool debug_mode;

//Defines dos botões do PSX
#define PSX_TRIANGLE 0
#define PSX_CIRCLE   1
#define PSX_CROSS    2
#define PSX_SQUARE   3
#define PSX_L2       4
#define PSX_R2       5
#define PSX_L1       6
#define PSX_R1       7
#define PSX_SELECT   8
#define PSX_START    9
#define PSX_L3       10
#define PSX_R3       11

///ENUMS
enum STATE{ MAINMENU, GAMESCREEN, VICTORY, GAMEOVER };
enum DIRECTION { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

///GLOBAIS
const int SCREEN_W = 950;
const int SCREEN_H = 750;
const double FPS = 60;
extern int screenstate;
extern bool exit_program;
extern bool desenhar;
extern float volBGM;
extern float volSFX;

extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_EVENT ev;
extern ALLEGRO_TIMER* timer_FPS;
extern ALLEGRO_BITMAP* icon;
extern ALLEGRO_KEYBOARD_STATE keystate;
extern ALLEGRO_JOYSTICK* joy1;
extern ALLEGRO_JOYSTICK_STATE joy1_state;

///FUNÇÕES
void init();
void deinit();
int width(ALLEGRO_BITMAP* img);
int height(ALLEGRO_BITMAP* img);
void fade(int r, int g, int b, float speed);
int max(int a, int b);
int min(int a, int b);
int oposite_direction(int dir);

#endif
