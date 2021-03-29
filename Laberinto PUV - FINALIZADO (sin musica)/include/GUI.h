#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include<iostream>
#include<sstream>

#include "Ranking.h"
#include "Jugador.h"

class GUI
{
    private:
    ///RELOJ Y PUNTUACION
        sf::Font _gpFont;
        sf::Font _CrayonFont;

        ///RELOJ----------------------------------------------->
        sf::Text _cronoTxt[3]; /// Crono[0] del timer en la borda, crono[1] de la tabla de puntajes, crono[2] de la trivia.
        sf::Clock clock;

        std::stringstream ss, jugador, jugadores; ///Variable donde guardar el tiempo que va transcurriendo.
        int st=0 /**Segundos Trans*/, si = 1; /**Segundos iniciales*/
        int mi= 5; /** minutos iniciales*/
        int se = 30; ///Segundos enunciado
        //int ht=0 /**Horas Trans*/, hi = 0; /**horas iniciales*/
        //int mt=0; /**Minutos Trans*/
        int stAnt=st;
        ///BORDE----------------------------------------------->
        sf::Texture _BordeTexture, _gemTexture;
        sf::RectangleShape _Borde; /// hacerle get para pintar en gameplay.
        sf::RectangleShape *pGemas = NULL; ///Array dinamico, inicializado en el constructor
        int pos; ///Posicion para el array dinamico. Es para mostrar las gemas obtenidas en el borde.

        ///PUNTUACION FINAL---------------------------------------->
        sf::RectangleShape _manto, _mantito, _gema[4], _gameOVer;
        bool _gameOV = false;
        sf::Texture _gameOVerTexture;
        sf::Text _puntTxt[5]; ///0 ->Esmeralda, 2-> Ruby, 3->Zafiro, 4->piedra
        int _cantEsmeralda, _cantRuby, _cantZafiro,_cantPiedra;
        int puntosE = 0, puntosR = 0, puntosZ = 0, puntosC = 0;
        float _puntuacionTotal=0, puntosP = 0;
        bool bandera = true;
        int intensidad = 255;
        //sf::Color desvanecer(255, 255, 255, 255);

        // las variables m y s que contienen el tiempo transcurrido hay que sumar los puntos al final.
        ///Ranking
        char _text[10];
        int _size=0;
        sf::Text _jugador;
        sf::Text _jugadores[5];
        sf::Text _cartelRanking;
        sf::Text _namae;

    public:
        GUI();

        ///RELOJ----------------------------------------------->
        void defaultCrono();
        bool setCrono(bool Enun = false);
        sf::Text* getCronoprint(){ return _cronoTxt; }

        ///BORDE----------------------------------------------->
        void setBorde();
        sf::RectangleShape& getBordeprint(){ return _Borde; }

        void defaultGema();
        void setCantGEM(int tipoGema);
        sf::RectangleShape* getGemaPrintenBorde(){ return pGemas; }
        int getPos(){ return pos; }

        ///PUNTUACION FINAL---------------------------------------->
        void defaultPuntuacion(); ///Metodo que setea los parametros de inicio para los textos de la tabla final (esmeralda, rubi, zafiro y piedra)
        void setPuntuacionTotal(); /// setea el total de puntos mostrados en la tabla final (en la variable priv _puntuacionTotal)
        float getPuntuacionTotal(){return _puntuacionTotal;} /// luego eliminar metodo, es para probar si funciona el new record!!!!
        //sf::Text* getPuntprint(){ return _puntTxt; }
        void defaultManto();
        sf::RectangleShape& getMantoprint(){ return _manto; }
        sf::RectangleShape& getMantitoprint(){ return _mantito; }
        sf::RectangleShape* getGematablaPrint(){ return _gema; }
        sf::Text* getPTSgemasprint(){ setPTSGema(); setPuntuacionTotal(); return _puntTxt; }
        void setPTSGema();
        void setPTSCrono();
        sf::RectangleShape& getGameOverprint(){ return _gameOVer; }
        bool getGameOver(){ /*_gameOV = ( si == 0 && mi == 0 )? _gameOV = true : _gameOV = false;*/
            if(si == 0 && mi == 0) return true;

             return false; }
        void defaultGameOver();
        void setDesvanecerShape(sf::RectangleShape& shape);
        ///ENUNCIADO
        void setDesvanecerText(sf::Text& text);
        int getSegundosEnunciado(){ return se;}
        void setSegundosIniciales(int seg ){ se = seg; }
        void setPremioSE();

        ///RANKING
        void addToCola(int);
        void removeFromCola(int);
        sf::Text& getPedirNombre(){ return _jugador; }
        const char* getJugador(){return _text;}
        void defaultRanking();
        void setRanking( Jugador *VecArchivo); ///primero recibe el vector con el ranking a pintar y se transforma a Text
        sf::Text* getRankingPrint(){ return _jugadores; } ///luego se retorna el text para pintar el ranking.
        sf::Text& getCartelRanking(){ return _cartelRanking; }
        sf::Text& getNamae(){ return _namae;}


};

#endif // GUI_H
