#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "init.h"

typedef struct button
{
  BITMAP* img;
  BITMAP* h_img;
  SAMPLE* h_click;

  int tempoEmCima;

  int pos_x;
  int pos_y;

  int hx;
  int hy;

  int highlightON;
  int ativado;

  int bip;
}Button;


Button* create_button(BITMAP* image, BITMAP* h_image, SAMPLE* h_effect, int x, int y, int hx, int hy);
void button_input(Button* b);
void button_draw(Button* b, BITMAP* buffer);
void destroy_button(Button* b);
bool is_on_button(Button* b);


#endif // BUTTON_H_INCLUDED
