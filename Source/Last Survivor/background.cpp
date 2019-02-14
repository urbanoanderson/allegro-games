#include "background.hpp"

void Background::Set_New_Planet()
{
   planet = c->game_planetas[randnum(MAX_PLANETAS)];
   planeta_y = -planet->h;
   planeta_x = -planet->w/2 + rand() % (SCREEN_W + planet->w/4);
   curtime_pl = milisegundos;
   to_next_planet = 4000 + (rand() % 10000);
   teta = 0.0;

   if(rand()%2 == 0)
    dir_teta = LEFT;
   else
    dir_teta = RIGHT;
}

///CREATE
Background::Background()
{
   front = c->game_BG[0];
   back = c->game_BG[0];
   next = c->game_BG[0];
   planet = NULL;

   BG_y = 0;
   curtime = milisegundos;
   to_next_BG = 20000 + (rand() % 10001);

   curtime_pl = milisegundos;
   to_next_planet = 3000 + (rand() % 9000);
}

///UPDATE
void Background::Update()
{
    //Se der o tempo altera quem é o next
    if(milisegundos - curtime >= to_next_BG)
    {
       int aux;
       do{
       aux = rand() % MAX_BG;
       }while(c->game_BG[aux] == front);

       next = c->game_BG[aux];
       curtime = milisegundos;
       to_next_BG = 20000 + (rand() % 10001);
    }

    //Se tiver na hora de aparecer um planeta
    if(planet == NULL && (milisegundos - curtime_pl >= to_next_planet))
     Set_New_Planet();

    //Move o BG
    BG_y += 4.2;

    //Move o planeta
    planeta_y += 2.0;
    teta += 0.05 * dir_teta;

   //Se o BG chegou ao final
   if(BG_y - back->h >= 0)
   {
     BG_y = 0;
     front = back;
     back = next;
   }

   //Se o planeta chegou ao final
   if((int)planeta_y > SCREEN_H + 50)
    planet = NULL;
}

///DRAW
void Background::Draw()
{
    draw_sprite(buffer, front, 0, (int)BG_y);
    draw_sprite(buffer, back, 0, ((int)BG_y - back->h));

    if(planet != NULL)
     rotate_sprite(buffer, planet, (int)planeta_x, (int)planeta_y, ftofix(teta));
}
