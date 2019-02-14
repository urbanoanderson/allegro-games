#include "button.h"

Button* create_button(BITMAP* image, BITMAP* h_image, SAMPLE* h_effect, int x, int y, int hx, int hy)
{
   Button* b = (Button*) malloc(sizeof(Button));

   b->img = image;
   b->h_img = h_image;
   b->h_click = h_effect;
   b->pos_x = x;
   b->pos_y = y;
   b->hx = hx;
   b->hy = hy;
   b->highlightON = FALSE;
   b->ativado = FALSE;
   b->bip = 0;

   return b;
}

bool is_on_button(Button* b)
{
    if(mouse_x > b->pos_x && mouse_x < b->pos_x + b->img->w
    && mouse_y > b->pos_y && mouse_y < b->pos_y + b->img->h
    && getpixel(b->img, mouse_x - b->pos_x, mouse_y - b->pos_y) != makecol(255,0,255))
    return true;

    return false;
}

void button_input(Button* b)
{
  if(mouse_x > b->pos_x && mouse_x < b->pos_x + b->img->w
  && mouse_y > b->pos_y && mouse_y < b->pos_y + b->img->h
  && getpixel(b->img, mouse_x - b->pos_x, mouse_y - b->pos_y) != makecol(255,0,255))
  {
    if(!b->highlightON)
        b->tempoEmCima = milisegundos;

    b->highlightON = TRUE;
    b->bip++;

    if(b->bip == 1 && b->h_click != NULL)
     play_sample(b->h_click, volume, 128, 1000, FALSE);

    if(Clicou(1))
    {
       b->ativado = !b->ativado;
    }

  }
  else
  {
    b->tempoEmCima = milisegundos;
    b->highlightON = FALSE;
    b->bip = 0;
  }
}


void button_draw(Button* b, BITMAP* buffer)
{
    draw_sprite(buffer,  b->img, b->pos_x,  b->pos_y);

    if(b->highlightON && b->h_img != NULL)
       draw_sprite(buffer,  b->h_img, b->hx,  b->hy);
}


void destroy_button(Button* b)
{
    free(b);
}
