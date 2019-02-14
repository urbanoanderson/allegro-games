#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "init.h"

typedef struct animation
{
     BITMAP* image;
     BITMAP* imageaux;
     int numframes;
     int switchtime;
     int frame_w;
     int frame_h;

     int curframe;
     int curtime;

     int loop;
     int finish;
}Animation;

Animation* Create_Animation(BITMAP* image, int numframes, int switchtime, int loop);
void Update_Animation(Animation* a);
void Draw_Animation(Animation* a, BITMAP* effect, BITMAP* buffer, int pos_x, int pos_y);
void Draw_Animation_H_Flip(Animation* a, BITMAP* effect, BITMAP* buffer, int pos_x, int pos_y);
void Draw_Animation_90_degree(Animation* a, BITMAP* effect, BITMAP* buffer, int pos_x, int pos_y, int sentido);
void Destroy_Animation(Animation* a);

#endif // ANIMATION_H_INCLUDED
