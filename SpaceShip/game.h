#pragma once
#include <allegro.h>

class Game
{

private:
    BITMAP* buffer;
    bool gameover;
    int cont;
public:
    Game();
    void update();
    void draw();
    void dispose();
    void main();
    void start();
    void init();
    void shutdown();

};
