#ifndef PERSONAJES_H_INCLUDED
#define PERSONAJES_H_INCLUDED

#include <allegro.h>

/*struct Nave{
    int x,y;
    int n_disp;
    int max_disp;
    int tick;
    int ancho_b , alto_b;
    int ancho_p , alto_p;
    int dir_bala;
    int tipo;
    int vida;

    BITMAP *img_nav;
    BITMAP *img_bala;
    BITMAP *exp_n;

    void inicia(const char *ruta_nave,const char *ruta_bala , int _ancho_b , int _alto_b ,
                int _ancho_p , int _alto_p , int _x , int _y,int _dir_bala,int _tipo, int _vida);
    bool temporizador(int tiempo);
    void pinta(BITMAP *buffer , int ix , int iy);
    void mueve();
    void dispara(struct Balas disparos[] , BITMAP *buffer);
};*/

class Nave{
    private:
        int x,y;
        int n_disp;
        int max_disp;
        int tick;
        int anchi_b,alto_b;
        int dir_bala;
        int tipo;
        int vida;
        BITMAP *img_nav;
        BITMAP *img_bala;
        BITMAP *exp_n;
    public:
        void inicia(const char *ruta_nave,const char *ruta_bala , int _ancho_b , int _alto_b ,
                int _ancho_p , int _alto_p , int _x , int _y,int _dir_bala,int _tipo, int _vida);
    bool temporizador(int tiempo);
    void pinta(BITMAP *buffer , int ix , int iy);
    void mueve();
    void dispara(struct Balas disparos[] , BITMAP *buffer);
    int getNdisp(){return n_disp;}
};

void acomoda_enemigos(Nave E[]);
void pintar_enemigos(Nave E[], BITMAP *buffer, int mov);
void explosion1(struct Nave E ,BITMAP *buffer);
void crear_bala_enemigo(struct Nave E[] , int &azar);
void crear_bala_nave(struct Nave &E, struct Balas disparos[]);
bool limites(struct Nave E[] , int &dir);
void mover_enemigos(struct Nave E[] , int &mov , int &dir);

struct escudo{
    int x , y;
    int dan;
    int tipo;
};

void iniciar_escudo(struct escudo muros[]);
void pintar_escudos(struct escudo ES[], BITMAP *img_muro, BITMAP *buffer);

#endif // PERSONAJES_H_INCLUDED
