#ifndef ANIMATION_HPP_INCLUDED
#define ANIMATION_HPP_INCLUDED

#include "init.hpp"

class Animation
{
  public:

  BITMAP* img;
  BITMAP* trans_img; //auxiliar para efeito de transparência

  int init_frame;
  int loopframe;
  int qtdframes;
  int curframe;

  int curtime;
  int switchtime;

  int frame_w;
  int frame_h;

  bool loop;
  bool finish;

  void Reset();
  Animation(BITMAP* img, int qtdframes, int switchtime, int loopframe, bool loop);
  void Update();
  void Draw(BITMAP* buffer, int pos_x, int pos_y);
  void Draw_ex(BITMAP* buffer, int pos_x, int pos_y, fixed angle, int trans_level);
  ~Animation() { destroy_bitmap(trans_img); }
};

#endif // ANIMATION_HPP_INCLUDED
