#ifndef GAMEOBJECT_HPP_INCLUDED
#define GAMEOBJECT_HPP_INCLUDED

#include "init.hpp"
#include "animation.hpp"
#include "physics.hpp"

class GameObject
{
  public:
   Animation* anim;

   float pos_x;
   float pos_y;
   float speed_x;
   float speed_y;
   int dir_x;
   int dir_y;

   bool collidable;
   bool ativo;

   int ID;

   GameObject() {}
   virtual void Update() {}
   virtual void Draw() {}
   virtual void Destroy() {}
   virtual int CheckCollision(GameObject* obj) { return 0; }
};

#endif // GAMEOBJECT_HPP_INCLUDED
