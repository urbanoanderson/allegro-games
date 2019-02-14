#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include "init.h"

typedef struct coordenada
{
  int i;
  int j;
}Coordenada;

typedef struct tilemap
{
    int** matriz;
    int linhas;
    int colunas;
    int flip_ini;
    int flip_end;

    Coordenada ini;
    Coordenada fim;
}Tilemap;

Tilemap* Create_Tilemap(FILE* entrada);
void Draw_Tilemap(Tilemap* t, BITMAP* buffer);
void Draw_Bases(Tilemap* t, BITMAP* buffer);
void Destroy_Tilemap(Tilemap* t);

#endif
