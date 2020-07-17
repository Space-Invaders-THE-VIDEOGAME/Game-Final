#include "enemigo.h"
#include <time.h>

Enemigo::Enemigo (int _x,int _y)
{
    x=_x;
    y=_y;
    ima_enemy=load_bitmap("imagen/bos.bmp",NULL);
    ima_vida=load_bitmap("imagen/b_vida.bmp",NULL);
    vida=100;
}

void Enemigo::draw(BITMAP*buffer)
{

    draw_sprite(buffer,ima_enemy,x,y);
    tam_vida = (50.0/100.0) * vida;
	stretch_sprite(buffer,ima_vida,x,y+ima_enemy->h/2,tam_vida,5);

}

void Enemigo::update(BITMAP*buffer)
{
   if(alarm.timer(6))
    {
     y++;
    if (y>SCREEN_H)
    {
        x = rand()%500+20
        ;
        y=0;
    }
    }
    draw(buffer);
}


Enemigo::~Enemigo()
{
    destroy_bitmap(ima_enemy);
}
