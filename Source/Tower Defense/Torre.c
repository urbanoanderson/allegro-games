#include "Torre.h"

Torre* Create_Torre(int ID, int i, int j)
{
    Torre* tn = (Torre*) malloc(sizeof(Torre));

    tn->ID = ID;
    tn->level = 1;
    tn->i = i;
    tn->j = j;
    tn->x = X0 + tn->j * TILESIZE + TILESIZE/2;
    tn->y = Y0 + tn->i * TILESIZE + TILESIZE/2;
    tn->target = NULL;
    tn->timer_update_tiro = gametime;

    if(ID == TORRE_NORMAL)
    {
      tn->img = torre_normal;
      tn->raio = TNRAIOLV1;
      tn->dano = TNDANOLV1;
      tn->tiros = Create_Lista_Tiros();
      tn->timer_tiro = gametime;
      tn->to_next_shot = 180;
    }

    else if(ID == TORRE_SLOW)
    {
      tn->img = torre_slow;
      tn->raio = TSRAIOLV1;
      tn->dano = TSSLOWLV1;
      tn->tiros = NULL;
    }

    if(ID == TORRE_ANTITANQUE)
    {
      tn->img = torre_antitanque;
      tn->raio = TARAIOLV1;
      tn->dano = TADANOLV1;
      tn->tiros = Create_Lista_Tiros();
      tn->timer_tiro = gametime;
      tn->to_next_shot = 500;
    }

    if(ID == TORRE_VENENO)
    {
      tn->img = torre_veneno;
      tn->raio = TVRAIOLV1;
      tn->dano = TVDANOLV1;
      tn->tiros = NULL;
      tn->to_next_shot = 8;
    }

    return tn;
}

void Aplicando_Veneno(Torre* tn, Enemy_List* el)
{
    Enemy_Node* aux = el->inicio;
    while(aux != NULL)
    {
      if(aux->e->ID != TANQUE)
      {
        //Se estiver dentro do alcance da torre
        if(Distancia(aux->e->x, aux->e->y, tn->x, tn->y) <= tn->raio+3)
        {
           aux->e->envenenado = TRUE;
           aux->e->vida -= tn->dano;
           if(aux->e->vida <= 0)
            aux->e->ativo = FALSE;
        }
      }
      aux = aux->prox;
    }
}

void Update_Torre(Torre* tn, Enemy_List* el, Stage* s)
{
    if(gametime - tn->timer_update_tiro >= 10){
      Update_Lista_Tiros(tn->tiros, tn->x, tn->y, tn->raio);
      tn->timer_update_tiro = gametime;
    }

    //Se não tem alvo procura um
    if(tn->target == NULL)
      tn->target = Search_For_New_Target(el, tn->x, tn->y, tn->raio, tn->ID);

    else if(tn->target->ativo)
    {
        //Insere tiro na lista
        if(tn->ID == TORRE_NORMAL || tn->ID == TORRE_ANTITANQUE)
        {
            if(gametime - tn->timer_tiro >= tn->to_next_shot)
            {
                Insere_Tiro(tn->tiros, tn->x, tn->y, tn->dano, tn->ID, tn->target);
                tn->timer_tiro = gametime;
            }
        }

        else if(tn->ID == TORRE_SLOW)
        {
            tn->target->slow = TRUE;
            if(tn->level == 1)
              tn->target->velaparente = tn->target->speed - (tn->target->speed * TSSLOWLV1);
            else if(tn->level == 2)
              tn->target->velaparente = tn->target->speed - (tn->target->speed * TSSLOWLV2);
            else if(tn->level == 3)
              tn->target->velaparente = tn->target->speed - (tn->target->speed * TSSLOWLV3);
        }

        else if(tn->ID == TORRE_VENENO)
         Aplicando_Veneno(tn, el);

        //Se a vida do alvo acabar ele morre (e a torre fica sem alvo)
        if(tn->target->vida <= 0.0)
        {
            tn->target->ativo = FALSE;

            if(tn->target->ID == SOLDADO)
             s->dinheiro += SOLDADOBONUS;
            else if(tn->target->ID == SOLDADO_FORTE)
             s->dinheiro += SOLDADOFBONUS;
            else if(tn->target->ID == MOTO)
             s->dinheiro += MOTOBONUS;
            else if(tn->target->ID == TANQUE)
             s->dinheiro += TANQUEBONUS;

            tn->target = NULL;
        }

        //Se ele tem um alvo travado testa se ele ainda está dentro do raio de alcance
        if(tn->target != NULL && Distancia(tn->target->x, tn->target->y, tn->x, tn->y) > tn->raio)
        {
            tn->target->slow = FALSE;
            tn->target->velaparente = tn->target->speed;
            tn->target = NULL;
        }
    }
    else
      tn->target = NULL;
}

void Draw_Torre(Torre* tn, BITMAP* buffer)
{
    draw_sprite(buffer, tn->img, tn->j*TILESIZE + X0, tn->i*TILESIZE + Y0);

    if(tn->level >= 2)
    {
       draw_sprite(buffer, marca_upgrade, tn->x + 10, tn->y-20);
       if(tn->level == 3)
       draw_sprite(buffer, marca_upgrade, tn->x + 10, tn->y-15);
    }

   if(tn->target != NULL)
   {
     if(tn->ID == TORRE_NORMAL)
      Draw_Lista_Tiros(tn->tiros, buffer);
     else if(tn->ID == TORRE_SLOW)
     {
        fastline(buffer, (int)tn->x, (int)tn->y, (int)tn->target->x, (int)tn->target->y, makecol(255,255,0));
        fastline(buffer, (int)tn->x+1, (int)tn->y+1, (int)tn->target->x+1, (int)tn->target->y+1, makecol(250,255,0));
     }
     else if(tn->ID == TORRE_ANTITANQUE)
      Draw_Lista_Tiros(tn->tiros, buffer);
   }
}

void Destroy_Torre(Torre* tn)
{
    Destroy_Lista_Tiros(tn->tiros);
    free(tn);
}


///--------------------------------------------------------------------------------
///---------------------------------------------------------------------------------
void Initialize_Matrix()
{
    int i, j;
    for(i = 0; i < NUMTILESI; i++)
    {
        for(j = 0; j < NUMTILESJ; j++)
          mtx[i][j] = NULL;
        selecao = NULL;
    }
}

void Insert_Tower_on_Matrix(int ID, int i, int j)
{
   if(i >= 0 && i < NUMTILESI
   && j >= 0 && j < NUMTILESJ
   && mtx[i][j] == NULL  )
   {
      mtx[i][j] = Create_Torre(ID, i, j);
   }
}

void Update_Tower_Matrix(Enemy_List* el, Stage* s)
{
    int i, j;
    for(i = 0; i < NUMTILESI; i++)
    {
        for(j = 0; j < NUMTILESJ; j++)
        {
            if(mtx[i][j] != NULL)
             Update_Torre(mtx[i][j], el, s);
        }
    }
}

void Draw_Tower_Matrix(BITMAP* buffer)
{
    int i, j;
    for(i = 0; i < NUMTILESI; i++)
    {
        for(j = 0; j < NUMTILESJ; j++)
        {
            if(mtx[i][j] != NULL)
            {
               Draw_Torre(mtx[i][j], buffer);
            }
        }
    }
}

void Destroy_Tower_Matrix()
{
    int i, j;
    for(i = 0; i < NUMTILESI; i++)
    {
        for(j = 0; j < NUMTILESJ; j++)
        {
            if(mtx[i][j] != NULL)
             Destroy_Torre(mtx[i][j]);
            mtx[i][j] = NULL;
        }
    }
}

