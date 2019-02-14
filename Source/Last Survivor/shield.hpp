#ifndef SHIELD_HPP_INCLUDED
#define SHIELD_HPP_INCLUDED

#include "init.hpp"
#include "spaceship.hpp"

class Shield : public GameObject
{
  public:
   Spaceship* user_ship;
   int max_points;
   int points;
   int consumo;
   int recarga;

   Shield(Spaceship* user_ship);
   void Input();
   void Update();
   void Draw();
   int CheckCollision(GameObject* obj);

   void Destroy()
   {
     delete anim;
   }
};

#endif // SHIELD_HPP_INCLUDED
