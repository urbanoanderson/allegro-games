#include "enemy_E.hpp"

Enemy_E::Enemy_E()
{
  anim = new Animation(c->game_enemyE, 1, 1000, 0, true);
  ID = ENEMY_E;
  collidable = true;
  ativo = true;
  vidas = 3;
  timer_tiro = milisegundos;
  to_next_shot = 500 + rand()%3000;

  pos_x = rand() % (SCREEN_W - anim->frame_w);
  pos_y = rand() % (2*SCREEN_H/5);

  accel_y = 0.08;
  speed_y = 0.0;

  if(rand() % 2 == 0)
   dir_y = UP;
  else
   dir_y = DOWN;
}


void Enemy_E::Movimento()
{
   speed_y += accel_y * dir_y;

   if(abs(speed_y) > 2.0)
    { dir_y *= -1; }

   pos_y += speed_y;
}

void Enemy_E::Update()
{
  Movimento();

  if(!collidable && milisegundos - timer_imortal >= 70)
    collidable = true;

}

void Enemy_E::Draw()
{
   anim->Draw(buffer, (int)pos_x, (int)pos_y);

  if(!collidable)
  {
    set_trans_blender(255, 255, 255, 180);
    draw_trans_sprite(buffer, c->game_enemyE_dano, (int)pos_x, (int)pos_y);
  }
}
