#include "Personajes.h"
#include "Disparos.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define ANCHO 600
#define ALTO  600
void Nave ::inicia(const char *ruta_nave,const char *ruta_bala, int _ancho_b, int _alto_b,
                   int _ancho_p, int _alto_p, int _x, int _y,int _dir_bala,int _tipo, int _vida)
{
    x = _x;
    y = _y;
    n_disp = 0;
    max_disp = 3;
    img_nav = load_bitmap(ruta_nave,NULL);
    img_bala = load_bitmap(ruta_bala,NULL);
    tick = 0;
    ancho_b = _ancho_b;
    alto_b = _alto_b;
    alto_p = _alto_p;
    ancho_p = _ancho_p;
    dir_bala = _dir_bala;
    tipo = _tipo;
    vida = _vida;
    exp_n = load_bitmap("Recursos/pum_enemigo.bmp", NULL);
}

bool Nave::temporizador(int tiempo)
{
    tick++;
    if(tick == tiempo)
    {
        tick = 0;
        return true;
    }
    return false;
}

void Nave::pinta(BITMAP *buffer, int ix, int iy)
{
    masked_blit(img_nav,buffer,ix*ancho_p,iy*alto_p,x,y,ancho_p,alto_p);
}

void Nave::mueve()
{
    if(key[KEY_LEFT])
    {
        x -= 8;
    }
    if(key[KEY_RIGHT])
    {
        x += 8;
    }
}
void Nave::dispara(struct Balas disparos[], BITMAP *buffer)
{

    if(tipo)
        crear_bala(disparos);
    pintar_bala(disparos,buffer);
    elimina_bala(n_disp,max_disp,disparos,ANCHO,ALTO);
}

void Nave::crear_bala( struct Balas disparos[])
{

    if( n_disp<max_disp-1)  // n -1 disparos permitidos
    {
        set_nDisp();

        disparos[get_nDisp()].x  = x+11;
        disparos[get_nDisp()].y  = y;
        disparos[get_nDisp()].dx = 0;
        disparos[get_nDisp()].dy = dir_bala;
    }

}
void Nave::pintar_bala(Balas disparos[], BITMAP* buffer)

{
    if ( n_disp > 0 && n_disp < max_disp)
    {
        for ( int cont = 1; cont <= n_disp; cont++)
        {
            disparos[cont].x += disparos[cont].dx;
            disparos[cont].y += disparos[cont].dy;
            masked_blit( img_bala, buffer, 0, 0, disparos[cont].x, disparos[cont].y, ancho_b, alto_b);

        }
    }

}

void acomoda_enemigos(Nave E[])
{
    int indice = -1;
    int _tipo = 0;
    for(int x = 0; x < 5 ; x++)
    {
        _tipo++;
        if(_tipo == 4)
        {
            _tipo = 1;
        }
        for(int i = 0; i < 11 ; i++)
        {
            indice++;
            E[indice].inicia("Recursos/enemigos.bmp","Recursos/Bala_enem.bmp", 6, 12, 25, 20,140+i*30,130+x*24, 10,_tipo,1);
        }
    }

}


void pintar_enemigos(Nave E[], BITMAP *buffer, int mov)
{
    int indice = -1;
    for(int x = 0; x < 5; x++)
    {
        for(int j= 0; j < 11; j++)
        {
            indice++;
            if(E[indice].get_Vida() > 0)
            {
                E[indice].pinta(buffer,mov,E[indice].get_Tipo() - 1);
            }
        }
    }
}
bool limites( Nave E[], int &dir)
{
    for(int i = 0; i < 55 ; i++)
    {
        if((E[i].get_X()> 520 || E[i].get_X() < 50)&& E[i].get_Vida() != 0)
        {
            dir = -1 * dir;
            return true;
        }
    }
    return false;
}
void mover_enemigos( Nave E[], int &mov, int &dir)
{
    for(int i = 0; i < 55; i++)
    {
        E[i].set_X(dir);
    }

    if(++mov == 2)
    {
        mov = 0;
    }

    if(limites(E,dir))
    {
        for(int j = 0; j < 55; j++)
        {
            E[j].set_Y(10);
        }
    }
}
void disparos_enem (Nave E[],Balas disp_enem[], BITMAP *buffer)
{
    //int indice=0;
  //while( E[indice].get_Vida() > 0 && indice < 55 ) {
    //    indice ++;

  azar= rand()% 55;
    E[azar].dispara(disp_enem,buffer); //}
}
bool elimina_bala_objeto( Nave N,  Nave E[],  Balas balas[])
{

    if ( N.get_nDisp() > 0 && N.get_nDisp() < N.get_maxDIsp())
    {

        for ( int cont = 1; cont <= N.get_nDisp(); cont++)
        {

            for(int x=0; x<55; x++)
            {

                if(colicion(E[x].get_X(), E[x].get_Y(), E[x].get_anchoP(), E[x].get_altoP(), balas[cont].x, balas[cont].y,N.get_anchoB(), N.get_altoB()) && E[x].get_Vida() > 0)
                {
                    eliminar(balas,N.get_nDisp(),cont);
                    E[x].set_vida();
                    return true;
                }

            }
        }
    }
    return false;
}




