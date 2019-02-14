#include "homing_shot.hpp"

int qtd_tiros_E;

Homing_Shot::Homing_Shot(GameObject* target, float pos_x, float pos_y, int ID)
{
  this->target = target;
  this->pos_x = pos_x;
  this->pos_y = pos_y;
  this->ID = ID;
  ativo = true;
  collidable = true;

  if(ID == SHOT_ENEMY_E)
  {
    this->anim = new Animation(c->game_enemyE_tiro, 4, 75, 0, true);
    play_sample(c->FX_tiro_E, vol_SFX, 128, 1000, TRUE);
    accel_x = 0.02;
    speed_x = 0.0;
    dir_x = NONE;
    speed_y = 2.0;
    dir_y = DOWN;
  }
}

void Homing_Shot::Update()
{
   anim->Update();

   target_x = target->pos_x + target->anim->frame_w/2;
   target_y = target->pos_y + target->anim->frame_h/2;

   if(target_x > pos_x + anim->frame_w/2)
     dir_x = RIGHT;
   else if(target_x < pos_x + anim->frame_w/2)
     dir_x = LEFT;
   else
     dir_x = NONE;

   speed_x += accel_x * dir_x;
   if(abs(speed_x) >= 2.0)
    speed_x = 2.0 * dir_x;

   pos_x += speed_x;
   pos_y += speed_y * dir_y;

   if(pos_y > SCREEN_H  || pos_y + anim->frame_h < 0)
    ativo = false;
}

void Homing_Shot::Draw()
{
   anim->Draw(buffer, pos_x, pos_y);
}
