#ifndef ENEMY_E_HPP_INCLUDED
#define ENEMY_E_HPP_INCLUDED

#include "enemy.hpp"

class Enemy_E : public Enemy
{
   public:
     float accel_y;

     Enemy_E();
     void Movimento();
     void Update();
     void Draw();

     int CheckCollision(GameObject* obj)
     {
        if(Enemy::CheckCollision(obj))
        {
          collidable = false;
          timer_imortal = milisegundos;

          return 1;
        }

        return 0;
     }

     void Destroy()
     {
       delete anim;
     }
};

#endif // ENEMY_E_HPP_INCLUDED
