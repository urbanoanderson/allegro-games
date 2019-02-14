#ifndef TIRO_H_INCLUDED
#define TIRO_H_INCLUDED

#include "init.h"
#include "Enemy.h"

int shotnoise1;

typedef struct tiro
{
    Enemy* target;

    float teta;
    float x;
    float y;
    float vel_x, vel_y;
    float power;
    int ativo;
    int ID;
}Tiro;

Tiro* Create_Tiro(int x, int y, float power, Enemy* target, int ID);
void Update_Tiro(Tiro* t, float iniX, float iniY, float raio);
void Draw_Tiro(Tiro* t, BITMAP* buffer);
void Destroy_Tiro(Tiro* t);

typedef struct no_tiro
{
   Tiro* t;
   struct no_tiro* prox;
}No_Tiro;

typedef struct lista_tiros
{
   No_Tiro* inicio;
}Lista_tiros;

Lista_tiros* Create_Lista_Tiros();
void Insere_Tiro(Lista_tiros* l, int x, int y, float power, int ID, Enemy* target);
void Update_Lista_Tiros(Lista_tiros* l, float iniX, float iniY, float raio);
void Draw_Lista_Tiros(Lista_tiros* l, BITMAP* buffer);
void Destroy_Lista_Tiros(Lista_tiros* l);

#endif
