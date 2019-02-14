#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "init.h"
#include "animation.h"
#include "boundingbox.h"

class Player
{
    private:
        float x, y, speed_y;
        int score;
        bool alive;
        BoundingBox box;

    public:
        void WinPoint();
        int GetScore() { return score; }
        float GetX() { return x; }
        float GetY() { return y; }
        float GetAlive() { return alive; }
        BoundingBox GetBox() { return box; }

        void Die();
        void Jump();
        void Initialize();
        void Update();
        void Draw();
};

#endif // PLAYER_H_INCLUDED
