#include "Gameplay.h"
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Personaje.h"
#include "TileMap.h"
#include <conio.h> ///PARA EL GETCH
#include "GUI.h"
#include "Ranking.h"
#include "Archivo.h"
#define MOSTRAR(x) std::cout << x << std::endl


int const levelwidth = 30, levelhight = 20;

int Oscuridad[600] = {}; /// nivel del mapa

int OscuridadDef[600] = {}; /// nivel del mapa

void Gameplay::iluminar(int x,int y)
{
    if ( pj.getVecPos().x+pj.getVecPos().y*levelwidth!=30 )
    {///Oscuridad[29] = 0;
        Oscuridad[x-1 + (y-1)*levelwidth] = 1; ///bloque arriba 2   |Van encerrados porque en pos 30 iluminan cosas no deseadas
        Oscuridad[x-1 + y*levelwidth] = 1;///bloque izquierda       |
        Oscuridad[x-1 + (y+1)*levelwidth] = 1;///bloque izquierda 2 |
    }
        Oscuridad[x + y*levelwidth] = 1; ///bloque actual
        Oscuridad[x+1 + y*levelwidth] = 1; ///bloque derecha
        Oscuridad[x+1 + (y-1)*levelwidth] = 1; ///bloque derecha 2
        Oscuridad[x + (y-1)*levelwidth] = 1; ///bloque arriba
        Oscuridad[x + (y+1)*levelwidth] = 1; ///bloque abajo
        Oscuridad[x+1 + (y+1)*levelwidth] = 1; ///bloque abajo 2
}

int const level[] =  /// nivel del mapa
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,
    1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,0,1,0,1,1,1,1,0,0,1,
    1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,1,1,0,0,1,0,0,0,0,1,0,1,1,
    1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,0,0,1,1,1,1,1,0,0,0,0,1,
    1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,
    1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,
    1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,1,1,1,0,1,0,1,

    1, 0, 1, 1, 1, 1, 1, 1, 0, 1,  0, 1, 1, 1, 1, 1, 0, 1, 0, 0,  1, 0, 1, 0, 0, 1, 0, 1, 0, 1,
    1, 1, 1, 0, 0, 0, 0, 0, 0, 1,  0, 1, 0, 0, 0, 1, 1, 1, 1, 0,  0, 0, 1, 1, 0, 1, 0, 1, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 0, 1, 1,  0, 0, 0, 1, 0, 0, 0, 0, 1, 0,  0, 1, 1, 0, 0, 1, 0, 1, 0, 1,
    1, 0, 1, 0, 0, 0, 1, 0, 0, 1,  1, 0, 1, 1, 1, 1, 1, 0, 1, 0,  1, 1, 0, 0, 0, 1, 0, 1, 0, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 0, 1,  0, 0, 0, 0, 0, 0, 1, 0, 1, 0,  1, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 0, 0, 1,  1, 1, 0, 1, 1, 1, 1, 0, 1, 0,  1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
    1, 0, 0, 1, 1, 1, 1, 1, 1, 1,  0, 0, 0, 1, 0, 0, 0, 0, 1, 0,  0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
    1, 1, 0, 1, 0, 0, 0, 1, 0, 0,  0, 1, 1, 1, 0, 1, 0, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 1,  0, 1, 0, 0, 0, 1, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
};

