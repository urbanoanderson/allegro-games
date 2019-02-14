#ifndef POWERUP_HPP_INCLUDED
#define POWERUP_HPP_INCLUDED

#include "spaceship.hpp"
#include "shield.hpp"

class Power_up : public GameObject
{
  public:

   float teta;
   int tempo_espera;
   int tempo_marcado;

   int cor[2];

   string txt;

   Power_up();
   void Reset();
   void Update(Spaceship* ship, Shield* barreira);
   void Draw();
   void Destroy()
   { delete anim; }
};



#endif // POWERUP_H_INCLUDED
