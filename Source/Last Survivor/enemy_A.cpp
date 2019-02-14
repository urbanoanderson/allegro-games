#include "enemy_A.hpp"

Enemy_A::Enemy_A()
{
  anim = new Animation(c->game_enemyA, 1, 1000, 0, true);
  ID = ENEMY_A;
  collidable = true;
  ativo = true;
  vidas = 1;
  timer_tiro = milisegundos;
  to_next_shot = rand()%2500;

  pos_x = rand() % (SCREEN_W - anim->frame_w);
  pos_y = rand() % (SCREEN_H/3 - anim->frame_h);
  speed_x = 6.5;
  speed_y = 3.5;

  if(rand()%2 == 0)
    dir_x = LEFT;
  else
    dir_x = RIGHT;

  if(rand()%2 == 0)
    dir_y = UP;
  else
    dir_y = DOWN;
}


void Enemy_A::Movimento()
{
   pos_x += speed_x * dir_x;
   pos_y += speed_y * dir_y;

   if(pos_x + anim->frame_w > SCREEN_W || pos_x < 0)
     dir_x *= -1;
   if(pos_y > SCREEN_H/3 - anim->frame_h || pos_y < 0)
     dir_y *= -1;
}

void Enemy_A::Update()
{
  Movimento();
}

void Enemy_A::Draw()
{
  anim->Draw(buffer, (int)pos_x, (int)pos_y);
}
