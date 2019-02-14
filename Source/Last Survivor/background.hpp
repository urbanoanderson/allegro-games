#ifndef BACKGROUND_HPP_INCLUDED
#define BACKGROUND_HPP_INCLUDED

#include "init.hpp"

class Background
{
  public:
   BITMAP* front;
   BITMAP* back;
   BITMAP* next;
   BITMAP* planet;

   float BG_y;
   int curtime;
   int to_next_BG;

   float planeta_x;
   float planeta_y;
   float teta;
   int dir_teta;
   int curtime_pl;
   int to_next_planet;

   Background();
   void Set_New_Planet();
   void Update();
   void Draw();
};

#endif // BACKGROUND_HPP_INCLUDED
