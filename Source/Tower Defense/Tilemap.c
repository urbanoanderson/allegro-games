#include "Tilemap.h"

Tilemap* Create_Tilemap(FILE* entrada)
{
    int i, j;
    Tilemap* t = (Tilemap*) malloc(sizeof(Tilemap));
    t->linhas = 10;
    t->colunas = 15;

    fscanf(entrada, "%d %d", &t->ini.i, &t->ini.j);
    fscanf(entrada, "%d %d", &t->fim.i, &t->fim.j);

    t->matriz = (int**) malloc(t->linhas * sizeof(int*));
    for(i = 0; i < t->linhas; i++)
     t->matriz[i] = (int*) malloc(t->colunas * sizeof(int));

    for(i = 0; i < t->linhas; i++)
    {
        for(j = 0; j < t->colunas; j++)
          fscanf(entrada, "%d", &t->matriz[i][j]);
    }

    //Flipar o sprite das barracas se necessário
    if(t->matriz[t->ini.i][t->ini.j] == 3)
      t->flip_ini = TRUE;
    else
      t->flip_ini = FALSE;

    if(t->matriz[t->fim.i][t->fim.j] == 4)
      t->flip_end = TRUE;
    else
      t->flip_end = FALSE;

    return t;
}

void Draw_Tilemap(Tilemap* t, BITMAP* buffer)
{
    int i, j;
    for(i = 0; i < t->linhas; i++)
    {
        for(j = 0; j < t->colunas; j++)
        {
            if(t->matriz[i][j] != NONE)
              rectfill(buffer, X0 + TILESIZE*j, Y0 + TILESIZE*i, X0 + TILESIZE*(j+1), Y0 + TILESIZE*(i+1), makecol(168, 84, 0));
        }
    }
}

void Draw_Bases(Tilemap* t, BITMAP* buffer)
{
    if(!t->flip_ini)
     draw_sprite(buffer, barraca_ini, t->ini.j*TILESIZE + X0, t->ini.i*TILESIZE + Y0);
    else
     draw_sprite_h_flip(buffer, barraca_ini, t->ini.j*TILESIZE + X0, t->ini.i*TILESIZE + Y0);

    if(!t->flip_end)
     draw_sprite(buffer, barraca_fim, t->fim.j*TILESIZE + X0, t->fim.i*TILESIZE + Y0);
    else
     draw_sprite_h_flip(buffer, barraca_fim, t->fim.j*TILESIZE + X0, t->fim.i*TILESIZE + Y0);
}

void Destroy_Tilemap(Tilemap* t)
{
   int i;
   for(i = 0; i < t->linhas; i++)
     free(t->matriz[i]);

   free(t->matriz);
   free(t);
}
