#include "shield.hpp"


Shield::Shield(Spaceship* user_ship)
{
  anim = new Animation(c->game_barreira, 4, 50, 0, true);
  ID = SHIELD;
  this->user_ship = user_ship;
  max_points = 1000;
  points = max_points;
  consumo = 4;
  recarga = 1;
  collidable = false;
  ativo = true;
}

void Shield::Input()
{
   if(user_ship->pode_barreira)
   {
    if((key[KEY_SPACE] || xbox[BUTTON_RB]) && points > 0 && !user_ship->morreu)
   {
       if(just_pressed(KEY_SPACE) || xbox_just_pressed(BUTTON_X))
        play_sample(c->FX_barreira, vol_SFX, 128, 1000, TRUE);
       this->collidable = true;
       user_ship->collidable = false;
   }
   else
   {
     stop_sample(c->FX_barreira);
     this->collidable = false;
     user_ship->collidable = true;
   }
   }
}

void Shield::Update()
{
  if(this->collidable)
  {
    anim->Update();

    points -= consumo;
    if(points <= 0)
    {
      points = -70;
      collidable = false;
      user_ship->collidable = true;
    }
  }
  else
  {
   points += recarga;
   if(points >= max_points)
    points = max_points;
  }

  pos_x = (user_ship->pos_x + user_ship->anim->frame_w/2 - anim->frame_w/2);
  pos_y = (user_ship->pos_y + user_ship->anim->frame_h/2 - anim->frame_h/2 + 3);
}

void Shield::Draw()
{
    if(collidable)
     anim->Draw_ex(buffer, pos_x, pos_y, itofix(0), 128);
}

int Shield::CheckCollision(GameObject* tiro)
{
  if(this->collidable && tiro->collidable && tiro->ID >= SHOT_ENEMY_A && tiro->ID < TOTAL_ENEMY_SHOT_TYPES )
  {
    if(collision_between_animations(this->anim, (int)pos_x, (int)pos_y, tiro->anim, (int)tiro->pos_x, (int)tiro->pos_y))
    {
       tiro->collidable = false;

       if(tiro->ID != SHOT_ENEMY_F)
        tiro->ativo = false;

       return true;
    }
  }

  return false;
}
