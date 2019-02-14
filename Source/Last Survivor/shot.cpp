#include "shot.hpp"

Shot::Shot(float pos_x, float pos_y, int ID)
{
  this->pos_x = pos_x;
  this->pos_y = pos_y;
  this->ID = ID;
  ativo = true;
  collidable = true;

  if(ID == SHOT_LV0)
  {
    this->anim = new Animation(c->game_shot_lv0, 1, 1000, 0, true);
    play_sample(c->FX_tiro_lv0, vol_SFX, 128, 1000, FALSE);
    speed_x = 0;
    speed_y = 17.0;
    dir_y = UP;
  }

  else if(ID == SHOT_LV1)
  {
    this->anim = new Animation(c->game_shot_lv1, 2, 100, 0, true);
    play_sample(c->FX_tiro_lv1, vol_SFX, 128, 1000, FALSE);
    speed_x = 0;
    speed_y = 18.0;
    dir_y = UP;
  }

  else if(ID == SHOT_LV2)
  {
    this->anim = new Animation(c->game_shot_lv2, 3, 100, 0, true);
    play_sample(c->FX_tiro_lv2, vol_SFX, 128, 1000, FALSE);
    speed_x = 0;
    speed_y = 20.0;
    dir_y = UP;
  }

  else if(ID == SHOT_ENEMY_A)
  {
    this->anim = new Animation(c->game_enemyA_tiro, 1, 100, 0, true);
    play_sample(c->FX_tiro_A, vol_SFX, 128, 1000, FALSE);
    speed_x = 0;
    speed_y = 18.5;
    dir_y = DOWN;
  }

  else if(ID == SHOT_ENEMY_B)
  {
    this->anim = new Animation(c->game_enemyB_tiro, 4, 50, 0, true);
    play_sample(c->FX_tiro_lv0, vol_SFX, 128, 1000, FALSE);
    speed_x = 0;
    speed_y = 15.0;
    dir_y = DOWN;
  }

  else if(ID == SHOT_ENEMY_C)
  {
    this->anim = new Animation(c->game_enemyC_tiro, 1, 100, 0, true);
    play_sample(c->FX_tiro_lv0, vol_SFX, 128, 1000, FALSE);
    speed_x = 0;
    speed_y = 17.0;
    dir_y = DOWN;
  }

  else if(ID == SHOT_ENEMY_D)
  {
    this->anim = new Animation(c->game_enemyD_tiro, 1, 70, 0, true);
    play_sample(c->FX_tiro_lv0, vol_SFX, 128, 1000, FALSE);
    speed_x = 0;
    speed_y = 17.0;
    dir_y = DOWN;
  }
}

void Shot::Update()
{
   pos_y += speed_y * dir_y;

   if(pos_y > SCREEN_H  || pos_y + anim->frame_h < 0)
    ativo = false;
}

void Shot::Draw()
{
   anim->Draw(buffer, pos_x, pos_y);
}
