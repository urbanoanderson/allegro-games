#ifndef ENEMY_B_HPP_INCLUDED
#define ENEMY_B_HPP_INCLUDED

#include "init.hpp"
#include "enemy.hpp"

class Enemy_B : public Enemy
{
   public:
     float teta;
     float vel_angular;

     Enemy_B();
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

#endif // ENEMY_B_HPP_INCLUDED
