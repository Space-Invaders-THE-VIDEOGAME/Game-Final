#pragma once
#include<allegro.h>
#include "actor.h"

class Nave:public Actor
{
protected:
   // int vida;
    float tam_vida;
    BITMAP* ima_nave;
    BITMAP*ima_vida;
public:
     Nave();
     ~Nave();
    void draw(BITMAP*);
    void update(BITMAP*);
   // void setima_nave(BITMAP*image){ima_nave = image;};

};
