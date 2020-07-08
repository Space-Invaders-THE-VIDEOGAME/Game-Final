#ifndef PERSONAJES_H_INCLUDED
#define PERSONAJES_H_INCLUDED
#include <allegro.h>
#include "Disparos.h"
class escudo{
    private:
    int x , y;
    int tipo;
    int dan;
 BITMAP *img_muros;
 public:
 void inicia_img();
     void pinta(BITMAP *buffer);
 int get_X();
 int get_Y();
 int get_Tipo();
 int get_Dan();
 void set_X(int);
 void set_Y(int);
 void set_tipo(int);
 void set_Dan(int);
};

class Nave
{
private:

    int x,y;
    int n_disp;
    int max_disp;
    int tick;
    int ancho_b, alto_b;
    int ancho_p, alto_p;
    int dir_bala;
    int tipo;
    int vida;
    BITMAP *img_nav;
    BITMAP *img_bala;
    BITMAP *exp_n;

public:
    void inicia(const char *ruta_nave,const char *ruta_bala, int _ancho_b, int _alto_b,
                int _ancho_p, int _alto_p, int _x, int _y,int _dir_bala,int _tipo, int _vida);
    bool temporizador(int tiempo);
    void pinta(BITMAP *buffer, int ix, int iy);
    void mueve();
    void dispara( struct Balas disparos[], BITMAP *buffer);
    void crear_bala(struct Balas disparos[]);
    void pintar_bala(struct Balas disparos[],BITMAP *buffer);
    int get_anchoB();
        int get_altoB();
    int get_anchoP();
    int get_altoP();
int get_Vida();
int get_Tipo();
int get_nDisp();
void set_nDisp();
int get_maxDIsp();
int get_dirBala();
int get_X();
int get_Y();
void set_X(int &dir);
void set_Y(int dir);
void set_vida();
};
//****FUNCIONES DE LOS ENEMIGOS*****//
void explosion1( Nave E[] ,BITMAP *buffer);
bool limites( Nave E[] , int &dir);
void mover_enemigos( Nave E[] , int &mov , int &dir);
void pintar_enemigos(Nave E[], BITMAP *buffer, int mov);
void acomoda_enemigos(Nave E[]);
void disparos_enem (Nave E[],Balas disp_enem[], BITMAP *buffer);
bool elimina_bala_objeto( Nave N, Nave E[], Balas balas[]);

//Funciones Escudos//
void iniciar_escudo( struct escudo muros[]);
void pintar_escudos( struct escudo ES[], BITMAP *buffer);

#endif // PERSONAJES_H_INCLUDED
