#ifndef KEYBOARD_HPP_INCLUDED
#define KEYBOARD_HPP_INCLUDED

#include <allegro.h>

extern int prev_keystate[KEY_MAX];

void keyboard_input();
int is_pressed(int KEY);
int just_pressed(int KEY);
int just_pressed_any_key();
int just_released(int KEY);

#endif
