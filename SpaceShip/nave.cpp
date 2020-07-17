#include "bala.h"
#include "nave.h"


Nave::Nave()
{

    x=(SCREEN_W/2.2);
    y=(SCREEN_H/1.2);
    ima_nave=load_bitmap("imagen/nave.bmp",NULL);
    ima_vida=load_bitmap("imagen/b_vida.bmp",NULL);
    vida=100;
}

Nave::~Nave()
{
    destroy_bitmap(ima_nave);
}

void Nave::draw(BITMAP*buffer)
{
    draw_sprite(buffer,ima_nave,x,y);
    tam_vida = (50.0/100.0) * vida;
	stretch_sprite(buffer,ima_vida,x,y+ima_nave->h/2,tam_vida,5);
}

void Nave::update(BITMAP*buffer)
{
    if (key[KEY_UP] && y>0)
        y-=2;
    if (key[KEY_DOWN] && y<SCREEN_H-ima_nave->h )
        y+=2;
    if (key[KEY_LEFT] && x>0)
        x-=2;
    if (key[KEY_RIGHT] && x<SCREEN_W-ima_nave->w)
        x+=2;
        draw(buffer);
}


