#include <iostream>
#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

#include "Inicia.h"
#include "Personajes.h"
#include "Disparos.h"

#define ALTO 600 //porque la imagen de portada es de 600 x 600 si no, no funciona
#define ANCHO 600

int main()
{
    srand(time(NULL));

    Nave N;
    Nave E[60];

    Balas disparos[N.get_maxDIsp()];//vectores de struct bala

    Balas disp_enem [3];

    //iniciar_bEnmigas(disp_enem);//inicia el vector de clase, d los disparos enemigos

    inicia_allegro(ANCHO,ALTO);
    inicia_audio(70,70);

    BITMAP *buffer = create_bitmap(ANCHO,ALTO);


    N.inicia("Recursos/nave.bmp","Recursos/bala.bmp", 8, 8, 80, 100, ANCHO/2, ALTO - 120, -10,0,1);

   acomoda_enemigos(E);

 escudo ES[30];

    iniciar_escudo(ES);
    int mov = 0;
    int dir=-5;
    int velocidad_juego=14;

            while(!key[KEY_ESC])
    {
        clear_to_color(buffer,0x000000);

 pintar_escudos(ES,buffer);

        if(E[0].temporizador(velocidad_juego))
        {
            mover_enemigos(E,mov,dir);
        }
        N.pinta(buffer,0,0);
        N.mueve();
        if(key[KEY_SPACE] )
            N.crear_bala(disparos);
        N.dispara(disparos,buffer);


          if( elimina_bala_objeto(N,E,disparos))
            {
             //  explosion1(E[x],buffer);
            }



        pintar_enemigos(E,buffer,mov);
  disparos_enem (E,disp_enem, buffer);
        /*E[azar].dispara(disparo_enemigo,buffer);
        if(E[azar(55)].get_nDisp() == 0){azar(55);}
               E[azar(55)].dispara(disparos,buffer);
               if(E[0].temporizador(14)){
                   if(++mov == 2){ // cuanto uno antes de entrar en mov
                       mov = 0;
                   }
               }*/

        blit(buffer,screen,0,0,0,0,ANCHO,ALTO); // imprime todo por pantalla
        rest(20);
    }
    return 0;
}
END_OF_MAIN();
