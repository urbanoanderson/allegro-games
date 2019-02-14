#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "init.h"

class BoundingBox
{
    private:
     int x;
     int y;
     int w;
     int h;

     int offX, offY;

    public:
     BoundingBox() { }
     void Initialize(int offX, int offY, int w, int h) { this->offX = offX; this->offY = offY; this->w = w; this->h = h; }
     void Initialize2(int x, int y, int w, int h) { this->x = x; this->y = y; this->w = w; this->h = h; }
     void UpdatePosition(int x, int y) { this->x = x + offX; this->y = y + offY; }
     bool CheckCollision(BoundingBox box);
     bool CollisionWithTiles(int xt, int yt, int wt, int ht);
     void Draw();
     ~BoundingBox() { }
};

#endif // COLLISION_H_INCLUDED
