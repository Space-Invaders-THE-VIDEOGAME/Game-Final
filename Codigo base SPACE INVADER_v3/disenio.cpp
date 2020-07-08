#include "disenio.h"
#include <allegro.h>

void menuImagenes::Portada(BITMAP *p){
    int parpadeo = 0;
    int y = 0;
    int cont = 0;
    bool salida = false;
    bool cargar = false;

    while(!salida){
        if(parpadeo < 25){
            blit(p,screen,0,y,0,100,600,400);
        }
        else{
            blit(p , screen , 600 , y , 0, 100, 600,400);
        }
        if(key[KEY_ENTER]){
            y = 400;
            cargar = true;
        }
        if(cargar){
            cont++;
        }
        if(cont > 400){
            salida = true;
        }
        rest(5);
        if(++parpadeo == 50){
            parpadeo = 0;
        }
    }
    clear_to_color(screen,0x000000);
}

void menuImagenes::imprimir_fondo(BITMAP *fondo, BITMAP *buffer){
    masked_blit(fondo , buffer , 0 ,0, 0 ,0,600,600);
}
