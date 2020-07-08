#ifndef DISPAROS_H_INCLUDED
#define DISPAROS_H_INCLUDED

#include <allegro.h>
#include "Personajes.h"

struct Balas{
    int x , y;
    int dx , dy;

};

//bool colicion(Nave &N, int h1 , int x2,Nave &E);
bool colicion(int x1 , int y1 , int w1 , int h1 , int x2 , int y2 , int w2, int h2);
void eliminar( Balas disparos[], int n_disparos, int cont);

void elimina_bala(int n_disparos, const int max_disparos, Balas disparos[],
                 const int ANCHO, const int ALTO);//Elimina la bala del buffer,si esta funcion no esta la imagen de la bala sigue en curso aunque no se vea






#endif // DISPAROS_H_INCLUDED
