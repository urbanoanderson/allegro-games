#ifndef XBOX_HPP_INCLUDED
#define XBOX_HPP_INCLUDED

#include <allegro.h>

enum
{
  BUTTON_A,
  BUTTON_B,
  BUTTON_X,
  BUTTON_Y,
  BUTTON_LB,
  BUTTON_RB,
  BUTTON_LS,
  BUTTON_RS,
  BUTTON_BACK,
  BUTTON_START,

  DPAD_UP,
  DPAD_DOWN,
  DPAD_LEFT,
  DPAD_RIGHT,

  LSTICK_UP,
  LSTICK_DOWN,
  LSTICK_LEFT,
  LSTICK_RIGHT,

  TAM_MAX
};


extern int xbox_prev_state[TAM_MAX];
extern int xbox[TAM_MAX];

void xbox_input();
int xbox_just_released(int botao);
int xbox_holding(int botao);
int xbox_just_pressed(int botao);
int xbox_just_pressed_any_button();


#endif // XBOX_H_INCLUDED
