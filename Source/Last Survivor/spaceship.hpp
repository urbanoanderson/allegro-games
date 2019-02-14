#ifndef SPACESHIP_HPP_INCLUDED
#define SPACESHIP_HPP_INCLUDED

#include "init.hpp"
#include "gameobject.hpp"
#include "shot.hpp"

class Spaceship : public GameObject
{
  public:
   Animation* charging1;
   Animation* charging2;
   list<GameObject*>* lista_tiros;

   int vidas;
   bool morreu;
   bool imortal;
   bool pode_atirar;
   bool pode_barreira;
   int timer_imortal;

   int charge;
   int timer_charge;
   int qtd_tiros;
   int max_tiros;

   Spaceship(list<GameObject*>* lista_tiros, int flag);
   void Input();
   void Update();
   void Draw();
   int CheckCollision(GameObject* obj);
   void Reset_Stats();

   void Destroy()
   {
     delete anim;
     delete charging1;
     delete charging2;
   }
};

#endif // SPACESHIP_HPP_INCLUDED
