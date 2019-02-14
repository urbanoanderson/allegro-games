#ifndef TORRE_H_INCLUDED
#define TORRE_H_INCLUDED

#include "Enemy_List.h"
#include "Tiro.h"

typedef struct torre
{
   BITMAP* img;
   int i, j;
   float x, y;

   int ID;
   int level;
   float raio;
   float dano;
   Enemy* target;

   Lista_tiros* tiros;
   int timer_tiro;
   int to_next_shot;
   int timer_update_tiro;
}Torre;


Torre* Create_Torre(int ID, int i, int j);
void Aplicando_Veneno(Torre* tn, Enemy_List* el);
void Update_Torre(Torre* tn, Enemy_List* el, Stage* s);
void Draw_Torre(Torre* tn, BITMAP* buffer);
void Destroy_Torre(Torre* tn);

///--------------------------------------------------------------
///Matriz de torres
Torre* mtx[NUMTILESI][NUMTILESJ];
Torre* selecao;

void Initialize_Matrix();
void Insert_Tower_on_Matrix(int ID, int i, int j);
void Update_Tower_Matrix(Enemy_List* el, Stage* s);
void Draw_Tower_Matrix(BITMAP* buffer);
void Destroy_Tower_Matrix();



#endif