int gemas[] = /// 0 Vacio, 1 Piedra, 2 PRota, 3 PEsmeralda, 4 ERota, 5 Esmeralda, 6 PRuby, 7 RRota, 8 Ruby, 9 PZafiro, 10 ZRota, 11 Zafiro, 12 Win, 13 CajaC++
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1,  1, 3, 3, 0, 1, 1, 1, 1, 1, 0,  3, 1, 1, 1, 0, 6, 1, 1, 1, 3, 0,
    0, 0, 0, 3, 0, 1, 0, 0, 0, 0,  0, 0, 0, 1, 0, 1, 0, 9, 0, 0,  1, 0, 1, 0, 0, 0, 0, 3, 3, 0,
    0, 1, 1, 1, 0, 1, 1, 1, 1, 1,  0, 1, 1, 1, 0, 1, 0, 0, 0, 1,  1, 0, 1, 1, 13, 1, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 1, 0, 1, 0, 3,  0, 1, 0, 0, 0, 6, 0, 1, 1, 1,  0, 0, 0, 0, 0, 1, 1, 1, 3, 0,
    0, 6, 1, 3, 0, 1, 0, 1, 0, 3,  0, 1, 0, 1, 1, 6, 0, 1, 0, 1,  0, 9, 0, 6, 0, 3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 0, 0, 1, 0, 3,  0, 3, 3, 6, 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1, 1, 1, 0, 1, 1, 1,  0, 1, 0, 1, 1, 1, 1, 1, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 13, 0,  0, 13, 0, 1, 0, 0, 0, 0, 0, 6,  0, 1, 1, 3, 1, 1, 1, 0, 6, 0,
    0, 1, 1, 3, 1, 6, 9, 0, 1, 0,  3, 3, 0, 3, 0, 9, 3, 6, 1, 1,  0, 1, 0, 0, 0, 0, 3, 0, 3, 0,

    0, 9, 0, 0, 0, 0, 0, 0, 1, 0,  3, 0, 0, 0, 0, 0, 3, 0, 1, 1,  0, 1, 0, 9, 9, 0, 3, 0, 1, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 0,  1, 0, 1, 1, 1, 0, 0, 0, 0, 1,  1, 3, 0, 0, 3, 0, 1, 0, 1, 0,
    0, 1, 1, 1, 0, 0, 0, 1, 0, 0,  1, 1, 1, 0, 1, 1, 1, 1, 0, 3,  1, 0, 0, 6, 3, 0, 1, 0, 1, 0,
    0, 1, 0, 1, 6, 6, 0, 1, 1, 0,  0, 1, 0, 0, 0, 0, 0, 1, 0, 3,  0, 0, 3, 3, 3, 0, 3, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 3, 0,  1, 1, 1, 1, 1, 9, 0, 1, 0, 1,  0, 9, 3, 0, 3, 0, 6, 6, 13, 0,
    0, 1, 6, 0, 9, 6, 1, 1, 3, 0,  0, 0, 1, 0, 0, 0, 0, 3, 0, 1,  0, 0, 0, 0, 1, 0, 1, 0, 3, 0,
    0, 6, 6, 0, 0, 0, 0, 0, 0, 0,  1, 13, 1, 0, 1, 1, 3, 3, 0, 6,  1, 1, 1, 1, 1, 0, 1, 0, 3, 0,
    0, 0, 1, 0, 1, 1, 1, 0, 1, 1,  1, 0, 0, 0, 1, 0, 1, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 6, 1, 1, 3, 0, 1, 1, 3, 0,  1, 0, 9, 3, 1, 0, 1, 1, 1, 1,  1, 1, 3, 3, 6, 9, 9, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 12, 0,
};
int gemasDef[] = /// 0 Vacio, 1 Piedra, 2 PRota, 3 PEsmeralda, 4 ERota, 5 Esmeralda, 6 PRuby, 7 RRota, 8 Ruby, 9 PZafiro, 10 ZRota, 11 Zafiro, 12 Win, 13 CajaC++
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1,  1, 3, 3, 0, 1, 1, 1, 1, 1, 0,  3, 1, 1, 1, 0, 6, 1, 1, 1, 3, 0,
    0, 0, 0, 3, 0, 1, 0, 0, 0, 0,  0, 0, 0, 1, 0, 1, 0, 9, 0, 0,  1, 0, 1, 0, 0, 0, 0, 3, 3, 0,
    0, 1, 1, 1, 0, 1, 1, 1, 1, 1,  0, 1, 1, 1, 0, 1, 0, 0, 0, 1,  1, 0, 1, 1, 13, 1, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 1, 0, 1, 0, 3,  0, 1, 0, 0, 0, 6, 0, 1, 1, 1,  0, 0, 0, 0, 0, 1, 1, 1, 3, 0,
    0, 6, 1, 3, 0, 1, 0, 1, 0, 3,  0, 1, 0, 1, 1, 6, 0, 1, 0, 1,  0, 9, 0, 6, 0, 3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 0, 0, 1, 0, 3,  0, 3, 3, 6, 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1, 1, 1, 0, 1, 1, 1,  0, 1, 0, 1, 1, 1, 1, 1, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 13, 0,  0, 13, 0, 1, 0, 0, 0, 0, 0, 6,  0, 1, 1, 3, 1, 1, 1, 0, 6, 0,
    0, 1, 1, 3, 1, 6, 9, 0, 1, 0,  3, 3, 0, 3, 0, 9, 3, 6, 1, 1,  0, 1, 0, 0, 0, 0, 3, 0, 3, 0,

    0, 9, 0, 0, 0, 0, 0, 0, 1, 0,  3, 0, 0, 0, 0, 0, 3, 0, 1, 1,  0, 1, 0, 9, 9, 0, 3, 0, 1, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 0,  1, 0, 1, 1, 1, 0, 0, 0, 0, 1,  1, 3, 0, 0, 3, 0, 1, 0, 1, 0,
    0, 1, 1, 1, 0, 0, 0, 1, 0, 0,  1, 1, 1, 0, 1, 1, 1, 1, 0, 3,  1, 0, 0, 6, 3, 0, 1, 0, 1, 0,
    0, 1, 0, 1, 6, 6, 0, 1, 1, 0,  0, 1, 0, 0, 0, 0, 0, 1, 0, 3,  0, 0, 3, 3, 3, 0, 3, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 3, 0,  1, 1, 1, 1, 1, 9, 0, 1, 0, 1,  0, 9, 3, 0, 3, 0, 6, 6, 13, 0,
    0, 1, 6, 0, 9, 6, 1, 1, 3, 0,  0, 0, 1, 0, 0, 0, 0, 3, 0, 1,  0, 0, 0, 0, 1, 0, 1, 0, 3, 0,
    0, 6, 6, 0, 0, 0, 0, 0, 0, 0,  1, 13, 1, 0, 1, 1, 3, 3, 0, 6,  1, 1, 1, 1, 1, 0, 1, 0, 3, 0,
    0, 0, 1, 0, 1, 1, 1, 0, 1, 1,  1, 0, 0, 0, 1, 0, 1, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 6, 1, 1, 3, 0, 1, 1, 3, 0,  1, 0, 9, 3, 1, 0, 1, 1, 1, 1,  1, 1, 3, 3, 6, 9, 9, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 12, 0,
};

