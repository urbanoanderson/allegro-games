#ifndef SHOT_HPP_INCLUDED
#define SHOT_HPP_INCLUDED

#include "gameobject.hpp"

class Shot : public GameObject
{
  public:
    Shot(float pos_x, float pos_y, int ID);
    void Update();
    void Draw();
    void Collide(int ObjID) {}
    void Destroy() { delete anim; }
};

#endif // SHOT_HPP_INCLUDED
