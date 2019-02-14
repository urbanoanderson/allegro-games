#ifndef UPGRADE_H_INCLUDED
#define UPGRADE_H_INCLUDED

#include "init.h"
#include "collision.h"
#include "animation.h"
#include "tilemap.h"

#define CHANCE_UPGRADE 30
#define TEMPO_INDESTRUTIVEL 0.6

enum UPGRADE_ID { EXTRA_BOMB, FIRE, SPEED, EXTRA_LIFE, REMOTE_BOMB, SPIKE_BOMB, KICK_BOMBS, TOTAL_UPGRADE_IDs };

class Upgrade
{
    protected:
        int ID;
        Animation anim;
        BoundingBox box;

        int x;
        int y;

        bool indestrutivel;
        float timer_indestrutivel;

    public:
        Upgrade() { }
        void Initialize(int x, int y);
        void Update();
        void Draw();
        int GerarID();
        BoundingBox GetBox() { return box; }
        int GetID() { return ID; }
        bool GetIndestrutivel() { return indestrutivel; }
       ~Upgrade() { }
};

#endif // UPGRADE_H_INCLUDED
