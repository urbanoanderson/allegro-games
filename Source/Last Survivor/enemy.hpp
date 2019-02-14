#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include "init.hpp"
#include "gameobject.hpp"

class Enemy : public GameObject
{
   public:
     int vidas;
     int timer_imortal;
     int to_finish_imortal;
     int timer_tiro;
     int to_next_shot;

     Enemy() {}
     virtual void Movimento() {}
     virtual void Update() { }
     virtual void Draw() { }
     virtual void Destroy() { }

     int CheckCollision(GameObject* tiro);
};

#endif //ENEMY_HPP_INCLUDED
