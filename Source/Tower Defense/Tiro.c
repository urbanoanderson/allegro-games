#include "Tiro.h"

Tiro* Create_Tiro(int x, int y, float power, Enemy* target, int ID)
{
    Tiro* t = (Tiro*) malloc(sizeof(Tiro));

    t->target = target;
    t->power = power;
    t->ativo = TRUE;
    t->x = (float)x;
    t->y = (float)y;
    t->ID = ID;

    t->teta = -atan2((target->y - y), (target->x - x));

    float vel = 10.0;
    t->vel_x = vel*cos(t->teta);
    t->vel_y = vel*sin(t->teta);

    if(ID == TORRE_NORMAL)
     play_sample(FX_machinegun, 235, 128, 1000, FALSE);
    else
      play_sample(FX_cannon, 235, 128, 1000, FALSE);

    return t;
}

void Update_Tiro(Tiro* t, float iniX, float iniY, float raio)
{
    t->x += t->vel_x;
    t->y -= t->vel_y;

    if(Distancia(t->x, t->y, t->target->x, t->target->y) <= 15)
    {
        t->target->vida -= t->power;
        t->ativo = FALSE;
    }
    else if(Distancia(t->x, t->y, iniX, iniY) > raio)
        t->ativo = FALSE;
}

void Draw_Tiro(Tiro* t, BITMAP* buffer)
{
    if(t->ID == TORRE_NORMAL)
      circlefill(buffer, t->x, t->y, 3, makecol(255, 255, 255));
    else
      circlefill(buffer, t->x, t->y, 5, makecol(0, 0, 0));
}

void Destroy_Tiro(Tiro* t)
{
    free(t);
}


///------------------------------------------------------------------------------------


Lista_tiros* Create_Lista_Tiros()
{
    Lista_tiros* l = (Lista_tiros*) malloc(sizeof(Lista_tiros));

    l->inicio = NULL;

    return l;
}

void Insere_Tiro(Lista_tiros* l, int x, int y, float power, int ID, Enemy* target)
{
    if(l != NULL)
    {
      No_Tiro* novo = (No_Tiro*) malloc(sizeof(No_Tiro));
      novo->t = Create_Tiro(x, y, power, target, ID);
      novo->prox = l->inicio;
      l->inicio = novo;
    }
}

void Update_Lista_Tiros(Lista_tiros* l, float iniX, float iniY, float raio)
{
    if(l != NULL)
    {
    No_Tiro* aux = l->inicio;
    No_Tiro* aux2 = l->inicio;

    while(aux != NULL)
    {
        //Se o tiro ainda está ativo
        if(aux->t->ativo)
        {
          Update_Tiro(aux->t, iniX, iniY, raio);
          aux2 = aux;
          aux = aux->prox;
        }

        //Caso contrário é preciso removê-lo da lista
        else
        {
            //Início da lista
            if(aux == aux2)
            {
                l->inicio = l->inicio->prox;
                Destroy_Tiro(aux->t);
                free(aux);
                aux2 = aux = l->inicio;
            }

            //Posição qualquer  (aux2 será o anterior a aux)
            else
            {
               aux2->prox = aux->prox;
               Destroy_Tiro(aux->t);
               free(aux);
               aux = aux2->prox;
            }
        }
    }
    }
}

void Draw_Lista_Tiros(Lista_tiros* l, BITMAP* buffer)
{
    if(l != NULL)
    {
      No_Tiro* aux = l->inicio;

      while(aux != NULL)
      {
        Draw_Tiro(aux->t, buffer);
        aux = aux->prox;
      }
    }
}

void Destroy_Lista_Tiros(Lista_tiros* l)
{
    if(l != NULL)
    {
      while(l->inicio != NULL)
      {
        No_Tiro* aux = l->inicio;
        l->inicio = l->inicio->prox;
        Destroy_Tiro(aux->t);
        free(aux);
      }
      free(l);
    }
}
