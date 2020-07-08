#ifndef PERSONAJES_H_INCLUDED
#define PERSONAJES_H_INCLUDED

#include <allegro.h>

struct Nave{
    int x,y;
    int n_disp;
    int max_disp;
    int tick;
    int ancho_b , alto_b;
    int ancho_p , alto_p;
    int dir_bala;
    int tipo;

    BITMAP *img_nav;
    BITMAP *img_bala;

    void inicia(const char *ruta_nave,const char *ruta_bala , int _ancho_b , int _alto_b ,
                int _ancho_p , int _alto_p , int _x , int _y,int _dir_bala,int _tipo);
    bool temporizador(int tiempo);
    void pinta(BITMAP *buffer , int ix , int iy);
    void mueve();
    void dispara(struct Balas disparos[] , BITMAP *buffer);
};

void acomoda_enemigos(Nave E[]);
void pintar_enemigos(Nave E[], BITMAP *buffer, int mov);

#endif // PERSONAJES_H_INCLUDED
