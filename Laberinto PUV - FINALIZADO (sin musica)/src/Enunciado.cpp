#include "Enunciado.h"
#include <iostream>
#include <sstream>
#include <stdlib.h> ///Rand
#include <cstring>
#include <string.h>
#include <ctime>

#define MOSTRAR(x) std::cout << x << std::endl

#include "GUI.h"

Enunciado::Enunciado()
{
srand(time(NULL));
if (!_enunFont.loadFromFile("Fuente/POCKC.ttf") )
{
    MOSTRAR("ERROR AL CARGAR LA FUENTE");
}

estado = false;
_size = 0;
/*
_res [0] = '3';
_res [1] = '0';
_res [2] = '\0';
*/
 idRandom = true;
_id = 0; ///setRandomId();
_text = new char [10]; /// memoria se libera en el destructor.
defaultTRIVIAS();
defaultTrivia();
///setTriviaViaID();
///setResViaID();

}

Enunciado::~Enunciado()
{
    delete [] _text;
    //dtor
}

bool Enunciado::getEstado()
{
    return estado;
}

void Enunciado::abrirEnunVent(GUI* gui)
{
    if (getEstado() == true) ///Evento caja C++
    {
        sf::RenderWindow ventEnun(sf::VideoMode(600,400),"| ! |-TRIVIA DE LOGICA-| ! |");
        while (ventEnun.isOpen())
        {
            sf::Event eveEnun;
            while (ventEnun.pollEvent(eveEnun))
            {
                if (eveEnun.type == sf::Event::Closed)
                {
                estado = false;
                ventEnun.close();
                }

                //eveEnun.key.code.Enter
                if( !_endTrivia )
                {
                    if (eveEnun.type == sf::Event::TextEntered)
                    {
                        if(eveEnun.text.unicode != 8 && eveEnun.text.unicode != 13 )
                        {
                            addToCola(eveEnun.text.unicode);
                        }else if(eveEnun.text.unicode == 8 ){
                            removeFromCola(eveEnun.text.unicode);
                        }else{
                            validarResultado();
                            //ventEnun.close();
                        }//llave cierre del else.
                    }//llave de cierre IF
                }

                if( _endTrivia && (eveEnun.type == sf::Event::KeyPressed) && (eveEnun.key.code == sf::Keyboard::Enter) ){ ///para que se cierre presionando enter luego de finalizar la trivia.
                        MOSTRAR("entra");
                        if(correcto == 1) gui->setPremioSE();
                        estado=false;
                        ventEnun.close();
                }

            }
                if(!_endTrivia) estado = gui->setCrono(estado); ///set crono retorna false si el tiempo llega a 0.
                if(!estado) _endTrivia = true;

                if(idRandom){
                    _id = rand() % 5;
                    _enun->setString( _trivias[_id] );
                    idRandom = false;
                }
                ///setTrivia(texto);
                ventEnun.clear();
                ventEnun.draw(*_enun);
                ventEnun.draw(*(_enun+1));
                ventEnun.draw( *(gui->getCronoprint()+2));
                if(_endTrivia) ventEnun.draw( gui->getMantoprint() );

                if( _endTrivia && gui->getSegundosEnunciado() == 0){
                    gui->setDesvanecerText(_endTriv[1]);
                    ventEnun.draw( _endTriv[1] ); ///TExto "tiempo agotado"
                }else if (_endTrivia && correcto == 0){
                    gui->setDesvanecerText(_endTriv[2]);
                    ventEnun.draw( _endTriv[2] ); /// Texto "Incorrecto"
                }else if(_endTrivia && correcto == 1){
                    gui->setDesvanecerText(_endTriv[0]);
                    setPremio( gui->getSegundosEnunciado() );
                    ventEnun.draw( _endTriv[0] ); /// Texto "Correcto"
                }
                ventEnun.display();
        }
        idRandom = true;
        _endTrivia = false;
        ss.str(">> ");
        _enun[1].setString(">> ");
        _text[0] = '\0';
        _size = 0;
        gui->setSegundosIniciales(30);
        correcto = -1;
    }
}

