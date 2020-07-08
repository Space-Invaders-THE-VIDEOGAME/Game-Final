#include <allegro.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "inicia.h"
#include "disparos.h"
#include "personajes.h"
#include "disenio.h"

#define ANCHO 600      //porque la imagen de portada es de 600 x 600
#define ALTO  600

int main(){

    srand(time(NULL));
    /// DECLARACIONES DE OBJETOS

    iniciaAllegro objInicio;
    menuImagenes objMenu;
    Nave objNave;
    Nave E[60];

    /// DECLARACIONES DE OBJETOS
    objInicio.inicia_allegro(ANCHO,ALTO);

    BITMAP *buffer = create_bitmap(ANCHO,ALTO);
    BITMAP *portada = load_bitmap("Recursos/portada.bmp",NULL);
    BITMAP *fondo = load_bitmap("Recursos/fondo_juegov6.bmp",NULL);
    BITMAP *img_muros = load_bitmap("Recursos/escudos.bmp", NULL);

    objMenu.Portada(portada);

    objNave.inicia("Recursos/nave.bmp","Recursos/bala.bmp" , 8 , 8 , 80 , 100, ANCHO/2 , ALTO - 120 , -10 ,0,1);

    acomoda_enemigos(E);

    Balas disparos[objNave.max_disp]; //estructura para que dispare la nave
    Balas disparos_enem[E[0].max_disp]; // estructuta para disparos del enemigo

    escudo ES[30];

    iniciar_escudo(ES);

    int azar = rand() % 55;
    int mov = 0;
    int dir= -5;
    int velocidad_juego = 15;

    while(!key[KEY_ESC]){
        clear_to_color(buffer,0x000000);

        pintar_escudos(ES,img_muros,buffer);

        if(E[0].temporizador(velocidad_juego)){
            mover_enemigos(E,mov,dir);
        }

        objNave.pinta(buffer,0,0);
        objNave.mueve();
        crear_bala_nave(objNave , disparos);

        objNave.dispara(disparos,buffer);

        for(int x = 0; x < 55 ; x++){
            if(elimina_bala_objeto(objNave,E[x],disparos)){
                explosion1(E[x],buffer);
            }
        }
        eliminar_bala_escudo(objNave , ES,disparos);

        pintar_enemigos(E,buffer,mov);
        crear_bala_enemigo(E,azar);

        E[azar].dispara(disparos_enem , buffer);

        eliminar_bala_escudo(E[azar] , ES,disparos_enem);

        objMenu.imprimir_fondo(fondo , buffer); // imprime el fondo
        blit(buffer,screen,0,0,0,0,ANCHO,ALTO); // imprime todo por pantalla
        rest(20);
    }
	return 0;
}
END_OF_MAIN();


