#include "Enemy_List.h"


Enemy_List* Create_Enemy_List()
{
    Enemy_List* el = (Enemy_List*) malloc(sizeof(Enemy_List));

    el->inicio = NULL;
    el->numenemies = 0;
    el->timer_insertion = gametime;

    el->remainSOL = 0;
    el->remainSOLF = 0;
    el->remainMOTO = 0;
    el->remainTANK = 0;

    return el;
}

int Enemy_List_Empty(Enemy_List* el)
{
    return (el->numenemies == 0);
}

void Insert_Enemy_In_List(Enemy_List* el, Stage* s, int ID)
{
    Enemy_Node* novo = (Enemy_Node*) malloc(sizeof(Enemy_Node));
    novo->e = Create_Enemy(ID, s);
    novo->prox = el->inicio;
    el->inicio = novo;
    el->numenemies++;
}

void Program_Insertions_In_Enemy_List(Enemy_List* el, int qtdSOL, int qtdSOLF, int qtdMOTO, int qtdTANK, int time)
{
   el->remainSOL = qtdSOL;
   el->remainSOLF = qtdSOLF;
   el->remainMOTO = qtdMOTO;
   el->remainTANK = qtdTANK;

   el->to_next_insertion = time;
   el->timer_insertion = gametime;
}

int Remain_Units_To_Insert(Enemy_List* el)
{
    return (el->remainSOL + el->remainSOLF + el->remainMOTO + el->remainTANK);
}

void Try_to_Insert_In_Enemy_List(Enemy_List* el, Stage* s)
{
    //É hora de gerar um novo inimigo
    if(Remain_Units_To_Insert(el) > 0 && (gametime - el->timer_insertion >= el->to_next_insertion))
    {
        int inserido = FALSE;
        while(!inserido)
        {
          int randunity = rand()%4;

          if(randunity == SOLDADO && el->remainSOL > 0)
          {
            Insert_Enemy_In_List(el, s, SOLDADO);
            el->remainSOL--;
            inserido = TRUE;
          }

          else if(randunity == SOLDADO_FORTE && el->remainSOLF > 0)
          {
            Insert_Enemy_In_List(el, s, SOLDADO_FORTE);
            el->remainSOLF--;
            inserido = TRUE;
          }

          else if(randunity == MOTO && el->remainMOTO > 0)
          {
            Insert_Enemy_In_List(el, s, MOTO);
            el->remainMOTO--;
            inserido = TRUE;
          }

          else if(randunity == TANQUE && el->remainTANK > 0)
          {
            Insert_Enemy_In_List(el, s, TANQUE);
            el->remainTANK--;
            inserido = TRUE;
          }
        }

        el->timer_insertion = gametime;
    }
}

void Update_Enemy_List(Enemy_List* el, Stage* s)
{
    Enemy_Node* aux = el->inicio;
    Enemy_Node* aux2 = aux;

    while(aux != NULL)
    {
        Update_Enemy(aux->e, s);

        //Se inimigo morreu elimina-o da lista
        if(!aux->e->ativo)
        {
           //é o primeiro inimigo da lista
           if(aux == el->inicio)
           {
               el->inicio = el->inicio->prox;
               Destroy_Enemy(aux->e);
               free(aux);
               aux = el->inicio;
           }

           else
           {
               aux2->prox = aux->prox;
               Destroy_Enemy(aux->e);
               free(aux);
               aux = aux2->prox;
           }

            el->numenemies--;
        }

        else{
           aux2 = aux;
           aux = aux->prox;
        }
    }
}

void Draw_Enemy_List(Enemy_List* el, BITMAP* buffer)
{
    Enemy_Node* aux;
    for(aux = el->inicio; aux != NULL; aux = aux->prox)
    {
        if(aux->e->ativo)
         Draw_Enemy(aux->e, buffer);
    }
}

void Destroy_Enemy_List(Enemy_List* el)
{
    Enemy_Node* aux;
    while(el->inicio != NULL)
    {
       aux = el->inicio;
       el->inicio = el->inicio->prox;
       Destroy_Enemy(aux->e);
       free(aux);
    }

    free(el);
}


Enemy* Search_For_New_Target(Enemy_List* el, float x, float y, float raio, int torreID)
{
    Enemy* target = NULL;
    Enemy_Node* aux = el->inicio;

    while(target == NULL && aux != NULL)
    {
        if(Distancia(aux->e->x, aux->e->y, x, y) <= raio )
        {
            if(torreID == TORRE_ANTITANQUE && aux->e->ID == TANQUE)
             target = aux->e;
            else if(torreID != TORRE_ANTITANQUE)
             target = aux->e;
        }

        aux = aux->prox;
    }

    return target;
}
