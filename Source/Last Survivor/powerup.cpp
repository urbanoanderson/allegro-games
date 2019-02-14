#include "powerup.hpp"


///-------------
///RESET
void Power_up::Reset()
{
  ID = PW_UP_SHIELD + rand() % 3;

  if(ID == PW_UP_LIFE)
  {
     anim = new Animation(c->game_powerup_extra_life, 1, 1000, 0, true);
     txt = (const string) "1UP";
  }
  else if(ID == PW_UP_SHIELD)
  {
     anim = new Animation(c->game_powerup_shield_recharge, 1, 1000, 0, true);
     txt = (const string) "SH";
  }

  else if(ID == PW_UP_SPEED)
  {
    anim = new Animation(c->game_powerup_speed_boost, 1, 1000, 0, true);
    txt = (const string) "SB";
  }

  pos_x = rand() % (SCREEN_W - anim->frame_w);
  pos_y = -anim->frame_h;
  teta = 0.0;
  ativo = true;
  collidable = true;
}


///-------------
///CREATE
Power_up::Power_up()
{
   this->Reset();
   this->cor[0] = makecol(255, 0, 0);
   this->cor[1] = makecol(255, 255, 0);
   ativo = false;
   tempo_marcado = milisegundos;
   tempo_espera = 20000 + rand() % 40001; // Seta tempo entre 20s e 1 min
}


///-------------
///UPDATE
void Power_up::Update(Spaceship* ship, Shield* barreira)
{
   if(ativo)
   {
     pos_y += 2.0;
     teta += 0.5;

     if((int)pos_y > SCREEN_H)
     {
       ativo = false;
       tempo_marcado = milisegundos;
       tempo_espera = 20000 + rand() % 40001; // Seta tempo entre 20s e 1 min
     }

     //Se a nave pegou o power_up
     else if(collision_between_animations(ship->anim, (int)ship->pos_x, (int)ship->pos_y, this->anim, (int)this->pos_x, (int)this->pos_y))
     {
       play_sample(c->FX_powerup, vol_SFX, 128, 1000, FALSE);
       ativo = false;
       tempo_marcado = milisegundos;
       tempo_espera = 20000 + rand() % 40001; // Seta tempo entre 20s e 1 min

       //O que cada power_up faz
       if(ID == PW_UP_LIFE && !ship->morreu && ship->vidas < 5)
        ship->vidas++;
       else if(ID == PW_UP_SHIELD && !ship->morreu)
        barreira->points = 1000;
       else if(ID == PW_UP_SPEED && !ship->morreu)
        ship->speed_x = 9.00;
     }
   }

   //Espera pra resetar o power_up
   else if(milisegundos - tempo_marcado >= tempo_espera)
    this->Reset();
}


///-------------
///DRAW
void Power_up::Draw()
{
   if(ativo)
   {
     anim->Draw_ex(buffer, (int)pos_x, (int)pos_y, ftofix(teta), 255);
     textprintf_ex(buffer, c->font_score, (int)pos_x + 13, (int)pos_y + 12, cor[(milisegundos/300)%2], -1, "%s", txt.c_str());
   }
}

