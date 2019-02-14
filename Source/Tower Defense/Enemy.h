#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "init.h"
#include "Animation.h"
#include "Stage.h"

typedef struct enemy
{
   Animation* anim;
   BITMAP* img_veneno;
   BITMAP* img_slow;
   int ID;

   int slow;
   int envenenado;

   float vida;
   float vidamax;

   int dir;
   float x;
   float y;
   float speed;
   float velaparente;
   int timer_movimento;

   int ativo;
}Enemy;

Enemy* Create_Enemy(int ID, Stage* s);
void Update_Enemy(Enemy* e, Stage* s);
void Draw_Enemy(Enemy* e, BITMAP* buffer);
void Destroy_Enemy(Enemy* e);

#endif // ENEMY_H_INCLUDED