Gameplay::Gameplay()
{

    //Registro *padre = &obj;
    /*
    Archivo Rank("Ranking.dat",obj.getSize());
    Rank.CargarpRegistro(padre);
    Rank.defaultArchivo(5, padre);
    Rank.MostrarArchivo();*/

    obj.CargarpRegistro( &obj.getJugador() );
    obj.defaultArchivo( 5, &obj.getJugador() );
    //if(obj.defaultArchivo(5, &obj)) obj.extraerReg();


}

Gameplay::~Gameplay(){
std::copy(gemasDef, gemasDef + 600, gemas); /// copy (address del vector a volcar, espacios desplazados desde ese address, lugar a volcar.
std::copy(OscuridadDef, OscuridadDef + 600, Oscuridad);

}

void Gameplay::AccessMovePJ(){

    pj.cmd();
    pj.setMovTexture();
    checkcollisionPARED();
    pj.update();
}

sf::RectangleShape& Gameplay::getPrintPERSONAJE(){
    return pj.getPersonaje();
}

TileMap& Gameplay::getOscuridadprint()
{
    return _Oscuridad;
}

TileMap& Gameplay::getMapprint(){
    return _Map;
}

TileMap& Gameplay::getGemMapprint(){
    return _Gem;
}



int Gameplay::setMap(){

    if (!_Map.load("imagenes\\TexturaLaberinto.png", sf::Vector2u(32, 32), level, levelwidth, levelhight))
        return -1;
    if (!_Gem.load("imagenes\\Gemas.png", sf::Vector2u(32, 32), gemas, levelwidth, levelhight, true))
        return -1;
    if (!_Oscuridad.load("imagenes\\Oscuridad.png", sf::Vector2u(32, 32), Oscuridad, levelwidth, levelhight))
        return -1;
        else return 0;
}

