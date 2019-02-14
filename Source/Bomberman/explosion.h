#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include "init.h"
#include "tilemap.h"
#include "collision.h"
#include "upgrade.h"
#include "animation.h"
#include "bomb.h"

#define THICKNESS 42
#define UNIDADE_DE_EXPLOSAO 45
#define DURACAO_EXPLOSAO 0.5

typedef struct brick_info
{
  int i;
  int j;
}BRICK_INFO;

class Explosion
{
    protected:
      int posI, posJ;
      int x, y;

      int size;
      int boundup;
      int bounddown;
      int boundleft;
      int boundright;

      bool active;
      float timer;
      float time_until_end;

      BoundingBox box[2];

      Animation brick_anim;
      std::list<BRICK_INFO> brick_list;
      std::list<BRICK_INFO>::iterator it;

    public:
      Explosion() { }
      void Initialize(std::list<Bomb> &lista_bombas, Tilemap &map, int size, int i, int j, float time_until_end, bool flag_espinho);
      void FindBounds(Tilemap &map, bool flag_espinho);
      void Update(std::list<Upgrade> &upgrade_list, Tilemap &map);
      void Draw();
      bool GetActive() { return active; }
      int GetX() { return x; }
      int GetY() { return y; }
      BoundingBox GetBoxY() { return box[0]; }
      BoundingBox GetBoxX() { return box[1]; }
      ~Explosion() { }
};

#endif // EXPLOSION_H_INCLUDED
