#include "animation.hpp"

///CREATE
Animation::Animation(BITMAP* img, int qtdframes, int switchtime, int loopframe, bool loop)
{
  this->img = img;
  this->qtdframes = qtdframes;
  this->switchtime = switchtime;
  this->loopframe = loopframe;
  this->loop = loop;
  this->finish = false;

  this->curframe = 0;
  this->curtime = milisegundos;
  this->frame_w = this->img->w / this->qtdframes;
  this->frame_h = this->img->h;

  this->trans_img = create_bitmap(this->frame_w, this->frame_h);
}


///UPDATE
void Animation::Update()
{
   if(!finish && (milisegundos - curtime >= switchtime))
   {
     curframe++;
     curtime = milisegundos;

     if(curframe == qtdframes)
     {
         if(loop == true)
          curframe = loopframe;
         else
          finish = true;
     }
   }
}

void Animation::Reset()
{
   curframe = 0;
   finish = false;
}

///DRAW
void Animation::Draw(BITMAP* buffer, int pos_x, int pos_y)
{
  if(!finish)
   masked_blit(img, buffer, curframe * frame_w, 0, pos_x, pos_y, frame_w, frame_h);
}

void Animation::Draw_ex(BITMAP* buffer, int pos_x, int pos_y, fixed angle, int trans_level)
{
  if(!finish)
  {
     set_trans_blender(255,255,255, trans_level);
     blit(img, trans_img, curframe * frame_w, 0, 0, 0, frame_w, frame_h);
     rotate_sprite_trans(buffer, trans_img, pos_x, pos_y, angle);
  }
}
