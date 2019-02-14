#ifndef ENEMY_LIST_H_INCLUDED
#define ENEMY_LIST_H_INCLUDED

#include "Enemy.h"

typedef struct enemy_node
{
   Enemy* e;
   struct enemy_node* prox;
}Enemy_Node;

typedef struct enemy_list
{
   Enemy_Node* inicio;
   int numenemies;

   int timer_insertion;
   int to_next_insertion;
   int remainSOL;
   int remainSOLF;
   int remainMOTO;
   int remainTANK;

}Enemy_List;

Enemy_List* Create_Enemy_List();
int Enemy_List_Empty(Enemy_List* el);
int Remain_Units_To_Insert(Enemy_List* el);
void Insert_Enemy_In_List(Enemy_List* el, Stage* s, int ID);
void Try_to_Insert_In_Enemy_List(Enemy_List* el, Stage* s);
void Program_Insertions_In_Enemy_List(Enemy_List* el, int qtdSOL, int qtdSOLF, int qtdMOTO, int qtdTANK, int time);
void Update_Enemy_List(Enemy_List* el, Stage* s);
void Draw_Enemy_List(Enemy_List* el, BITMAP* buffer);
void Destroy_Enemy_List(Enemy_List* el);

Enemy* Search_For_New_Target(Enemy_List* el, float x, float y, float raio, int torreID);

#endif
