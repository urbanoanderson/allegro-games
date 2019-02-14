#include "animation.h"

void Animation::Initialize(ALLEGRO_BITMAP* img, int qtdframes, double switchtime, bool loop)
{
    this->img = img;
    this->qtdframes = qtdframes;
    this->switchtime = switchtime;
    this->loop = loop;

    this->finish = false;
    this->frame_h = height(img);
    this->frame_w = width(img) / qtdframes;
    this->curframe = 0;
    this->curtime = al_get_time();
}

void Animation::Reset()
{
    curframe = 0;
    finish = 0;
    curtime = al_get_time();
}

void Animation::Update()
{
    //Hora de trocar de frame
    if( (al_get_time() - curtime) >= switchtime )
    {
        curframe++;

        //Passou Último frame
        if(curframe == qtdframes)
        {
            curframe = 0;

            if(!loop)
             finish = true;
        }

        curtime = al_get_time();
    }
}

void Animation::Draw(float x, float y, float xScale, float yScale, float angle, ALLEGRO_COLOR tint)
{
    if(!finish)
    al_draw_tinted_scaled_rotated_bitmap_region(img, frame_w * curframe, 0, frame_w, frame_h, tint, frame_w/2, frame_h/2, x, y, xScale, yScale, angle, 0);
}

void Animation::Draw(float x, float y)
{
    if(!finish)
        al_draw_bitmap_region(img, frame_w * curframe, 0, frame_w, frame_h, x, y, 0);
}

void Animation::Draw_Flip(float x, float y, int flip)
{
    if(!finish)
        al_draw_bitmap_region(img, frame_w * curframe, 0, frame_w, frame_h, x, y, flip);
}