void Gameplay::checkcollisionPARED(){

    sf::Vector2i PosPJ = pj.getVecPos();

    if(pj.estado.CAMINANDOABAJO){
        if(level[PosPJ.x + (PosPJ.y + 1) * levelwidth] == 1 || checkcollisionGEMAS(PosPJ,0,1) ){
            pj.estado.CAMINANDOABAJO = false;
            pj.estado.QUIETO = true;
            return;
        }
    }
    if(pj.estado.CAMINANDOARRIBA){
        if(level[PosPJ.x + (PosPJ.y - 1) * levelwidth] == 1 || checkcollisionGEMAS(PosPJ,0,-1) ){
        pj.estado.CAMINANDOARRIBA = false;
        pj.estado.QUIETO = true;
        return;
        }
    }
    if(pj.estado.CAMINANDODERECHA){
        if(level[(PosPJ.x + 1)+ PosPJ.y * levelwidth] == 1 || checkcollisionGEMAS(PosPJ,1) ){
        pj.estado.CAMINANDODERECHA = false;
        pj.estado.QUIETO = true;
        return;
        }
    }
    if(pj.estado.CAMINANDOIZQUIERDA){
        if(level[(PosPJ.x - 1) + PosPJ.y * levelwidth] == 1 || checkcollisionGEMAS(PosPJ,-1) ){
        pj.estado.CAMINANDOIZQUIERDA = false;
        pj.estado.QUIETO = true;
        return;
        }
    }
}

bool Gameplay::checkcollisionGEMAS(sf::Vector2i PosPJ, int x, int y){

    int tileNumberProx = gemas[(PosPJ.x+x) + (PosPJ.y+y) * levelwidth];
    //int tileNumberActual = gemas[ PosPJ.x + PosPJ.y * levelwidth];

    if(tileNumberProx == 1){ /// Piedra entera a píedra rota.
        gemas[(PosPJ.x+x) + (PosPJ.y+y) * levelwidth] = 2;
        return true;
    }
    if(tileNumberProx == 2){ /// Piedra rota a vacio.
        gemas[(PosPJ.x+x) + (PosPJ.y+y) * levelwidth] = 0;
        iluminar((PosPJ.x+x), (PosPJ.y+y));
        gui.setCantGEM(2); //Piedra rota
        return true;
    }

    if(tileNumberProx == 3){ /// PEsmeralda a PEsmeralda Rota.
        gemas[(PosPJ.x+x) + (PosPJ.y+y) * levelwidth] = 4;
        return true;
    }
    if(tileNumberProx == 4){ /// PEsmeralda Rota a Gema Esmeralda.
        gemas[(PosPJ.x+x) + (PosPJ.y+y) * levelwidth] = 5;
        iluminar((PosPJ.x+x),(PosPJ.y+y));
        return true;
    }
    if(tileNumberProx == 6){ /// PRuby a PRuby Rota.
        gemas[(PosPJ.x+x) + (PosPJ.y+y) * levelwidth] = 7;
        return true;
    }
    if(tileNumberProx == 7){ /// PRuby Rota a Gema Ruby.
        gemas[(PosPJ.x+x) + (PosPJ.y+y) * levelwidth] = 8;
        iluminar((PosPJ.x+x),(PosPJ.y+y));
        return true;
    }
    if(tileNumberProx == 9){ /// PZafiro a PZafiro Rota.
        gemas[(PosPJ.x+x) + (PosPJ.y+y) * levelwidth] = 10;
        return true;
    }
    if(tileNumberProx == 10){ /// PZafiro rota a Gema Zafiro .
        gemas[(PosPJ.x+x) + (PosPJ.y+y) * levelwidth] = 11;
        iluminar((PosPJ.x+x),(PosPJ.y+y));
        return true;
    }

    /// Coleccionador de gemas y destructor de piedra rota
    if(tileNumberProx == 5 || tileNumberProx == 8 || tileNumberProx == 11 || tileNumberProx == 13){ ///se usa el tilenumber prox y no actual porque se utiliza en chechcollison pared, donde entra al if anticipando el movimiento del personaje.

            switch(tileNumberProx)
            {
            case 5:
                gui.setCantGEM(5); //Esmeralda
                break;
            case 8:
                gui.setCantGEM(8); //Ruby
                break;
            case 11:
                gui.setCantGEM(11); //Zafiro
                break;
            case 13:
                enun.setEstado(true); //Trivia
                break;
            }
            if(tileNumberProx != 13) gemas[(PosPJ.x+x) + (PosPJ.y+y) * levelwidth] = 0; /// para que desaparezca la gema en cuanto estemos sobre su tile.
    }
    gemas[ PosPJ.x + PosPJ.y * levelwidth ] = 0; ///Para que desaparezca la gema luego de estar posicionada en su tile. Es para la trivia.
    return false;
}

