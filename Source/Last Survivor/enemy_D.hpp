#ifndef ENEMY_D_HPP_INCLUDED
#define ENEMY_D_HPP_INCLUDED

#include "init.hpp"
#include "enemy.hpp"

class Enemy_D : public Enemy
{
   public:
     Animation* teleport;
     int timer_teleport;
     int to_next_teleport;
     float teta;
     float vel_angular;

     Enemy_D();
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

     void Destroy()
     {
       delete anim;
       delete teleport;
     }
};

#endif // ENEMY_D_HPP_INCLUDED
