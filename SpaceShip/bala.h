#pragma once
#include <allegro.h>
#include "actor.h"
#include "alarma.h"

class Bala:public Actor
{
protected:

    int tipo;
    BITMAP* sprite;
    Alarma timer;
public:

    Bala(int, int, int);
    void mov(BITMAP*);

};

