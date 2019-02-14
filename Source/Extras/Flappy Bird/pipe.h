#ifndef PIPE_H_INCLUDED
#define PIPE_H_INCLUDED

#include "init.h"
#include "boundingbox.h"
#include "player.h"

class Pipe
{
    private:
        BoundingBox box_up;
        BoundingBox box_down;
        bool point_given;
        bool active;
        float x, y;

    public:
        bool GetActive() { return active; }
        BoundingBox GetBoxUp() { return box_up; }
        BoundingBox GetBoxDown() { return box_down; }
        void Initialize(float x);
        void Update(Player* player);
        void Draw();
};

class PipeList
{
    private:
        std::list<Pipe> pipe_list;
        std::list<Pipe>::iterator it;

    public:
        void InsertPipe(float x);
        void Initialize();
        void Update(Player* player);
        void Draw();
        void ResetPipes();
};

#endif
