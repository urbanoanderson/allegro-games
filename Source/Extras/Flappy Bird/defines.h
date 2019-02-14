#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

///ENUMS
enum SCREENS{ MAINMENU, GAMESCREEN };

//CONFIGURAÇÕES
#define SCREEN_W 800
#define SCREEN_H 600
#define FPS 60

//BOTÕES DO PSX
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

//GAME
#define GRAVITY 0.5
#define PLAYER_INITIAL_X 370
#define PLAYER_INITIAL_Y 250
#define PLAYER_JUMP_SPEED -9.0

#define GROUND_Y 490
#define BACKGROUND_SPEED 2.5
#define PIPE_WIDTH 125
#define SPACE_BEETWEEN_PIPES 175

#define MINIMUM_SPACE_UP   250
#define MINIMUM_SPACE_DOWN 250


#endif
