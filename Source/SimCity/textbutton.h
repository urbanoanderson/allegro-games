#ifndef TEXTBUTTON_H_INCLUDED
#define TEXTBUTTON_H_INCLUDED

#include "init.h"

typedef struct textbutton
{

  FONT* normal;
  FONT* high;
  FONT* active;

  char texto[20];

  int x;
  int y;

  bool highlightON;
  bool ativado;

  int bip;

}TextButton;


TextButton* create_textbutton(const char texto[20], FONT* normal, FONT* high, FONT* active, int x, int y);
void textbutton_input(TextButton* b);
void textbutton_draw(TextButton* b, BITMAP* buffer);
void destroy_textbutton(TextButton* b);


#endif
