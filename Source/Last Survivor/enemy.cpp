#include "enemy.hpp"

///COLISÃO
int Enemy::CheckCollision(GameObject* tiro)
{
  if(tiro->ID >= SHOT_LV0 && tiro->ID <= SHOT_LV2 )
  {
    if(this->collidable && collision_between_animations(this->anim, (int)pos_x, (int)pos_y, tiro->anim, (int)tiro->pos_x, (int)tiro->pos_y))
    {
       to_finish_imortal = 70;

       if(tiro->ID == SHOT_LV0)
        { vidas -= 1; tiro->ativo = false; }
       else if(tiro->ID == SHOT_LV1)
        { vidas -= 2; tiro->ativo = false; }
       else if(tiro->ID == SHOT_LV2)
        { vidas -= 3; to_finish_imortal = 100; }

       if(vidas <= 0)
        ativo = false;

       return true;
    }
  }

  return false;
}
