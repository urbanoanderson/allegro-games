#include "Enemy.h"

Enemy* Create_Enemy(int ID, Stage* s)
{
    Enemy* e = (Enemy*) malloc(sizeof(Enemy));

    e->ID = ID;
    e->slow = FALSE;
    e->envenenado = FALSE;
    e->ativo = TRUE;
    e->dir = s->map->matriz[s->map->ini.i][s->map->ini.j];
    e->x = (float)(s->map->ini.j * TILESIZE + X0 + TILESIZE/2);
    e->y = (float)(s->map->ini.i * TILESIZE + Y0 + TILESIZE/2);
    e->timer_movimento = gametime;

    if(e->ID == SOLDADO)
    {
       e->anim = Create_Animation(soldado, 11, 50, TRUE);
       e->img_veneno = soldado_veneno;
       e->img_slow = soldado_slow;
       e->speed = 1.5;
       e->vidamax = 100.0;
       e->vida = 100.0;
    }

    else if(e->ID == SOLDADO_FORTE)
    {
       e->anim = Create_Animation(soldadof, 10, 60, TRUE);
       e->img_veneno = soldadof_veneno;
       e->img_slow = soldadof_slow;
       e->speed = 1.7;
       e->vidamax = 250.0;
       e->vida = 250.0;
    }

    else if(e->ID == MOTO)
    {
       e->anim = Create_Animation(moto, 4, 60, TRUE);
       e->img_veneno = moto_veneno;
       e->img_slow = moto_slow;
       e->speed = 2.0;
       e->vidamax = 220.0;
       e->vida = 220.0;
    }

    else if(e->ID == TANQUE)
    {
       e->anim = Create_Animation(tank, 3, 60, TRUE);
       e->img_veneno = NULL;
       e->img_slow = tank_slow;
       e->speed = 0.8;
       e->vidamax = 1000.0;
       e->vida = 1000.0;
    }

    e->velaparente = e->speed;

    return e;
}

void Update_Enemy(Enemy* e, Stage* s)
{
   if(e->ativo)
   {
    Update_Animation(e->anim);

    //Movimento
    if(gametime - e->timer_movimento >= 10) //100fps
    {
      if(e->dir == UP)
        e->y -= e->velaparente;
      else if(e->dir == DOWN)
        e->y += e->velaparente;
      else if(e->dir == LEFT)
        e->x -= e->velaparente;
      else if(e->dir == RIGHT)
        e->x += e->velaparente;

      e->timer_movimento = gametime;
    }

    //Gera coordenadas i e j do inimigo na na matriz
    int i = (e->y - Y0)/TILESIZE;
    int j = (e->x - X0) / TILESIZE;

    //Se chegou ao fim morre e tira vida do jogador
    if(i == s->map->fim.i && j == s->map->fim.j)
    {
       s->vidas--;
       e->ativo = FALSE;
    }

    //Atualiza direção do inimigo baseado no mapa
    int x_cen = j*TILESIZE + TILESIZE/2 + X0;
    int y_cen = i*TILESIZE + TILESIZE/2 + Y0;

    if( (e->x >= (x_cen - 1) && e->x <= (x_cen + 1))
     && (e->y >= (y_cen - 1) && e->y <= (y_cen + 1)) )
     e->dir = s->map->matriz[i][j];
  }
}

void Draw_Enemy(Enemy* e, BITMAP* buffer)
{
    if(e->ativo)
    {
       //Animação
       if(e->dir == RIGHT)
       {
         if(e->envenenado)
          Draw_Animation(e->anim, e->img_veneno, buffer, ((int)e->x - e->anim->frame_w/2), ((int)e->y - e->anim->frame_h/2));
         else if(e->slow)
          Draw_Animation(e->anim, e->img_slow, buffer, ((int)e->x - e->anim->frame_w/2), ((int)e->y - e->anim->frame_h/2));
         else
          Draw_Animation(e->anim, NULL, buffer, ((int)e->x - e->anim->frame_w/2), ((int)e->y - e->anim->frame_h/2));
       }
       else if(e->dir == LEFT)
       {
         if(e->envenenado)
          Draw_Animation_H_Flip(e->anim, e->img_veneno, buffer, ((int)e->x - e->anim->frame_w/2), ((int)e->y - e->anim->frame_h/2));
         else if(e->slow)
          Draw_Animation_H_Flip(e->anim, e->img_slow, buffer, ((int)e->x - e->anim->frame_w/2), ((int)e->y - e->anim->frame_h/2));
         else
          Draw_Animation_H_Flip(e->anim, NULL, buffer, ((int)e->x - e->anim->frame_w/2), ((int)e->y - e->anim->frame_h/2));
       }
       else if(e->dir == UP)
       {
         if(e->envenenado)
          Draw_Animation_90_degree(e->anim, e->img_veneno, buffer, ((int)e->x - e->anim->frame_w/2), ((int)e->y - e->anim->frame_h/2), -1 );
         else if(e->slow)
          Draw_Animation_90_degree(e->anim, e->img_slow, buffer, ((int)e->x - e->anim->frame_w/2), ((int)e->y - e->anim->frame_h/2),-1);
         else
          Draw_Animation_90_degree(e->anim, NULL, buffer, ((int)e->x - e->anim->frame_w/2), ((int)e->y - e->anim->frame_h/2), -1);
       }
       else if(e->dir == DOWN)
       {
         if(e->envenenado)
          Draw_Animation_90_degree(e->anim, e->img_veneno, buffer, ((int)e->x - e->anim->frame_w/2), ((int)e->y - e->anim->frame_h/2), 1 );
         else if(e->slow)
          Draw_Animation_90_degree(e->anim, e->img_slow, buffer, ((int)e->x - e->anim->frame_w/2), ((int)e->y - e->anim->frame_h/2), 1);
         else
          Draw_Animation_90_degree(e->anim, NULL, buffer, ((int)e->x - e->anim->frame_w/2), ((int)e->y - e->anim->frame_h/2), 1);
       }

       e->envenenado = FALSE;

       //Barra de vida
       rectfill(buffer, (e->x-15), (e->y-28), (e->x-15) + 30, (e->y-28)+5, makecol(255, 0, 0));
       rectfill(buffer, (e->x-15), (e->y-28), (e->x-15) + 30 * (e->vida/e->vidamax), (e->y-28)+5, makecol(0, 220, 0));
    }
}

void Destroy_Enemy(Enemy* e)
{
   Destroy_Animation(e->anim);
   free(e);
}
