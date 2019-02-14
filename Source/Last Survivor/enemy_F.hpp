#ifndef ENEMY_F_HPP_INCLUDED
#define ENEMY_F_HPP_INCLUDED

#include "enemy.hpp"

class Enemy_F : public Enemy
{
   public:
     float teta;
     int timer_warning;
     int to_next_warning;
     bool warning;
     int timer_movement;

     Enemy_F();
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

#endif // ENEMY_F_HPP_INCLUDED
