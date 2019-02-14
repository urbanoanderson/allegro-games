#ifndef BOUNDINGBOX_H_INCLUDED
#define BOUNDINGBOX_H_INCLUDED

#include "init.h"

class BoundingBox
{
    private:
        int x;
        int y;
        int w;
        int h;

    public:
        int GetH() { return h; }
        void Initialize(int x, int y, int w, int h) { this->x = x; this->y = y; this->w = w; this->h = h; }
        void UpdatePosition(int x, int y) { this->x = x; this->y = y; }
        void Draw(ALLEGRO_COLOR color);
        friend bool CheckCollision(BoundingBox box1, BoundingBox box2);
};

bool CheckCollision(BoundingBox box1, BoundingBox box2);

#endif
