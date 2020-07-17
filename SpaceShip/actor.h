
#pragma once
#include <allegro.h>
class Actor
{
   protected:
       int x;
       int y;
       int vida;
   public:
     Actor();
    virtual~Actor();
    virtual void draw(BITMAP*);
    virtual void update(BITMAP*);
    void setvida(int _vida){vida -=_vida;}
    int getx(){return x;}
    int gety(){return y;}
    int getvida(){return vida;}
};