void Gameplay::printJuego(sf::RenderWindow& window){
    bool salir=false;
    ///bool UnaVez = false;
    sf::Event event;
    do{
        iluminar(pj.getVecPos().x ,pj.getVecPos().y);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                    window.close();

            if(!_endGame && event.type == sf::Event::KeyPressed){ /// se mueve si endgame está en false.
                    AccessMovePJ(); /// chequea las colisiones para moverse.
            }else{
                ///Acciones en caso de que el juego esté finalizado.


                if (_endGame && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter){ ///sale al menu principal si apretas enter y el endgame está en true.
                        if(estado == ESTADO::volverAlMenu) salir=true;

                        if(!entroUnaVez ) { ///newrecord se pone en true, si al leer el archivo de ranking logra sustituir a alguno de los puestos.

                            if( gui.getGameOver() )
                            {
                                estado = ESTADO::ranking;
                            }else {estado = ESTADO::nuevoRecord;}
                            entroUnaVez = true;
                        }
                }

                if (estado == ESTADO::nuevoRecord && event.type == sf::Event::TextEntered)
                {
                                MOSTRAR("entro x2");
                                if(event.text.unicode != 8 && event.text.unicode != 13)
                                {
                                    gui.addToCola(event.text.unicode);
                                }else if(event.text.unicode == 8)
                                {
                                    gui.removeFromCola(event.text.unicode);
                                }
                                if (event.text.unicode == 13 )
                                {
                                    MOSTRAR("ENTER PRESSED");
                                    obj.Cargar( gui.getJugador(), gui.getPuntuacionTotal() );
                                    obj.extraerReg(); //compara y guarda el ranking de jugadores en un vector..
                                    gui.setRanking( obj.getJugadores() );
                                    estado = ESTADO::ranking;
                                }
                }
                if (estado == ESTADO::ranking && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                {
                                    estado = ESTADO::volverAlMenu;
                }

            } //llave de cierre ELSE

        }///FIN WHILE POLL EVENT



        if(!_endGame)
        {
            _endGame = gui.setCrono(); /// si el tiempo llega a 0, setCrono retorna true para finalizar el juego.
            if(_endGame) estado = ESTADO::tablaPuntos;
        }

        setMap();

        window.clear();

        window.draw(getMapprint());
        window.draw(getGemMapprint());
        window.draw(getOscuridadprint());
        window.draw(getPrintPERSONAJE());
        window.draw(gui.getBordeprint() );
        window.draw(*gui.getCronoprint() );

        for(int i=0; i <= gui.getPos() ; i++){
            window.draw(*(gui.getGemaPrintenBorde()+i) );
        }
        if(_endGame){ ///Pintar tabla de puntaje final
            window.draw(gui.getMantoprint() );
            window.draw(gui.getMantitoprint() );

            if(estado == ESTADO::tablaPuntos){
                for(int i=0; i < 5 ; i++){
                    if(i<4) window.draw(*(gui.getGematablaPrint()+i) );

                    window.draw(*(gui.getPTSgemasprint()+i) );
                }

                window.draw(*(gui.getCronoprint() + 1) ); ///pintar tiempo del final.
                //window.draw(*(gui.getPTSgemasprint()+i) );
                if(gui.getGameOver() ){
                    gui.setDesvanecerShape(gui.getGameOverprint() );
                    window.draw(gui.getGameOverprint() );
                }

            }

            /// es para chequear que funcione la mecanica del newrecord, luego se cambia la variable desde archivos.
            if(estado == ESTADO::nuevoRecord ){
              window.draw(gui.getNamae());
              window.draw(gui.getPedirNombre() );
            }

        }
        if(estado == ESTADO::ranking )
                {
                    MOSTRAR("RANKING");
                    obj.Mostrar(); //carga los registros del archivo en un vec.
                    gui.setRanking( obj.getJugadores() );
                    for(int i=0; i < 5 ; i++){
                    window.draw(gui.getCartelRanking() );
                    window.draw(*(gui.getRankingPrint()+i) );
                    }
                }
                MOSTRAR(estado);
        window.display();

        enun.abrirEnunVent( &gui );
        if(!_endGame) CheckEndGame();
     }while( !salir );

}

inline void Gameplay::CheckEndGame(){
    sf::Vector2i PosPJ = pj.getVecPos();
    /// si el actual es el bloque final, poner al metodo endGame en true.
    if(gemas[PosPJ.x + PosPJ.y * levelwidth] == 12 )
    {
        _endGame = true;
        estado = ESTADO::tablaPuntos;
    }
}


