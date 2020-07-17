#include <list>
#include "menu.h"
#include "alarma.h"
#include "game.h"
#include "bala.h"
#include "nave.h"
#include "enemigo.h"
#include "fondo.h"
using namespace std;

Game::Game()
{
    start();
    buffer = create_bitmap(SCREEN_W,SCREEN_H);
    gameover = false;


}

void Game::init()
{
    main();
    shutdown();

}


void Game::draw()
{
    draw_sprite(screen,buffer,0,0);
    clear_to_color(buffer,0x000000);
}

void Game::update()
{

}

void Game::main()
{
    Menu menu;
    Alarma alarm_bala;     ///objeto  alarma para manejar los tiempos de dibujo de sprite de la bala
    menu.inicio();               ///iniciamaos la clase menu donde  se cargan todos los bitamps
    Fondo *fondo= new Fondo();
    Nave *nave= new Nave();
    list<Enemigo*>enemy;
    list<Bala*>balas;
    list<Bala*>bala_enemy;
    list<Bala *>::iterator itbala;         ///creamos in iterador para las balas
    list<Enemigo*>::iterator itenemy;     ///creamos in iterador para las enemigos
    list<Bala *>::iterator itbalaEne;
    for (int i=0; i<10; i++)
    {
        int p= rand()%600-700;                      ///creo numeros aleatorios y las asigno a la cordenada "Y" de los enemigos
        int c=rand()%300-500;
        enemy.push_back(new Enemigo((i+1)*100,p-c));   /// crea una lista de los enemigos
    }
    bool salir=false;
    int op,p=0;
    while(!salir)
    {
        op=menu.draw(buffer);  /// dibuja el menu y nos retorna por ahora 1 o 2

        if (op==1)
        {

            while(!key[KEY_ESC] && !gameover)    /// gamelopp
            {
                fondo->draw(buffer);     ///  se dibuja el fondo
                nave->update(buffer);   ///  se dibuja la nave

                for(itenemy = enemy.begin(); itenemy != enemy.end(); itenemy++)  ///iterador de la lista para dibujar enemigos
                {
                    (*itenemy)->update(buffer);   /// cada enemigo de la lista  "itenemy"    llama a su metodo update

                    if ((rand()%1000)>997)  ///condicion para que solo se cree balas enemigas si  el (rand) es mayor a 997
                    {
                        bala_enemy.push_back(new Bala((*itenemy)->getx()+20,(*itenemy)->gety()+50,2)); /// se crean las balas enemigas
                    }
                    for (itbalaEne=bala_enemy.begin(); itbalaEne!= bala_enemy.end(); itbalaEne++)  ///iterador para recorrer todas las balas creadas
                    {
                        (*itbalaEne)->mov(buffer);  ///se dibujan las balas enemigas

                         if ((*itbalaEne)->gety()>SCREEN_H || (*itbalaEne)->getx() >= nave->getx() && (*itbalaEne)->getx() <= nave->getx()+50 &&   ///condicion para que  baje de vida si la bala enemiga coliciona con nuetra nave
                                           (*itbalaEne)->gety() >= nave->gety() &&(*itbalaEne)->gety() <= nave->gety()+50 )
                         {
                                      delete (*itbalaEne);
                                      bala_enemy.erase(itbalaEne);
                                        nave->setvida(3);
                                 if (nave->getvida()<1)
                                 {
                                     delete nave;
                                     while(!key[KEY_ENTER])
                                     {
                                         menu.gameover(buffer);
                                         draw();
                                     }
                                     gameover =true;
                                 }
                         }
                    }

                }

                if (key[KEY_SPACE]&& alarm_bala.timer(100))   ///condicion para manejar el timepo de  creacion  de las  balas
                {

                    balas.push_back(new Bala(nave->getx()+20,nave->gety(),1));  /// se crea una lista de balas
                }

                for(itbala = balas.begin(); itbala != balas.end(); itbala++)   /// se dibujan las balas
                {
                    (*itbala)->mov(buffer); ///cada bala de la lista "itbala" llama a  su metodo mov

                    if (!((*itbala)->gety()>0))   ///condicion  para eliminar la bala cuando salga de la pantalla
                    {
                        delete (*itbala);
                        balas.remove(*itbala);

                    }
                }
                for(itenemy = enemy.begin(); itenemy != enemy.end(); itenemy++)     /// volvemos a llamar al iterador de enemigos para detectar coliciones
                {
                    for(itbala = balas.begin(); itbala != balas.end(); itbala++)
                    {
                        if((*itbala)->getx() >= (*itenemy)->getx() && (*itbala)->getx() <= (*itenemy)->getx()+30 &&  ///condicion para que cuando la bala toque los enemigos  desaparesca
                                (*itbala)->gety() >= (*itenemy)->gety() && (*itbala)->gety() <= (*itenemy)->gety()+30)
                        {
                            delete (*itbala);
                            balas.remove(*itbala);
                            (*itenemy)->setvida(10);    /// con cada colicion de la bala la vida del enemigo menora

                            if ((*itenemy)->getvida()<1)   ///si la vida del enemigo es menor a 0 se la imagen del enemigo se elimina
                            {
                                delete (*itenemy);   /// se elimina el la imagen del enemigo

                                enemy.remove(*itenemy);   /// se remueve el enemigo
                            }
                        }
                    }

                }

                draw();  /// se limpia el buffer en el segundo while
            }
        }
        if(op==2)
        {
            salir=true;
        }
        draw();     /// se limpia el buffer antes de la llave del primer while
    }
    //
    nave->~Nave();
}






void Game::start()       /// metodo  que inicia  la libreria allegro
{
    int depth, res;
    allegro_init();
    depth = desktop_color_depth();
    if (depth == 0)
        depth = 32;
    set_color_depth(depth);
    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 600, 600, 0, 0);
    if (res != 0)
    {
        allegro_message(allegro_error);
        exit(-1);
    }

    install_timer();
    install_keyboard();
    install_mouse();

}

void Game::shutdown()          /// metodo para cerrar allegro
{
    clear_keybuf();
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_exit();
}
