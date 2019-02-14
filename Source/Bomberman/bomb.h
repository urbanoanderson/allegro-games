#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

#include "init.h"
#include "animation.h"
#include "collision.h"
#include "tilemap.h"

#define TEMPO_ATE_DETONACAO 2.25
#define VELOCIDADE_BOMBA 8

enum TIPO_BOMBA { BOMBA_NORMAL, BOMBA_RELOGIO, BOMBA_ESPINHO };

class Bomb
{
    protected:
      Animation anim;
      BoundingBox box;
      int x;
      int y;
      int posI;
      int posJ;
      int tipo;

      bool active;
      float timer;
      float time_until_explosion;

      bool in_motion;
      int dir;

    public:
      Bomb() { }
      void Initialize(int x, int y, int tipo, float time_until_explosion, Tilemap &map);
      void Update(Tilemap &map);
      void Draw();
      void Detonate(Tilemap &map) { active = false; map.SetBombPos(posI, posJ, 0); }
      bool GetActive() { return active; }
      BoundingBox GetBox() { return box; }
      int GetX() { return x; }
      int GetY() { return y; }
      int GetI() { return posI; }
      int GetJ() { return posJ; }
      int GetType() { return tipo; }
      bool GetInMotion() { return in_motion; }
      void KickBomb(int dir) { in_motion = true; this->dir = dir; }
      bool IsOnTheCenterOfTile();
      bool CheckForObstaclesOnTile(Tilemap &map, int i, int j);
     ~Bomb() { }
};

#endif // BOMB_H_INCLUDED
