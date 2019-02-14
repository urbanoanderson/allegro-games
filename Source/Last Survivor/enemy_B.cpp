#include "enemy_B.hpp"

Enemy_B::Enemy_B()
{
  anim = new Animation(c->game_enemyB, 1, 1000, 0, true);
  ID = ENEMY_B;
  collidable = true;
  ativo = true;
  vidas = 2;
  timer_tiro = milisegundos;
  to_next_shot = rand()%3500;

  pos_x = rand() % (SCREEN_W - anim->frame_w);
  pos_y = rand() % (SCREEN_H/4 + SCREEN_H/4);
  teta = 2.0;
  vel_angular = 3.0;

  if(rand() % 2 == 0)
   dir_x = 1;
  else
   dir_x = -1;
}


void Enemy_B::Movimento()
{
   teta += vel_angular * dir_x;

   pos_x = pos_x + 5 * cos(rads(teta));
   pos_y = pos_y - 2 * sin(rads(teta));
}

void Enemy_B::Update()
{
  Movimento();

  if(!collidable && milisegundos - timer_imortal >= 70)
    collidable = true;

}

void Enemy_B::Draw()
{
   anim->Draw(buffer, (int)pos_x, (int)pos_y);

  if(!collidable)
  {
    set_trans_blender(255, 255, 255, 180);
    draw_trans_sprite(buffer, c->game_enemyB_dano, (int)pos_x, (int)pos_y);
  }
}
