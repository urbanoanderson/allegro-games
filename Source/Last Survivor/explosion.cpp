#include "explosion.hpp"

Explosion::Explosion(float pos_x, float pos_y, int explID)
{
   ativo = true;
   collidable = false;
   ID = EXPLOSION;
   this->pos_x = pos_x;
   this->pos_y = pos_y;

   if(explID == EXPL_SMALL)
   {
     anim = new Animation(c->game_explosion_small, 8, 50, 0, false);
     play_sample(c->FX_explosao_small, vol_SFX, 128, 1000, false);
   }

   else if(explID == EXPL_MEDIUM)
   {
     anim = new Animation(c->game_explosion_medium, 10, 30, 0, false);
     play_sample(c->FX_explosao_medium, vol_SFX, 128, 1000, false);
   }

   else if(explID == EXPL_LARGE)
   {
     anim = new Animation(c->game_explosion_large, 4, 70, 0, false);
     play_sample(c->FX_explosao_large, vol_SFX, 128, 1000, false);
   }

   else if(explID == EXPL_SHIELD)
   {
     anim = new Animation(c->game_explosion_shield, 6, 50, 0, false);
     play_sample(c->FX_explosao_shield, vol_SFX, 128, 1000, false);
   }
}


void Explosion::Update()
{
  anim->Update();

  if(anim->finish)
   ativo = false;
}


void Explosion::Draw()
{
  anim->Draw(buffer, (int)pos_x, (int)pos_y);
}
