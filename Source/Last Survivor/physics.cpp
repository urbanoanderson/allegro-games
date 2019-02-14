#include "physics.hpp"

double rads(double graus)
{
    return (graus * 3.14159265) / 180.0;
}

fixed GRAUS_ALLEGRO(double graus)
{
  return ftofix(graus * (256.0 / 360.0));
}

int max(int a, int b)
{
  if(a >= b)
   return a;
  else
   return b;
}

int min(int a, int b)
{
  if(a <= b)
   return a;
  else
   return b;
}

int pixel_perfect_colision(BITMAP* obj1, int x1, int y1, BITMAP* obj2, int x2, int y2)
{
   int i, j;
   int colisao = FALSE;

   //Se os retângulos estiverem se intersectando
   if(!( (x1 > x2 + obj2->w) || (y1 > y2 + obj2->h) || (x2 > x1 + obj1->w) || (y2 > y1 + obj1->h) ))
   {
     int cima = max(y1, y2);
	 int baixo = min(y1 + obj1->h, y2 + obj2->h);
	 int esquerda = max(x1, x2);
     int direita = min(x1 + obj1->w, x2 + obj2->w);

	 for(i = cima; i < baixo && !colisao; i++)
	 {
		for(j = esquerda; j < direita && !colisao; j++)
		{
		  if(getpixel(obj1, j-x1, i-y1) != makecol(255,0,255) && getpixel(obj2, j-x2, i-y2) != makecol(255,0,255))
           colisao = TRUE;
		}
	 }
   }

   return colisao;
}


///COLISÂO ENTRE DUAS ANIMAÇÕES
int collision_between_animations(Animation* obj1, int x1, int y1, Animation* obj2, int x2, int y2)
{
    BITMAP* img1 = create_bitmap(obj1->frame_w, obj1->frame_h);
    BITMAP* img2 = create_bitmap(obj2->frame_w, obj2->frame_h);

    blit(obj1->img, img1, (obj1->curframe * obj1->frame_w), 0, 0, 0, obj1->frame_w, obj1->frame_h);
    blit(obj2->img, img2, (obj2->curframe * obj2->frame_w), 0, 0, 0, obj2->frame_w, obj2->frame_h);

    int colisao = pixel_perfect_colision(img1, x1, y1, img2, x2, y2);
    destroy_bitmap(img1);
    destroy_bitmap(img2);

    return colisao;
}

///COLISÃO ENTRE UM BITMAP E UMA ANIMAÇÃO
int collision_against_animation(Animation* obj1, int x1, int y1, BITMAP* img2, int x2, int y2)
{
    BITMAP* img1 = create_bitmap(obj1->frame_w, obj1->frame_h);
    blit(obj1->img, img1, (obj1->curframe * obj1->frame_w), 0, 0, 0, obj1->frame_w, obj1->frame_h);

    int colisao = pixel_perfect_colision(img1, x1, y1, img2, x2, y2);
    destroy_bitmap(img1);

    return colisao;
}


int bounding_box_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    if( (x1 > x2 + w2) || (y1 > y2 + h2) || (x2 > x1 + w1) || (y2 > y1 + h1) )
     return FALSE;
    else
     return TRUE;
}
