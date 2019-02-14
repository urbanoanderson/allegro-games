#ifndef ENEMY_C_HPP_INCLUDED
#define ENEMY_C_HPP_INCLUDED

#include "init.hpp"
#include "enemy.hpp"

class Enemy_C : public Enemy
{
   public:
     Enemy_C();
     void Movimento();
     void Update();
     void Draw();

     int CheckCollision(GameObject* obj)
     {
        if(Enemy::CheckCollision(obj))
        {
          collidable = false;
          timer_imortal = milisegundos;
        }
     }

     void Destroy() { delete anim; }
};

#endif // ENEMY_C_HPP_INCLUDED
