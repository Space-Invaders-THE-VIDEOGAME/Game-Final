#include "personajes.h"
#include "disenio.h"
#include "disparos.h"
#include "allegro.h"

#define ANCHO 600
#define ALTO  600


void Nave::inicia(const char *ruta_nave,const char *ruta_bala, int _ancho_b ,
                  int _alto_b , int _ancho_p , int _alto_p ,int _x , int _y ,int _dir_bala, int _tipo ,int _vida){
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
    vida = _vida;
    exp_n = load_bitmap("Recursos/pum_enemigo.bmp" , NULL);
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
            E[indice].inicia("Recursos/enemigos.bmp","Recursos/Bala_enem.bmp", 6 , 12 , 25 , 20 ,140+i*30,130+x*24, 10,_tipo,1);
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
                if(E[indice].vida > 0){
                    E[indice].pinta(buffer,mov,E[indice].tipo - 1);
                }
        }
    }
}

void explosion1(struct Nave E, BITMAP *buffer){
    BITMAP *parche = create_bitmap(25 , 20 );
    clear_to_color(parche , 0x000000);
    blit(parche , buffer ,0,0, E.x , E.y , 25, 20);
    masked_blit(E.exp_n , buffer , 0,0,E.x - 10 , E.y , 41 , 34);

}
void crear_bala_enemigo(struct Nave E[] , int &azar){
        if(E[azar].n_disp == 0){
            azar = rand()% 55;
            while(E[azar].vida == 0){
                azar = rand()%55;
            }
        }
}

void crear_bala_nave(struct Nave &objNave, struct Balas disparos[]){
    if(key[KEY_SPACE] && objNave.temporizador(3))
        crear_bala(objNave.n_disp , objNave.max_disp , disparos , objNave.x , objNave.y , objNave.dir_bala);
}

bool limites(struct Nave E[] , int &dir){
    for(int i = 0; i < 55 ;i++){
        if((E[i].x > 520 || E[i].x < 50)&& E[i].vida != 0){
            dir = -1 * dir;
            return true;
        }
    }
    return false;
}
void mover_enemigos(struct Nave E[] , int &mov , int &dir){
    for(int i = 0; i < 55;i++){E[i].x += dir;}

        if(++mov == 2){mov = 0;}

        if(limites(E,dir)){
            for(int j = 0; j < 55;j++){E[j].y += 10;}
        }
}

void iniciar_escudo(struct escudo muros[]){
    char pos_muros[3][22] = {
       "AEC   AEC   AEC   AEC",
       "B D   B D   B D   B D",
     };
     int r = 0;
     for(int i = 0; i < 21; i++){
        for(int j = 0; j < 2; j++){
            if(pos_muros[j][i] != ' '){ //donde haya espacios vacios que haga algo
                muros[r].x = 90+i*20;
                muros[r].y = 400+j*15;
                muros[r].dan = 0;
                if(pos_muros[j][i] == 'A'){muros[r].tipo = 0;}
                if(pos_muros[j][i] == 'B'){muros[r].tipo = 1;}
                if(pos_muros[j][i] == 'C'){muros[r].tipo = 2;}
                if(pos_muros[j][i] == 'D'){muros[r].tipo = 3;}
                if(pos_muros[j][i] == 'E'){muros[r].tipo = 4;}
                r++;
            }
        }
     }

}
void pintar_escudos(struct escudo ES[], BITMAP *img_muro, BITMAP *buffer){
    for(int x = 0; x < 20 ; x++){ // 20 son los muros
            if(ES[x].dan != 3){
                masked_blit(img_muro , buffer , ES[x].dan*20, ES[x].tipo*16, ES[x].x, ES[x].y,20,16);
            }
    }
}
