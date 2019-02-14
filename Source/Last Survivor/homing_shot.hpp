#ifndef HOMING_SHOT_HPP_INCLUDED
#define HOMING_SHOT_HPP_INCLUDED

#include "gameobject.hpp"

extern int qtd_tiros_E;

class Homing_Shot : public GameObject
{
  public:
   GameObject* target;
   float target_x;
   float target_y;
   float accel_x;

   Homing_Shot(GameObject* target, float pos_x, float pos_y, int ID);
   void Update();
   void Draw();
   void Collide(int ObjID) {}
   void Destroy() { delete anim; qtd_tiros_E--; if(qtd_tiros_E == 0) stop_sample(c->FX_tiro_E); }
};

#endif // HOMING_SHOT_HPP_INCLUDED
