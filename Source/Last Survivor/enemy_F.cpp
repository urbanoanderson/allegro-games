#include "enemy_F.hpp"

Enemy_F::Enemy_F()
{
  anim = new Animation(c->game_enemyF, 1, 1000, 0, true);
  ID = ENEMY_F;
  collidable = true;
  ativo = true;
  vidas = 8;
  timer_tiro = milisegundos;
  to_next_shot = 4000;

  timer_warning = milisegundos;
  to_next_warning = 800;
  warning = false;
  timer_movement = milisegundos;

  pos_x = rand() % (SCREEN_W - anim->frame_w);
  pos_y = -anim->frame_h;

  speed_y = 2.0;
  teta = 0.0;

  if(rand() % 2 == 0)
   dir_x = LEFT;
  else
   dir_x = RIGHT;
}


void Enemy_F::Movimento()
{
   if(milisegundos - timer_movement >= 9)
   { pos_y += speed_y; timer_movement = milisegundos; }
}

void Enemy_F::Update()
{
  Movimento();
  teta += 0.5 * dir_x;

  if(!warning && milisegundos - timer_warning >= to_next_warning)
  {
    warning = true;
    play_sample(c->FX_warning_F, vol_SFX, 128, 1000, FALSE);
  }

  else if(warning && milisegundos - timer_warning >= to_next_warning + 150)
  {
    warning = false;
    timer_warning = milisegundos;
    to_next_warning -= 140;
  }

  if(!collidable && (milisegundos - timer_imortal >= to_finish_imortal))
    collidable = true;
}

void Enemy_F::Draw()
{
  anim->Draw_ex(buffer, (int)pos_x, (int)pos_y, ftofix(teta), 255);

  if(warning)
   rotate_sprite_trans(buffer, c->game_enemyF_warning, (int)pos_x, (int)pos_y, ftofix(teta));

  if(!collidable)
  {
    set_trans_blender(255, 255, 255, 180);
    rotate_sprite_trans(buffer, c->game_enemyF_dano, (int)pos_x, (int)pos_y, ftofix(teta));
  }
}
