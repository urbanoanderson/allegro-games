#include "enemy_D.hpp"

Enemy_D::Enemy_D()
{
  anim = new Animation(c->game_enemyD, 1, 1000, 0, true);
  teleport = new Animation(c->game_teleport, 3, 75, 0, false);
  ID = ENEMY_D;
  collidable = true;
  ativo = true;
  vidas = 2;
  timer_tiro = milisegundos;
  to_next_shot = rand()%3500;

  teta = 0.0;
  vel_angular = 6.0;

  if(rand() % 2 == 0)
   dir_x = 1;
  else
   dir_x = -1;

  pos_x = rand() % (SCREEN_W - anim->frame_w);
  pos_y = rand() % (SCREEN_H/4 + SCREEN_H/4);
  timer_teleport = milisegundos;
  to_next_teleport = 1000 + rand()%1000;
}


void Enemy_D::Movimento()
{
  if(milisegundos - timer_teleport >= to_next_teleport)
  {
   pos_x = rand() % (SCREEN_W - anim->frame_w);
   pos_y = rand() % (SCREEN_H/4 + SCREEN_H/4);
   timer_teleport = milisegundos;
   to_next_teleport = 1000 + rand()%1000;
   teleport->Reset();
  }
  else
  {
    teta += vel_angular * dir_x;
    pos_x = pos_x + 2*cos(rads(teta));
    pos_y = pos_y - 2*sin(rads(teta));
  }
}

void Enemy_D::Update()
{
  Movimento();
  teleport->Update();

  if(!collidable && milisegundos - timer_imortal >= 70)
    collidable = true;

}

void Enemy_D::Draw()
{
  anim->Draw(buffer, (int)pos_x, (int)pos_y);

  if(!collidable)
  {
    set_trans_blender(255, 255, 255, 180);
    draw_trans_sprite(buffer, c->game_enemyD_dano, (int)pos_x, (int)pos_y);
  }

  teleport->Draw(buffer, (int)pos_x+10, (int)pos_y-35);
}
