#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <allegro.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Content.h"
#include "Keyboard.h"

#define X0 60
#define Y0 60
#define TILESIZE 60
#define NUMTILESI 10
#define NUMTILESJ 15

#define TNDANOLV1 7.0
#define TNDANOLV2 7.85
#define TNDANOLV3 8.5
#define TNRAIOLV1 90.0
#define TNRAIOLV2 100.0
#define TNRAIOLV3 110.0
#define TNPRECO 4
#define TNPRECOUP 3

#define TSSLOWLV1 0.3
#define TSSLOWLV2 0.45
#define TSSLOWLV3 0.60
#define TSRAIOLV1 100.0
#define TSRAIOLV2 110.0
#define TSRAIOLV3 120.0
#define TSPRECO 6
#define TSPRECOUP 4

#define TADANOLV1 40.0
#define TADANOLV2 50.0
#define TADANOLV3 55.0
#define TARAIOLV1 100.0
#define TARAIOLV2 110.0
#define TARAIOLV3 120.0
#define TAPRECO 8
#define TAPRECOUP 6

#define TVDANOLV1 0.25
#define TVDANOLV2 0.30
#define TVDANOLV3 0.40
#define TVRAIOLV1 120.0
#define TVRAIOLV2 125.0
#define TVRAIOLV3 130.0
#define TVPRECO 12
#define TVPRECOUP 10

#define SOLDADOBONUS 1
#define SOLDADOFBONUS 1
#define MOTOBONUS 2
#define TANQUEBONUS 4

//ENUMS
enum DIRECTION { NONE = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 };
enum ENEMIES { SOLDADO, SOLDADO_FORTE, MOTO, TANQUE };
enum TOWERS { TORRE_NORMAL, TORRE_SLOW, TORRE_VENENO, TORRE_ANTITANQUE };
enum GAMESTATE { JOGANDO, FIM_DO_TURNO };
enum SCREEN { MAINMENU, GAMESCREEN, GAMEOVER, VITORIA };

//VARIÁVEIS GLOBAIS
volatile int exit_program;
int screen_state;
volatile int gametime;
int fps_timer;

//FUNÇÕES BÁSICAS
void GameTimeCounter();
void Exit_Game();
void init();
void deinit();

int contador;
void* malloc2 (size_t size);
void free2 (void* ptr);

//FÍSICA
float Distancia(float x1, float y1, float x2, float y2);
double graus(double rads);
fixed GRAUS_ALLEGRO(float graus);
double rads(double graus);

void fade_out(int velocidade);

#endif