void escudo::inicia_img()
{
    img_muros= load_bitmap("Recursos/escudos.bmp", NULL);

}

void iniciar_escudo(escudo muros[])
{
    char pos_muros[3][22] =
    {
        "AEC   AEC   AEC   AEC",
        "B D   B D   B D   B D",
    };
    int r = 0;
    for(int i = 0; i < 21; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(pos_muros[j][i] != ' ')  //donde haya espacios vacios que haga algo
            {
                muros[r].set_X(i);
                muros[r].set_Y(j);
                muros[r].set_Dan(0);
                if(pos_muros[j][i] == 'A')
                {
                    muros[r].set_tipo(0) ;
                }
                if(pos_muros[j][i] == 'B')
                {
                    muros[r].set_tipo(1);
                }
                if(pos_muros[j][i] == 'C')
                {
                    muros[r].set_tipo(2);
                }
                if(pos_muros[j][i] == 'D')
                {
                    muros[r].set_tipo(3);
                }
                if(pos_muros[j][i] == 'E')
                {
                    muros[r].set_tipo(4);
                }
                r++;
            }
        }
    }

}
void escudo::pinta(BITMAP *buffer)
{
    masked_blit(img_muros, buffer, dan*20,tipo*16, x, y,20,16);
}
void pintar_escudos(escudo ES[], BITMAP *buffer)
{

    for(int x = 0; x < 20 ; x++)  // 20 son los muros
    {

        ES[x].inicia_img();

        if(ES[x].get_Dan()
                != 3)
        {
            ES[x].pinta(buffer);
        }
    }
}

void Nave::set_vida()
{
    vida--;
}
int Nave::get_anchoB()
{
    return ancho_b;
}
int Nave::get_altoB()
{
    return alto_b;
}
int Nave::get_anchoP()
{
    return ancho_p;
}
int Nave::get_altoP()
{
    return alto_p;
}
int escudo::get_Dan()
{
    return dan;
}
int escudo::get_Tipo()
{
    return tipo;
}
int escudo::get_X()
{
    return x;
}
int escudo::get_Y()
{
    return y;
}
void escudo::set_tipo(int n)
{
    tipo=n;
}
void escudo::set_X(int i)
{
    x=90+i*20;
}
void escudo::set_Y(int j)
{
    y=400+j*15;
}
void escudo::set_Dan(int cero)
{
    dan=cero;
}
/*
void escudo::iniciar_escudo()
{
    char pos_muros[3][22] =
    {
        "AEC   AEC   AEC   AEC",
        "B D   B D   B D   B D",
    };
// int r = 0;
    for(int i = 0; i < 22; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(pos_muros[j][i] != ' ')  //donde haya espacios vacios que haga algo
            {
                x= 90+i*20;
                y=400+j*15;
                if(pos_muros[j][i] == 'A')
                {
                    tipo = 0;
                }
                if(pos_muros[j][i] == 'C')
                {
                   tipo = 2;
                }
                if(pos_muros[j][i] == 'B')
                {
                   tipo = 1;
                }
                if(pos_muros[j][i] == 'D')
                {
                 tipo = 3;
                }
                if(pos_muros[j][i] == 'E')
                {
                    tipo = 4;
                }
//r++;
            }

        }
    }

}

void escudo::pintar_escudos(BITMAP *buffer,escudo ES[])
{
    // 20 son los muros
    for (int i=0; i<4; i++)
    {
masked_blit(img_muros, buffer,1*20,ES[i].tipo*16, ES[i].x,ES[i].y,20,16);
    }
}

void escudo::iniciar_muro(const char *ruta_muro)
{
    for(int i=0;i<30;i++)
    {
        img_muros=load_bitmap(ruta_muro,NULL);
    }
}
*/
int Nave::get_Vida()
{
    return vida;
}

int Nave::get_Tipo()
{
    return tipo;
}

int Nave::get_nDisp()
{
    return n_disp;
}

void Nave::set_nDisp()
{
    n_disp++;
}

int Nave::get_maxDIsp()
{
    return max_disp;
}
int Nave::get_X()
{
    return x;
}
void Nave::set_X(int &dir)
{
    x+=dir;
}
int Nave::get_Y()
{
    return y;
}
void Nave::set_Y(int dir )
{
    y+=dir;
}
int Nave::get_dirBala()
{
    return dir_bala;
}
