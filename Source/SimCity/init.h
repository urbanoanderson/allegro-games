#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <allegro.h>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>

#include "content.h"
#include "keyboard.h"

///****************
///ENUMS
enum {WINDOWED,FULLSCREEN};
enum {NONE, SMALL, MEDIUM,  LARGE};
enum {SPLASHSCREEN, MAINMENU, GAMESCREEN, OPTIONSCREEN, PLAYMENU, NEWGAME, LOADGAME, TELA_ERRO};
enum {NAO_CONSTRUIR, CONSTRUIR_CASA, CONSTRUIR_AGUA, CONSTRUIR_FLORESTA, CONSTRUIR_RUA, DESCONSTRUIR};
enum {NULO, CASA, FLORESTA, AGUA, RUA, TERRA, CONSTRUCAO_CASA, CONSTRUCAO_FLORESTA, CONSTRUCAO_AGUA, CONSTRUCAO_RUA, DESTRUICAO};
enum {SEM_DESASTRE, ASSALTO, HOMICIDIO, CHACINA, INCENDIO, ENCHENTE, METEORITOS, MST, ALIEN, PROVA_IP};


///*******************
///VARIÁVEIS GLOBAIS
extern volatile bool exit_program;
extern volatile int milisegundos;
extern int screenstate;              //Controla as telas do jogo
extern int screenmode;               //Controla a Janela (WINDOWED ou FULLSCREEN)
extern int volume;
extern int mapNum;                   //Quantos mapas padrão existem
extern bool is_playing;
extern bool erro_newload;
extern BITMAP* buffer;
extern int prev_mouse_b;


///*******************
///FUNÇÕES
void contaMilisegundos();
void Exit_Game();
void init();
void deinit();
void Load_user_configuration();
void Save_user_configuration();
bool Clicou(int b);
void Receive_Mouse_Input();


#endif // INIT_H_INCLUDED
