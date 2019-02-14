#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "init.h"

class Animation
{
  private:
    ALLEGRO_BITMAP* img;
    int qtdframes;
    int curframe;
    double curtime;
    double switchtime;
    int frame_w;
    int frame_h;
    bool loop;
    bool finish;

  public:
    Animation() { }
    void Initialize(ALLEGRO_BITMAP* img, int qtdframes, double switchtime, bool loop);
    void Reset();
    void Update();
    void Draw(float x, float y, float xScale, float yScale, float angle, ALLEGRO_COLOR tint);
    void Draw(float x, float y);
    void Draw_Flip(float x, float y, int flip);
    int Width() { return frame_w; }
    int Height() { return frame_h; }
    bool Finish() { return finish; }
    ~Animation() { }
};

#endif
