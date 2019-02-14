#include "spaceship.hpp"

void Spaceship::Reset_Stats()
{
  speed_x = 6.5;
  max_tiros = 2;
}

///CREATE
Spaceship::Spaceship(list<GameObject*>* lista_tiros, int flag)
{
  anim = new Animation(c->game_nave, 1, 1000, 0, true);
  charging1 = new Animation(c->game_charging1, 6, 50, 0, true);
  charging2 = new Animation(c->game_charging2, 6, 50, 0, true);
  this->lista_tiros = lista_tiros;

   ID = SPACESHIP;
   pos_x = SCREEN_W/2 - anim->frame_w/2;
   pos_y = SCREEN_H - SCREEN_H/5;
   speed_x = 6.5;
   speed_y = 0;
   dir_x = NONE;
   dir_y = NONE;
   vidas = 3;
   morreu = false;
   imortal = false;
   ativo = true;
   collidable = true;

   qtd_tiros = 0;
   max_tiros = 2;

   if(flag == CHALLENGE1)
   { pode_atirar = false; pode_barreira = true; }
   else if(flag == CHALLENGE2)
   { pode_atirar = true; pode_barreira = false; }
   else if(flag == CHALLENGE3)
   { pode_atirar = false; pode_barreira = false; }
   else
   { pode_atirar = true; pode_barreira = true; }
}

///INPUT
void Spaceship::Input()
{
   ///MOVIMENTAÇÃO
   if((key[KEY_LEFT] || xbox[LSTICK_LEFT] || xbox[DPAD_LEFT]) && !morreu)
    { pos_x -= speed_x; dir_x = LEFT; }
   else if((key[KEY_RIGHT] || xbox[LSTICK_RIGHT] || xbox[DPAD_RIGHT]) && !morreu)
    { pos_x += speed_x; dir_x = RIGHT; }
   else
     dir_x = NONE;

   if((int)pos_x > SCREEN_W - (3*anim->frame_w/4))
    pos_x = (float)(SCREEN_W - 3*anim->frame_w/4);
   else if((int)pos_x < -anim->frame_w/4)
    pos_x = (float)(-anim->frame_w/4);

   ///ATIRANDO
   if(pode_atirar){
   if((just_released(KEY_A) || xbox_just_released(BUTTON_A)) && qtd_tiros < max_tiros && !morreu)
   {
     Shot* novo_tiro;

     if(charge == SHOT_LV0)
      novo_tiro = new Shot((pos_x + anim->frame_w/2 - c->game_shot_lv0->w/2), pos_y, SHOT_LV0);
     else if(charge == SHOT_LV1)
      novo_tiro = new Shot((pos_x + anim->frame_w/2 - c->game_shot_lv1->w/4), pos_y, SHOT_LV1);
     else if(charge == SHOT_LV2)
      novo_tiro = new Shot((pos_x + anim->frame_w/2 - c->game_shot_lv2->w/8), pos_y, SHOT_LV2);

     lista_tiros->push_back(novo_tiro);
     qtd_tiros++;
    }

   ///CARREGANDO O TIRO
   if((key[KEY_A] || xbox[BUTTON_A]) && !morreu)
   {
     if(just_pressed(KEY_A) || xbox_just_pressed(BUTTON_A))
      timer_charge = milisegundos;

     int aux = charge;

     if(milisegundos - timer_charge >= 2200)
      charge = SHOT_LV2;
     else if(milisegundos - timer_charge >= 750)
      charge = SHOT_LV1;

     if(aux == SHOT_LV0 && charge == SHOT_LV1)
       play_sample(c->FX_charging, vol_SFX, 128, 1000, true);
     else if(aux == SHOT_LV1 && charge == SHOT_LV2)
       play_sample(c->FX_fullcharge, vol_SFX, 128, 1000, false);
   }
   else{
    charge = SHOT_LV0; stop_sample(c->FX_charging); }
   }
}

int Spaceship::CheckCollision(GameObject* tiro)
{
  if(this->collidable && !this->imortal && tiro->collidable && tiro->ID >= SHOT_ENEMY_A && tiro->ID < TOTAL_ENEMY_SHOT_TYPES )
  {
    if(collision_between_animations(this->anim, (int)pos_x, (int)pos_y, tiro->anim, (int)tiro->pos_x, (int)tiro->pos_y))
    {
       vidas--;
       Reset_Stats();
       tiro->ativo = false;
       this->imortal = true;
       this->timer_imortal = milisegundos;

       return true;
    }
  }

  return false;
}

///UPDATE
void Spaceship::Update()
{
  if(charge == SHOT_LV1)
    charging1->Update();
  else if(charge == SHOT_LV2)
    charging2->Update();

  if(imortal && (milisegundos - timer_imortal) >= 1400)
    imortal = false;
}

///DRAW
void Spaceship::Draw()
{
  //Desenha a nave
  anim->Draw_ex(buffer, pos_x, pos_y, itofix(dir_x*3), 255);

  if(imortal && (milisegundos/100) % 2 == 0)
  {
     set_trans_blender(255,255,255,200);
     rotate_sprite_trans(buffer, c->game_imortal, pos_x, pos_y, itofix(dir_x*3));
  }


  //Animação da carga
  if(charge == SHOT_LV1)
    charging1->Draw(buffer, pos_x-3, pos_y-1);
  else if(charge == SHOT_LV2)
    charging2->Draw(buffer, pos_x-12, pos_y-10);

  //Marcador de vidas da nave
  for(int i = 0; i < vidas; i++)
   draw_sprite(buffer, c->game_life_counter, 750 - i*50, 550);
}
