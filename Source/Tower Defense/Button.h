#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "init.h"

typedef struct button
{
  BITMAP* img;
  BITMAP* h_img;

  int pos_x;
  int pos_y;

  int highlightON;
  int ativado;

  int bip;
}Button;


Button* Create_Button(BITMAP* image, BITMAP* h_image, int x, int y);
void Update_Button(Button* b);
void Draw_Button(Button* b, BITMAP* buffer);
void Destroy_Button(Button* b);

#endif // BUTTON_H_INCLUDED
