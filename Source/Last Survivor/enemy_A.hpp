#ifndef ENEMY_A_HPP_INCLUDED
#define ENEMY_A_HPP_INCLUDED

#include "init.hpp"
#include "enemy.hpp"

class Enemy_A : public Enemy
{
   public:
     Enemy_A();
     void Movimento();
     void Update();
     void Draw();

     int CheckCollision(GameObject* tiro)
     { return Enemy::CheckCollision(tiro); }

     void Destroy()
     {
       delete anim;
     }
};

#endif // ENEMY_A_HPP_INCLUDED
