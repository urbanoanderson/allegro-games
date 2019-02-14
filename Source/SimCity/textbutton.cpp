#include "textbutton.h"

TextButton* create_textbutton(const char texto[20], FONT* normal, FONT* high, FONT* active, int x, int y)
{
   TextButton* b = (TextButton*) malloc(sizeof(TextButton));

   b->normal = normal;
   b->high = high;
   b->active = active;
   b->x = x;
   b->y = y;

   strcpy(b->texto, texto);

   b->highlightON = FALSE;
   b->ativado = FALSE;

   b->bip = 0;

   return b;
}

void textbutton_input(TextButton* b)
{
  if( (mouse_x >= b->x - text_length(b->normal, b->texto)/2 && mouse_x <= b->x + text_length(b->normal, b->texto)/2)
   && (mouse_y >= b->y && mouse_y <= b->y + text_height(b->normal) ) )
  {
     b->highlightON = true;
     b->bip++;

     if(b->bip == 1)
      play_sample(click, 255, 128, 1000, FALSE);

     if(mouse_b == 1)
     {
       mouse_b = 0;
       b->ativado = !b->ativado;
     }
  }

  else
  {
    b->highlightON = false;
    b->bip = 0;
  }

}


void textbutton_draw(TextButton* b, BITMAP* buffer)
{
    if(b->ativado)
     textprintf_centre_ex(buffer, b->active, b->x, b->y, makecol(150,150,150), -1, b->texto);
    else if(b->highlightON)
     textprintf_centre_ex(buffer, b->high, b->x, b->y, makecol(255, 0, 0), -1, b->texto);
    else
     textprintf_centre_ex(buffer, b->normal, b->x, b->y, makecol(255, 255, 255), -1, b->texto);
}


void destroy_textbutton(TextButton* b)
{
    free(b);
}
