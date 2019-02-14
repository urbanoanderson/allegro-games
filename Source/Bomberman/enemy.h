#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "init.h"
#include "animation.h"
#include "collision.h"
#include "tilemap.h"
#include "bomb.h"
#include "explosion.h"
#include "upgrade.h"

#define ENEMY_SPEED 1
#define ENEMY_IMORTAL_TIME 2.0

enum ENEMY_STATES { STATE_WALKING, STATE_CHOOSING };

class Enemy
{
    protected:
        Animation anim[4];
        BoundingBox box[4];
        int x;
        int y;
        int dir;
        int speed;
        int posI;
        int posJ;

        int state;
        int numpaths;
        bool arraypaths[4];

        int vidas;
        bool imortal;
        bool ativo;
        float timer_imortal;

    public:
        Enemy() { }
        void Initialize(int i, int j);
        bool CheckCollisionWithObstacles(Tilemap map, int testI, int testJ);
        void Move(Tilemap &map);
        void Update(Tilemap &map, std::list<Explosion> explosion_list);
        void Draw();
        bool GetActive() { return ativo; }
        BoundingBox GetBox() { return box[dir]; }

        void WalkOnCurrentDirection();
        bool IsOnTheCenterOfTile();
        void CountPaths(Tilemap &map);

       ~Enemy() { }
};

#endif // ENEMY_H_INCLUDED
