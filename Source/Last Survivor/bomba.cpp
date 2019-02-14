#include "bomba.hpp"

Bomba::Bomba(float pos_x, float pos_y, int ID)
{
  this->pos_x = pos_x;
  this->pos_y = pos_y;
  this->ID = ID;
  ativo = true;
  collidable = true;

  if(ID == SHOT_ENEMY_F)
  {
    this->anim = new Animation(c->game_enemyF_tiro, 5, 50, 0, false);
    play_sample(c->FX_explosao_large, vol_SFX, 128, 1000, FALSE);
  }
}

void Bomba::Update()
{
   anim->Update();

   if(anim->finish)
    ativo = false;
}

void Bomba::Draw()
{
   anim->Draw(buffer, pos_x, pos_y);
}
