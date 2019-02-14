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
#include <ctype.h>
#include <cstdio>
#include <cstdlib>

#include "defines.h"
#include "content.h"

///GLOBAIS
extern int screenstate;
extern bool exit_program;
extern bool desenhar;
extern float volBGM;
extern float volSFX;
extern bool DEBUG;

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
float regVolume(float value);

#endif
