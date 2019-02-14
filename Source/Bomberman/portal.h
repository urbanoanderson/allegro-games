#ifndef PORTAL_H_INCLUDED
#define PORTAL_H_INCLUDED

#include "init.h"
#include "animation.h"
#include "collision.h"
#include "tilemap.h"

class Portal
{
    private:
        Animation anim;
        int i, j;
        int x, y;

    public:
        Portal() { }
        void Initialize(int i, int j);
        bool Update(Tilemap map, int playerX, int playerY, int enemy_list_size);
        void Draw(Tilemap map, int enemy_list_size);
        ~Portal() { }
};

#endif // PORTAL_H_INCLUDED
