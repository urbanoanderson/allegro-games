#include "Animation.h"

Animation* Create_Animation(BITMAP* image, int numframes, int switchtime, int loop)
{
   Animation* a = (Animation*) malloc(sizeof(Animation));

   a->image = image;
   a->numframes = numframes;
   a->switchtime = switchtime;
   a->loop = loop;
   a->finish = FALSE;
   a->curframe = 0;
   a->curtime = gametime;
   a->frame_w = image->w / numframes;
   a->frame_h = image->h;
   a->imageaux = create_bitmap(a->frame_w, a->frame_h);

   return a;
}

void Update_Animation(Animation* a)
{
   if(!a->finish)
   {
      if(gametime - a->curtime >= a->switchtime)
      {
          a->curframe++;
          a->curtime = gametime;

          if(a->curframe >= a->numframes)
          {
             if(a->loop == TRUE)
              a->curframe = 0;
            else
              a->finish = TRUE;
          }
      }
   }
}

void Draw_Animation(Animation* a, BITMAP* effect, BITMAP* buffer, int pos_x, int pos_y)
{
   if(!a->finish)
   {
    masked_blit(a->image, buffer, a->curframe * a->frame_w, 0, pos_x, pos_y, a->frame_w, a->image->h);

     //Aplica efeito
     if(effect != NULL)
     {
        blit(effect, a->imageaux, a->curframe * a->frame_w, 0, 0, 0, a->frame_w, a->image->h);
        draw_trans_sprite(buffer, a->imageaux, pos_x, pos_y);
     }

   }
}

void Draw_Animation_H_Flip(Animation* a, BITMAP* effect, BITMAP* buffer, int pos_x, int pos_y)
{
   if(!a->finish)
   {
     blit(a->image, a->imageaux, a->curframe * a->frame_w, 0, 0, 0, a->frame_w, a->image->h);
     draw_sprite_h_flip(buffer, a->imageaux, pos_x, pos_y);

     //Aplica efeito
     if(effect != NULL)
     {
        blit(effect, a->imageaux, a->curframe * a->frame_w, 0, 0, 0, a->frame_w, a->image->h);
        draw_sprite_ex(buffer, a->imageaux, pos_x, pos_y, DRAW_SPRITE_TRANS, DRAW_SPRITE_H_FLIP);
     }
   }
}

void Draw_Animation_90_degree(Animation* a, BITMAP* effect, BITMAP* buffer, int pos_x, int pos_y, int sentido)
{
   if(!a->finish)
   {
     blit(a->image, a->imageaux, a->curframe * a->frame_w, 0, 0, 0, a->frame_w, a->image->h);
     rotate_sprite(buffer, a->imageaux, pos_x, pos_y, itofix(sentido * 64));
   }

   //Aplica efeito
   if(effect != NULL)
   {
     blit(effect, a->imageaux, a->curframe * a->frame_w, 0, 0, 0, a->frame_w, a->image->h);
     rotate_sprite_trans(buffer, a->imageaux, pos_x, pos_y, itofix(sentido * 64));
   }
}

void Destroy_Animation(Animation* a)
{
    destroy_bitmap(a->imageaux);
    free(a);
}


