#ifndef BOMBA_HPP_INCLUDED
#define BOMBA_HPP_INCLUDED

#include "gameobject.hpp"

class Bomba : public GameObject
{
  public:
    Bomba(float pos_x, float pos_y, int ID);
    void Update();
    void Draw();
    void Collide(int ObjID) {}
    void Destroy() { delete anim; }
};

#endif // BOMBA_HPP_INCLUDED
