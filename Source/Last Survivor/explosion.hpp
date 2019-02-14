#ifndef EXPLOSION_HPP_INCLUDED
#define EXPLOSION_HPP_INCLUDED

#include "init.hpp"
#include "gameobject.hpp"

class Explosion : public GameObject
{
   public:
     Explosion(float pos_x, float pos_y, int explID);
     void Update();
     void Draw();
     void Destroy() { delete anim; }
};

#endif // EXPLOSION_HPP_INCLUDED
