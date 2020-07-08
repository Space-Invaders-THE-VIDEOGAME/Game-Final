#include <allegro.h>
#include <iostream>
#include "inicia.h"
#include "disparos.h"

#define ANCHO 800
#define ALTO  600

struct Nave{
    int x,y;
    int n_disp;
    int max_disp;
    int tick;
    int ancho_b , alto_b;
    int ancho_p , alto_p;
    int dir_bala;

    BITMAP *img_nav;
    BITMAP *img_bala;

    void inicia(const char *ruta_nave,const char *ruta_bala , int _ancho_b , int _alto_b ,
                int _ancho_p , int _alto_p , int _x , int _y,int _dir_bala);
    bool temporizador();
    void pinta(BITMAP *buffer);
    void mueve();
    void dispara(struct Balas disparos[] , BITMAP *buffer);

};

void Nave::inicia(const char *ruta_nave,const char *ruta_bala, int _ancho_b ,
                  int _alto_b , int _ancho_p , int _alto_p ,int _x , int _y ,int _dir_bala ){
    x = _x;
    y = _y;
    n_disp = 0;
    max_disp = 5;
    img_nav = load_bitmap(ruta_nave,NULL);
    img_bala = load_bitmap(ruta_bala,NULL);
    tick = 0;
    ancho_b = _ancho_b;
    alto_b = _alto_b;
    alto_p = _alto_p;
    ancho_p = _ancho_p;
    dir_bala = _dir_bala;
}

bool Nave::temporizador(){
    tick++;
    if(tick == 5){
        tick = 0;
        return true;
    }
    return false;
}

void Nave::pinta(BITMAP *buffer){
    masked_blit(img_nav,buffer,0,0,x,y,ancho_p,alto_p);
}

void Nave::mueve(){
    if(key[KEY_LEFT]){x -= 8;}
    if(key[KEY_RIGHT]){x += 8;}
}

void Nave::dispara(struct Balas disparos[] , BITMAP *buffer){
    if(key[KEY_SPACE] && temporizador()){
            crear_bala(n_disp,max_disp,disparos, x , y ,dir_bala);
        }
        pintar_bala(n_disp,max_disp,disparos,buffer,img_bala ,ancho_b , alto_b);
        elimina_bala(n_disp,max_disp,disparos,ANCHO,ALTO);
}

void acomoda_enemigos(struct Nave E[]){
    int indice = -1;
    for(int x = 0; x < 5 ; x++){
        for(int i = 0; i < 5 ; i++){
            indice++;

            E[indice].inicia("Recursos/enemigos.bmp","Recursos/Bala_enem.bmp", 6 , 12 , 25 , 20 , ANCHO/2 + x,ALTO - 50 + i, 10);
        }
    }
}

void pintar_enemigos(struct Nave E[], BITMAP *buffer){
    int indice = -1;
    for(int x = 0; x < 5; x++){
        for(int j= 0; j < 11; j++){
                indice++;
            E[indice].pinta(buffer);
        }
    }
}

using namespace std;

int main(){

    inicia_allegro(ANCHO,ALTO);

    BITMAP *buffer = create_bitmap(ANCHO,ALTO);

    Nave n;
    n.inicia("Recursos/nave.bmp","Recursos/bala.bmp" , 8 , 8 , 80 , 100, ANCHO/2 , ALTO - 90 , -10);
    //Nave E[10];

    //acomoda_enemigos(E);

    Balas disparos[n.max_disp]; //estructura para que dispare la nave
    //Balas disparos_enem[E[0].max_disp]; // estructuta para disparos del enemigo

    while(!key[KEY_ESC]){
        clear_to_color(buffer,0x000000);

        n.pinta(buffer);
        n.mueve();
        n.dispara(disparos,buffer);

        //pintar_enemigos(E,buffer);

        blit(buffer,screen,0,0,0,0,ANCHO,ALTO);
        rest(20);
    }
	return 0;
}
END_OF_MAIN();