void Enunciado::defaultTRIVIAS() ///contiene todos los posibles enunciados.
{
    _trivias[0] = "INT A = 5 ;\nINT B = 5 ;\nA = A + ( A * B ) ;\nCOUT << A ;\nQUE VALOR SE MUESTRA EN PANTALLA?";
    _trivias[1] = "INT A = 10, B = 100 ;\nFOR ( INT I = 0; I < 3; I ++ )\n{\nB += B * A * I;\n}\nCOUT << B % A ;\nQUE VALOR SE MUESTRA EN PANTALLA? ";
    _trivias[2] = "INT A = -3357 ;\nUNSIGNED INT B = A ; \nCOUT << B ;\nQUE VALOR SE MUESTRA EN PANTALLA?";
    _trivias[3] = "INT A ;\nFLOAT B = 2,7 ; A = B ;\nCOUT << A ;\nQUE VALOR SE MUESTRA EN PANTALLA?";
    _trivias[4] = "DADA UNA HERENCIA PUBLICA EN UNA CLASE\n1-SE PROHIBE LA MODIFICACION DE LOS METODOS DE LA CLASE RECEPTORA\n2-SE ME PROHIBE LA MODIFICACION DE LOS ATRIUTOS DE LA CLASE A HEREDAR\n3-DEBO MODIFICAR LOS ATRIBUTOS DE LA CLASE HEREDADA\n4-MUCHO TEXTO";


}

void Enunciado::defaultTrivia()
{
    _enun[0].setFont(_enunFont);
    sf::Color verde(51, 255, 0);
	_enun[0].setFillColor(verde);
	_enun[0].setPosition(sf::Vector2f(50,50));
    _enun[0].setString(_trivias[0]);

    _enun[1].setFont(_enunFont);
	_enun[1].setFillColor(verde);
	_enun[1].setPosition(sf::Vector2f(50,250));
	_enun[1].setString(">>  ");
	ss.str(" ");

	_endTriv[0].setFont(_enunFont);
	_endTriv[0].setFillColor(verde);
	_endTriv[0].setPosition(sf::Vector2f(200,300));
	_endTriv[0].setString(" ¡CORRECTO! ");

	_endTriv[1].setFont(_enunFont);
	_endTriv[1].setFillColor(verde);
	_endTriv[1].setPosition(sf::Vector2f(200,300));
	_endTriv[1].setString(" TIEMPO AGOTADO ");

	_endTriv[2].setFont(_enunFont);
	_endTriv[2].setFillColor(verde);
	_endTriv[2].setPosition(sf::Vector2f(200,300));
	_endTriv[2].setString(" INCORRECTO ");
}

void Enunciado::addToCola(int cod)
{
        if (_size < 10 )
    {
        if (_size == 0) {ss.str(""); ss<<">>  ";}

        _text[_size] = (char)cod;
        ss<<_text[_size];
        _size++;
        _text[_size] = '\0' ;
        _enun[1].setString( ss.str() );
    }

}


void Enunciado::removeFromCola(int cod) /// si cod es 8 remueve el ultimo dato de la cola
{
    ss.str("");
    if (cod == 8)
    {
        if (_size == 0)
        {
             ss.str(">>  ");
             _enun[1].setString( ss.str() );
            return;
        }
        _size--;
        _text[_size] = '\0';
        for(int i=0;i<=_size;i++) ///si el for se hacia < a _size, no entraba al for cuando el _size valia 0 luego de hacer el --
        {
            if( i == 0) ss<<">>  ";

            if( _text[i] != '\0' ) ss << _text[i]; /// se valida que no sea \0 la posicion, ya que imprimiria el caracter nulo porque recorre la ultima posicion.
        }
        _enun[1].setString( ss.str() );
    }
}


void Enunciado::validarResultado()
{
    if ( strcmp( _res[_id], _text ) == 0 )
    {
        correcto = 1; ///respuesta correcta
    }else{
        correcto = 0; ///respuesta incorrecta
        }
    _endTrivia=true;
}

void Enunciado::setPremio(int seg){
    ss.str("");
    ss<<"¡CORRECTO! +"<<seg<<" seg";
    _endTriv[0].setString(ss.str());
}

/*

void Enunciado::setRandomId(int)
{
    _id = rand() %3 +_y;

}
void Enunciado::addToCola(int cod)
{
    _kiwi[_size] = (char)cod;
    _size++;
}

void Enunciado::removeFromCola(int cod) /// si cod es 8 remueve el ultimo dato de la cola
{
    if (cod == 8)
    {
        if (_size == 0)
        {
            return;
        }
        _size--;
    }
}

void Enunciado::convertToString()
{
    triv.str("");
    for (int i=0;i<_size;i++)
    {
        triv << _kiwi[i];
    }
    _trivia.setString(triv.str());
}


void Enunciado::validarResultado()
{



    if (strcmp( _aRes , _aText ) )
    {
        MOSTRAR("Correcto!");
        setEstado(false);
        return;
    }
    triv.str("");
    triv.str("Error, intente de nuevo!");

}


void Enunciado::setResViaId()
{
    if (_id == 1)
    {
        _res.str("");
        _res.str("12");
    }
}
*/
