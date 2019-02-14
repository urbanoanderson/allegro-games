#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "init.h"
#include "animation.h"
#include "collision.h"
#include "tilemap.h"
#include "bomb.h"
#include "explosion.h"
#include "upgrade.h"

#define TEMPO_IMORTALIDADE 2.0

#define STARTVIDAS 3
#define STARTSPEED 3
#define STARTBOMBAS 1
#define STARTEXPLOSIONSIZE 1

#define MAXVIDAS 10
#define MAXSPEED 6
#define MAXBOMBAS 10
#define MAXEXPLOSIONSIZE 10

class Player
{
    protected:
        Animation anim[4];
        BoundingBox box[4];
        std::list<Bomb> bomb_list;
        std::list<Bomb>::iterator it;
        std::list<Explosion> explosion_list;
        std::list<Explosion>::iterator it2;
        std::list<Upgrade> upgrade_list;
        std::list<Upgrade>::iterator it3;
        int iniX, iniY;
        int x;
        int y;
        int dir;
        int speed;
        int posI;
        int posJ;

        int tipo_bomba;
        int numbombas;
        int explosionsize;
        int vidas;

        float timer_imortal;
        bool imortal;

        bool podechutar;

    public:
        Player() { }
        void MoveBomb(int i, int j);
        void Initialize(int x, int y);
        void ResetStats();
        void PutBomb(Tilemap &map);
        void Die();
        void RaiseSpeed();
        void RaiseFire();
        void RaiseLife();
        void RaiseNumBombs();
        void DetonateRemoteBomb(Tilemap &map);
        void Move(Tilemap &map);
        int GetLives() { return vidas; }
        int GetX() { return x; }
        int GetY() { return y; }
        BoundingBox GetBox() { return box[dir]; }
        bool GetImortal() { return imortal; }
        std::list<Explosion> GetExplosionList() { return explosion_list; }
        bool CheckCollisionWithObstacles(Tilemap map, int testI, int testJ);
        void Update(Tilemap &map);
        void Draw();
        ~Player() { }
};

#endif // PLAYER_H_INCLUDED
