#include "boundingbox.h"

void BoundingBox::Draw(ALLEGRO_COLOR color)
{
    al_draw_rectangle(x, y, x+w, y+h, color, 2);
}

bool CheckCollision(BoundingBox box1, BoundingBox box2)
{
    if( (box1.x > box2.x + box2.w)
    ||  (box1.y > box2.y + box2.h)
    ||  (box2.x > box1.x + box1.w)
    ||  (box2.y > box1.y + box1.h) )
     return false;

    else
     return true;
}
