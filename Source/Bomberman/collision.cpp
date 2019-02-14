#include "collision.h"

bool BoundingBox::CheckCollision(BoundingBox box)
{
    if( (x > box.x + box.w) || (y > box.y + box.h) || (box.x > x + w) || (box.y > y + h) )
     return false;
    else
     return true;
}

bool BoundingBox::CollisionWithTiles(int xt, int yt, int wt, int ht)
{
    if( (x > xt + wt) || (y > yt + ht) || (xt > x + w) || (yt > y + h) )
     return false;
    else
     return true;
}

void BoundingBox::Draw()
{
    al_draw_rectangle(x, y, x+w, y+h, al_map_rgba(255,0,0,255), 1);
}
