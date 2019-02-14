#include "enemy_C.hpp"

Enemy_C::Enemy_C()
{
  anim = new Animation(c->game_enemyC, 1, 1000, 0, true);
  ID = ENEMY_C;
  collidable = true;
  ativo = true;
  vidas = 2;

  pos_y = 0;
  dir_y = DOWN;

  if(rand()%2 == 0)
   speed_x = 6;
  else
   speed_x = 7;

  if(rand()%2 == 0)
   speed_y = 1.3;
  else
    speed_y = 2.0;

  timer_tiro = milisegundos;
  to_next_shot = 350;

  if(rand() % 2 == 0) {
   dir_x = RIGHT; pos_x = -anim->frame_w; }
  else{
   dir_x = LEFT; pos_x = SCREEN_W; }
}


void Enemy_C::Movimento()
{
   pos_x += speed_x * dir_x;
   pos_y += speed_y * dir_y;

   if(pos_x > SCREEN_W || pos_x + anim->frame_w < 0)
    ativo = false;
}

void Enemy_C::Update()
{
  Movimento();

  if(!collidable && milisegundos - timer_imortal >= 70)
    collidable = true;
}

void Enemy_C::Draw()
{
   anim->Draw(buffer, (int)pos_x, (int)pos_y);

  if(!collidable)
  {
    set_trans_blender(255, 255, 255, 180);
    draw_trans_sprite(buffer, c->game_enemyC_dano, (int)pos_x, (int)pos_y);
  }
}
