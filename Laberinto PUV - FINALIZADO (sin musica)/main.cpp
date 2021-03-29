#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>


#include "Personaje.h"
#include "Gameplay.h"
#include "Menu.h"

#include "Ranking.h"
#include "GUI.h"

#define MOSTRAR(x) std::cout << x << std::endl

enum EST{
    MENU,
    RANKING,
    CONTROLES,
    CREDITOS,
    AGRADECIMIENTOS
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(32*30, 32*20), "Laberinto PUV" , sf :: Style :: Default ); //960x640
    window.setKeyRepeatEnabled ( false ) ;
    window.setFramerateLimit(70);

    sf::Texture Background;
    Background.loadFromFile("imagenes\\Background.png");
    sf::RectangleShape BG;
    BG.setSize(sf::Vector2f( window.getSize().x, window.getSize().y ) );
    BG.setTexture(&Background);

    sf::Texture Controles;
    Controles.loadFromFile("imagenes\\Tutorial.png");
    sf::RectangleShape tuto;
    tuto.setSize(sf::Vector2f( window.getSize().x, window.getSize().y ) );
    tuto.setTexture(&Controles);

    sf::Texture Creditos;
    Creditos.loadFromFile("imagenes\\Creditos.png");
    sf::RectangleShape Cred;
    Cred.setSize(sf::Vector2f( window.getSize().x, window.getSize().y ) );
    Cred.setTexture(&Creditos);

    sf::Texture Agradecimientos;
    Agradecimientos.loadFromFile("imagenes\\Agradecimientos.png");
    sf::RectangleShape AG;
    AG.setSize(sf::Vector2f( window.getSize().x, window.getSize().y ) );
    AG.setTexture(&Agradecimientos);

    /*sf::Texture prueba;
    prueba.loadFromFile("imagenes\\TexturaLaberinto.png");
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(128,32));
    shape.setTexture(&prueba);
    shape.setPosition(200,200);*/
    Menu mp(window.getSize().x, window.getSize().y); ///Menu principal
    int estado = EST::MENU;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch( event.type )
            {
                case sf::Event::KeyPressed:
                    switch( event.key.code )
                    {
                    case sf::Keyboard::W:
                        mp.MoveUp();
                        break;
                    case sf::Keyboard::S:
                        mp.MoveDown();
                        break;
                    case sf::Keyboard::Return:
                        switch( mp.getOpcSeleccionada() )
                        {
                            case 0: ///jugar
                                {Gameplay gp;

                                gp.printJuego(window);

                                }
                                break;
                            case 1:  ///Ranking
                                estado = EST::RANKING;
                                {GUI gui;
                                Ranking obj;
                                    while( estado == EST::RANKING ){
                                        window.pollEvent(event);
                                        obj.extraerReg();
                                        gui.setRanking( obj.getJugadores() );

                                        window.clear();
                                        window.draw(BG);
                                        window.draw(gui.getMantitoprint());
                                        for(int i=0; i < 5 ; i++){
                                            window.draw(gui.getCartelRanking() );
                                            obj.Mostrar();
                                            gui.setRanking( obj.getJugadores() );
                                            window.draw(*(gui.getRankingPrint()+i) );
                                            }
                                        window.display();
                                        if( event.type == sf::Event::KeyPressed&& event.key.code == sf::Keyboard::Enter ) estado = EST::MENU;
                                    }
                                }
                                break;
                            case 2:  ///Controles
                                estado = EST::CONTROLES;
                                while( estado == EST::CONTROLES ){
                                        window.pollEvent(event);

                                        window.clear();
                                        window.draw(tuto);
                                        window.display();

                                        if( event.type == sf::Event::KeyPressed&& event.key.code == sf::Keyboard::Enter ) estado = EST::MENU;
                                    }
                                break;
                            case 3:  ///Creditos
                                estado = EST::CREDITOS;
                                while( estado == EST::CREDITOS ){
                                        window.pollEvent(event);

                                        window.clear();
                                        window.draw(Cred);
                                        window.display();

                                        if( event.type == sf::Event::KeyPressed&& event.key.code == sf::Keyboard::Enter ) estado = EST::AGRADECIMIENTOS;
                                    }
                                while( estado == EST::AGRADECIMIENTOS ){
                                        window.pollEvent(event);

                                        window.clear();
                                        window.draw(AG);
                                        window.display();

                                        if( event.type == sf::Event::KeyPressed&& event.key.code == sf::Keyboard::Enter ) estado = EST::MENU;
                                    }
                                break;
                            case 4:  ///Salir
                                window.close();
                                break;
                        }

                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
            /*if (event.type == sf::Event::KeyPressed)
                gp.AccessMovePJ();*/
        }

        //gp.setMap();


        window.clear();
        window.draw(BG); //pinta el fondo del menu
        mp.draw(window);
        //window.draw(gp.getMapprint());
        //window.draw(gp.getGemMapprint());
        //window.draw(gp.getPrintPERSONAJE());
        window.display();
    }

    return 0;
}
