#include "Disparos.h"
#include "Personajes.h"
#include <allegro.h>

bool colicion(int x1 , int y1 , int w1 , int h1 , int x2 , int y2 , int w2, int h2){

        return ((x1 < x2 + w2) && (x2 < x1 + w1 ) && (y1 < y2 + h2) && ( y2 < y1 + h1 ));

}

void eliminar( Balas disparos[], int n_disparos, int cont){
        Balas Btemp;
        Btemp = disparos[cont];
        disparos[cont] = disparos[n_disparos];
        disparos[n_disparos] = Btemp;
        n_disparos--;
        if ( n_disparos < 0 ){
                n_disparos=0;
        }
}
void elimina_bala(int n_disparos, const int max_disparos, struct Balas disparos[],
                  const int ANCHO, const int ALTO)
{

      if ( n_disparos > 0 && n_disparos < max_disparos){
            for ( int cont = 1; cont <= n_disparos; cont++){
                      if ( disparos[cont].y > ALTO || disparos[cont].y < 0 ||
                           disparos[cont].x > ANCHO || disparos[cont].x < 0  )
                       {
                                eliminar(disparos , n_disparos , cont);
                       }
            }
      }

}


