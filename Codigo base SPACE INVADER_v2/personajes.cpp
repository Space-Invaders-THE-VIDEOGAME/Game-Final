#include "personajes.h"
#include "disparos.h"
#include "allegro.h"

#define ANCHO 800
#define ALTO  600

void Nave::inicia(const char *ruta_nave,const char *ruta_bala, int _ancho_b ,
                  int _alto_b , int _ancho_p , int _alto_p ,int _x , int _y ,int _dir_bala, int _tipo ){
    x = _x;
    y = _y;
    n_disp = 0;
    max_disp = 2;
    img_nav = load_bitmap(ruta_nave,NULL);
    img_bala = load_bitmap(ruta_bala,NULL);
    tick = 0;
    ancho_b = _ancho_b;
    alto_b = _alto_b;
    alto_p = _alto_p;
    ancho_p = _ancho_p;
    dir_bala = _dir_bala;
    tipo = _tipo;
}

bool Nave::temporizador(int tiempo){
    tick++;
    if(tick == tiempo){
        tick = 0;
        return true;
    }
    return false;
}

void Nave::pinta(BITMAP *buffer ,int ix , int iy){
    masked_blit(img_nav,buffer,ix*ancho_p,iy*alto_p,x,y,ancho_p,alto_p);
}

void Nave::mueve(){
    if(key[KEY_LEFT]){x -= 8;}
    if(key[KEY_RIGHT]){x += 8;}
}

void Nave::dispara(struct Balas disparos[] , BITMAP *buffer){

        if(tipo)
        crear_bala(n_disp,max_disp,disparos, x , y ,dir_bala);
        pintar_bala(n_disp,max_disp,disparos,buffer,img_bala ,ancho_b , alto_b);
        elimina_bala(n_disp,max_disp,disparos,ANCHO,ALTO);
}

void acomoda_enemigos(Nave E[]){
    int indice = -1;
    int _tipo = 0;
    for(int x = 0; x < 5 ; x++){
            _tipo++;
    if(_tipo == 4){_tipo = 1;}
        for(int i = 0; i < 11 ; i++){
            indice++;
            E[indice].inicia("Recursos/enemigos.bmp","Recursos/Bala_enem.bmp", 6 , 12 , 25 , 20 ,140+i*50,100+x*30, 10,_tipo);
        }
    }
}

void pintar_enemigos(Nave E[], BITMAP *buffer, int mov)
{
    int indice = -1;
    for(int x = 0; x < 5; x++)
        {
        for(int j= 0; j < 11; j++){
                indice++;
                E[indice].pinta(buffer,mov,E[indice].tipo - 1);
        }
    }
}
