#include <allegro.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "inicia.h"
#include "disparos.h"
#include "personajes.h"

#define ANCHO 800
#define ALTO  600


int main(){

    srand(time(NULL));

    inicia_allegro(ANCHO,ALTO);

    BITMAP *buffer = create_bitmap(ANCHO,ALTO);

    Nave n;
    n.inicia("Recursos/nave.bmp","Recursos/bala.bmp" , 8 , 8 , 80 , 100, ANCHO/2 , ALTO - 90 , -10 , 0);
    Nave E[60];
    acomoda_enemigos(E);

    Balas disparos[n.max_disp]; //estructura para que dispare la nave
    Balas disparos_enem[E[0].max_disp]; // estructuta para disparos del enemigo

    int azar = rand() % 55;
    int mov = 0;

    while(!key[KEY_ESC]){
        clear_to_color(buffer,0x000000);

        n.pinta(buffer,0,0);
        n.mueve();
        if(key[KEY_SPACE] && n.temporizador(3))
        crear_bala(n.n_disp , n.max_disp , disparos , n.x , n.y , n.dir_bala);

        n.dispara(disparos,buffer);

        pintar_enemigos(E,buffer,mov);
        if(E[azar].n_disp == 0){azar = rand()% 55;}
        E[azar].dispara(disparos_enem , buffer);
        if(E[0].temporizador(14)){
            if(++mov == 2){
                mov = 0;
            }
        }

        blit(buffer,screen,0,0,0,0,ANCHO,ALTO);
        rest(20);
    }
	return 0;
}
END_OF_MAIN();


