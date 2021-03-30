#include "GUI.h"

#include <SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
#define MOSTRAR(x) std::cout << x << std::endl
#include<stdlib.h>

#include "Ranking.h"
#include "Jugador.h"


GUI::GUI()
{
    srand(time(NULL));

    _puntuacionTotal = 0;

    clock.restart();
    if (!_gpFont.loadFromFile("Fuente\\arial.ttf"))
	{
		//MOSTRAR("error al abrir la fuente");
	}
	_CrayonFont.loadFromFile("Fuente\\Black Crayon.ttf");

	_jugador.setFont(_CrayonFont);
	_jugador.setCharacterSize(35);
	_jugador.setFillColor(sf::Color::White);
	_jugador.setPosition(320, 300);
	_jugador.setString("");

    _namae.setFont(_CrayonFont);
	_namae.setCharacterSize(28);
	_namae.setFillColor(sf::Color::White);
	_namae.setPosition(350, 210);
	_namae.setString("  ¡ FELICIDADES ! \n¡ Escribe tu nombre !");

	defaultManto();
	defaultGameOver();
	defaultGema();
	defaultPuntuacion();
	setPTSGema();
	defaultCrono();
	setBorde();
	defaultRanking();

}

void GUI::defaultPuntuacion()
{
    ///texto informativo de la esmeralda
	_puntTxt[0].setFont(_gpFont);
    _puntTxt[0].setFillColor(sf::Color::White);
    _puntTxt[0].setCharacterSize(16);
    _puntTxt[0].setString(" ");
    _puntTxt[0].setOrigin(sf::Vector2f( 0, _puntTxt[0].getGlobalBounds().height/ 2.f ) );
    _puntTxt[0].setPosition(sf::Vector2f( _gema[0].getPosition().x + _gema[0].getGlobalBounds().width - 5, _gema[0].getPosition().y + ( _gema[0].getGlobalBounds().height/6.f ) ));

    ///texto informativo del rubi
    _puntTxt[1].setFont(_gpFont);
    _puntTxt[1].setFillColor(sf::Color::White);
    _puntTxt[1].setCharacterSize(16);
    _puntTxt[1].setString(" ");
    _puntTxt[1].setOrigin(sf::Vector2f( 0, _puntTxt[1].getGlobalBounds().height/ 2.f ) );
    _puntTxt[1].setPosition(sf::Vector2f( _gema[1].getPosition().x + _gema[1].getGlobalBounds().width - 5, _gema[1].getPosition().y + ( _gema[1].getGlobalBounds().height/6.f ) ));

    ///texto informativo del zafiro
    _puntTxt[2].setFont(_gpFont);
    _puntTxt[2].setFillColor(sf::Color::White);
    _puntTxt[2].setCharacterSize(16);
    _puntTxt[2].setString(" ");
    _puntTxt[2].setOrigin(sf::Vector2f( 0, _puntTxt[2].getGlobalBounds().height/ 2.f ) );
    _puntTxt[2].setPosition(sf::Vector2f( _gema[2].getPosition().x + _gema[2].getGlobalBounds().width - 5, _gema[2].getPosition().y + ( _gema[2].getGlobalBounds().height/6.f ) ));

    ///texto informativo de la piedra
    _puntTxt[3].setFont(_gpFont);
    _puntTxt[3].setFillColor(sf::Color::White);
    _puntTxt[3].setCharacterSize(16);
    _puntTxt[3].setString(" ");
    _puntTxt[3].setOrigin(sf::Vector2f( 0, _puntTxt[3].getGlobalBounds().height/ 2.f ) );
    _puntTxt[3].setPosition(sf::Vector2f( _gema[3].getPosition().x + _gema[3].getGlobalBounds().width + 2, _gema[3].getPosition().y ));

    ///texto informativo para crono seteado en metodo defaultCrono();

    ///Texto informativo para puntuacion total
    _puntTxt[4].setFont(_gpFont);
    _puntTxt[4].setFillColor(sf::Color::White);
    _puntTxt[4].setCharacterSize(32);
    _puntTxt[4].setString(" ");
   // _puntTxt[4].setOrigin(sf::Vector2f( (float) _puntTxt[4].getGlobalBounds().width/ 2.f, (float)_puntTxt[4].getGlobalBounds().height/ 2.f ) );
    _puntTxt[4].setPosition(sf::Vector2f( _mantito.getPosition().x + 100, _gema[3].getPosition().y +96)); ///es +64 porque el +32 ya lo ocupa el crono.


    /*_puntTxt[1].setFont(_gpFont);
    _puntTxt[1].setFillColor(sf::Color::White);
    _puntTxt[1].setString(std::to_string(_puntuacion));///(char)_puntuacion
    _puntTxt[1].setPosition(sf::Vector2f( _puntTxt[0].getPosition().x+_puntTxt[0].getGlobalBounds().width, 0 )); ///con getglobanbounds.width obtenemos el ancho del string Puntuacion.
    _puntTxt[1].setCharacterSize(20);*/
}

bool GUI::setCrono(bool Enun)
{

    ss.str(""); ///el string se setea a "" para volver a rellenarlo con el tiempo actualizado.
    sf::Time t;
    t = clock.getElapsedTime();
    st = t.asSeconds();

    if(Enun){
    ///segundos transcurridos en ENUNCIADO.
        if(stAnt!=st){
            stAnt = st;
        if( se == 0 ) return false; ///estado = false (de enunciado), para que finalice la trivia por falta de tiempo.
            se -= 1;
        }

        ///segundos en curso.
        ss<<"00";
        if(se<10)
        {
            ss<<":"<<"0"<<se;
        }
        else
        {
            ss<<":"<<se;
        }

    _cronoTxt[2].setString(ss.str());
    return true;///no finalice la ventana de enun. :D porque aun hay tiempo
    }else{
        ///segundos, horas y minutos transcurridos.
    /*mt = st/5;
    st = st-mt*5;
    */
    if(stAnt!=st){
        stAnt = st;
        if( si == 0 && mi == 0) return true; ///endgame = true, para que finalice el juego por falta de tiempo.
        if( (si - 1) < 0 )
        {
            si = 59;

            if( !( (mi-1) < 0 ) ) mi--;

        }else{ si -= 1; }
    }

    /*if(h<10)
        {
          ss<<"0"<<h;
        }
        else
        {
           ss<<h;
        }*/
        ///Minutos y segundos iniciales / en curso.
        if(mi<10)
        {
            ss<<"0"<<mi;
        }
        else
        {
            ss<<mi;
        }
        if(si<10)
        {
            ss<<":"<<"0"<<si;
        }
        else
        {
            ss<<":"<<si;
        }

    _cronoTxt[0].setString(ss.str());
    setPTSCrono(); /// se setea acá los pts de la tabla final para que utilice el ss.str que guarda el reloj, sino luego se resetea la variable.

    return false; /// _endgame = false, para que no finalice el juego.
    }


}
void GUI::setPremioSE(){

    if( (si+se)<60 ) {
        si += se;
    }else{
       mi += (si+se) / 60;
       si = (si+se) % 60;
    }
}

void GUI::defaultCrono(){ ///modificado en setPTScrono(), y llamado en metodo setCrono();
    _cronoTxt[0].setFont(_gpFont); ///crono del juego en la borda marron.
    _cronoTxt[0].setCharacterSize(16);
    _cronoTxt[0].setFillColor(sf::Color::White);
    _cronoTxt[0].setString(" ");
    _cronoTxt[0].setPosition(sf::Vector2f(460,0));

    _cronoTxt[1].setFont(_gpFont); ///crono de la tabla de puntajes
    _cronoTxt[1].setCharacterSize(18);
    _cronoTxt[1].setFillColor(sf::Color::White);
    _cronoTxt[1].setString(" ");
    _cronoTxt[1].setOrigin(sf::Vector2f( 0, _cronoTxt[1].getGlobalBounds().height/ 2.f ) );
    _cronoTxt[1].setPosition(sf::Vector2f( _gema[3].getPosition().x, _gema[3].getPosition().y + 32 ));

    _cronoTxt[2].setFont(_gpFont); ///crono de la trivia
    _cronoTxt[2].setCharacterSize(18);
    _cronoTxt[2].setFillColor(sf::Color::White);
    _cronoTxt[2].setString(" ");
    _cronoTxt[2].setOrigin(sf::Vector2f( 0, _cronoTxt[2].getGlobalBounds().height/ 2.f ) );
    _cronoTxt[2].setPosition(sf::Vector2f( 300, 0 )); /// teniendo en cuenta el tamaño de ventana de enun
}

void GUI::defaultGema(){
    pGemas = new sf::RectangleShape [86]; /// reservo memoria para 85 gemas ya que es el MAX que el pj puede recoger.

    _cantEsmeralda = 0, _cantRuby = 0, _cantZafiro = 0, _cantPiedra = 0, pos = 0;

    if (!_gemTexture.loadFromFile("imagenes\\Gemas.png"))
	{
		MOSTRAR("error al abrir archivo gemas");
	}
	pGemas[pos].setSize(sf::Vector2f(25,25));
	pGemas[pos].setTexture(&_gemTexture);
	pGemas[pos].setTextureRect(sf::IntRect(0,0,32,32) );
	pGemas[pos].setPosition(sf::Vector2f(210,0));

	///GEMAS para mostrar en el resultado final
	_gema[0].setSize(sf::Vector2f(32,32));
	_gema[0].setTexture(&_gemTexture);
	_gema[0].setTextureRect(sf::IntRect(160,0,32,32) ); ///ESMERALDA
	_gema[0].setPosition(sf::Vector2f(_mantito.getPosition().x+32, _mantito.getPosition().y+32));

	_gema[1].setSize(sf::Vector2f(32,32));
	_gema[1].setTexture(&_gemTexture);
	_gema[1].setTextureRect(sf::IntRect(256,0,32,32) ); ///RUBY
	_gema[1].setPosition(sf::Vector2f(_gema[0].getPosition().x, _gema[0].getPosition().y + 32));

    _gema[2].setSize(sf::Vector2f(32,32));
	_gema[2].setTexture(&_gemTexture);
	_gema[2].setTextureRect(sf::IntRect(352,0,32,32) ); ///ZAFIRO
	_gema[2].setPosition(sf::Vector2f(_gema[1].getPosition().x, _gema[1].getPosition().y + 32));

	_gema[3].setSize(sf::Vector2f(20,20));
	_gema[3].setTexture(&_gemTexture);
	_gema[3].setTextureRect(sf::IntRect(32,0,32,32) ); ///Piedra
	_gema[3].setPosition(sf::Vector2f(_gema[2].getPosition().x+5, _gema[2].getPosition().y + 37));

}

void GUI::setPTSGema(){
    puntosE = 5*_cantEsmeralda, puntosR = 15*_cantRuby, puntosZ = 25*_cantZafiro;
    puntosP = 0.5*(float)_cantPiedra;
    ss.str("");
    ss<<" x "<<_cantEsmeralda<<"  . . .   . . .   . . .   . . .   . . .   . . .   . . .   . . .   +"<<puntosE<<" pts";
    _puntTxt[0].setString(ss.str() ); ///Esmeralda

    ss.str("");
    ss<<" x "<<_cantRuby<<"  . . .   . . .   . . .   . . .   . . .   . . .   . . .   . . .   +"<<puntosR<<" pts";
    _puntTxt[1].setString(ss.str() ); ///Rubi

    ss.str("");
    ss<<" x "<<_cantZafiro<<"  . . .   . . .   . . .   . . .   . . .   . . .   . . .   . . .   +"<<puntosZ<<" pts";
    _puntTxt[2].setString(ss.str() ); ///Zafiro

    ss.str("");
    ss<<" x "<<_cantPiedra<<"  . . .   . . .   . . .   . . .   . . .   . . .   . . .   . . .   +"<<puntosP<<" pts";
    _puntTxt[3].setString(ss.str() ); ///Piedra

}

void GUI::setPTSCrono(){
    ///La variable ss ya tiene asignado el timer, no viene vacia. (metodo llamado en setCrono() )
    puntosC = ( mi*60 ) + si;
    ss<<"  . . .   . . .   . . .   . . .   . . .   . . .   . . .   +"<<puntosC<<" pts";
    _cronoTxt[1].setString(ss.str() ); ///Crono de la tabla de puntajes.

}

void GUI::setPuntuacionTotal(){
    _puntuacionTotal = puntosE+puntosP+puntosR+puntosZ+puntosC;
    ss.str("");
    ss<<" TOTAL "<<_puntuacionTotal<<" pts";
    _puntTxt[4].setString(ss.str() );
}

void GUI::setBorde(){
    _BordeTexture.loadFromFile("imagenes\\Borda.png");
    _Borde.setSize(sf::Vector2f(580,32));
    _Borde.setPosition(sf::Vector2f(190,0));
    _Borde.setTexture(&_BordeTexture);
}

void GUI::setCantGEM(int tipoGema){
    if(tipoGema != 2){
        pos++;
        pGemas[pos].setSize(sf::Vector2f(25,25));
        pGemas[pos].setTexture(&_gemTexture);
        switch(tipoGema)
                {
                case 5:
                     _cantEsmeralda++;//Esmeralda
                     pGemas[pos].setTextureRect(sf::IntRect(160,0,32,32) );
                    break;
                case 8:
                     _cantRuby++;//Ruby
                     pGemas[pos].setTextureRect(sf::IntRect(256,0,32,32) );
                    break;
                case 11:
                     _cantZafiro++;//Zafiro
                     pGemas[pos].setTextureRect(sf::IntRect(352,0,32,32) );
                    break;
                }
        if(pos==44){ /// para que la cant de gemas no pisen el tiempo
            pGemas[pos].setPosition( sf::Vector2f(_cronoTxt[0].getPosition().x + _cronoTxt[0].getGlobalBounds().width + 15, 0) );
        }else{
            pGemas[pos].setPosition( sf::Vector2f(pGemas[pos-1].getPosition().x + 5, 0) );
        }

    }else{_cantPiedra++;} //Piedra rota
}

void GUI::defaultManto(){
    sf::Color finalfondo(0,0,0,200);
    sf::Color opaco(0,0,0,230);
    sf::Color borde(0,0,0,130);

    _manto.setSize(sf::Vector2f( 960, 640 ));
    _manto.setFillColor(finalfondo);
    _manto.setPosition(sf::Vector2f( 0, 0 ));

    _mantito.setSize(sf::Vector2f( 480, 320 ));
    _mantito.setFillColor(opaco);
    _mantito.setPosition(sf::Vector2f( 240, 160 ));
    _mantito.setOutlineThickness(30.f);
    _mantito.setOutlineColor(borde);
}

void GUI::defaultGameOver(){
    if (!_gameOVerTexture.loadFromFile("imagenes\\Gameoverr.png"))
	{
		//MOSTRAR("error al abrir la fuente");
	}
    _gameOVer.setTexture(&_gameOVerTexture);
    _gameOVer.setSize(sf::Vector2f(512*1.50,124*1.50));
    _gameOVer.setOrigin(sf::Vector2f( _gameOVer.getSize().x/2.f, _gameOVer.getSize().y/2.f ) );
    _gameOVer.setRotation(30.f);
    _gameOVer.setPosition(sf::Vector2f(_mantito.getSize().x/2.f + _mantito.getPosition().x , _mantito.getSize().y/2.f + _mantito.getPosition().y) );

}

void GUI::setDesvanecerShape(sf::RectangleShape& shape){

    ///Va en la iteracion de la ventana, para desvanecer textura (podria ser funcion recursiva)
    if(intensidad>=5 && intensidad<=255 && bandera == true){ ///Si la intensidad es menor a 5, se va por el else.
    intensidad-=5;
    }else{
    intensidad+=5; ///Cuando la intensidad es 0, viene por el else y coloca la bandera en false hasta que el valor sea de 255, ahi vuelve a entrar en la primera condicion del IF.
    bandera = false;
    if(intensidad==255){bandera=true;} ///si no se usa la bandera, una vez que llegue del 255 al 0, siempre va a estar iterando entre 5 y 0, entonces pareceria que nunca se vuelve a dibujar el sello.
    }
    sf::Color desvanecer(255, 255, 255, intensidad);
    shape.setFillColor(desvanecer);
}

void GUI::setDesvanecerText(sf::Text& text){ ///Fijarse si el metodo no puede devolver el color, asi no se duplican metodos.
    if(intensidad>=5 && intensidad<=255 && bandera == true){ ///Si la intensidad es menor a 5, se va por el else.
    intensidad-=5;
    }else{
    intensidad+=5; ///Cuando la intensidad es 0, viene por el else y coloca la bandera en false hasta que el valor sea de 255, ahi vuelve a entrar en la primera condicion del IF.
    bandera = false;
    if(intensidad==255){bandera=true;} ///si no se usa la bandera, una vez que llegue del 255 al 0, siempre va a estar iterando entre 5 y 0, entonces pareceria que nunca se vuelve a dibujar el sello.
    }
    sf::Color desvanecer(80, 255, 0, intensidad);
    text.setFillColor(desvanecer);
}

void GUI::addToCola(int cod)
{

        if (_size < 10 )
    {
        if (_size == 0) {jugador.str(""); jugador<<">>  ";}

        _text[_size] = (char)cod;
        jugador<<_text[_size];
        _size++;
        _text[_size] = '\0' ;
        _jugador.setString( jugador.str() );
    }

}

void GUI::removeFromCola(int cod) /// si cod es 8 remueve el ultimo dato de la cola
{
    jugador.str("");
    if (cod == 8)
    {
        if (_size == 0)
        {
             jugador.str(">>  ");
             _jugador.setString( jugador.str() );
            return;
        }
        _size--;
        _text[_size] = '\0';
        for(int i=0;i<=_size;i++) ///si el for se hacia < a _size, no entraba al for cuando el _size valia 0 luego de hacer el --
        {
            if( i == 0) jugador<<">>  ";

            if( _text[i] != '\0' ) jugador << _text[i]; /// se valida que no sea \0 la posicion, ya que imprimiria el caracter nulo porque recorre la ultima posicion.
        }
        _jugador.setString( jugador.str() );
    }
}

void GUI::setRanking( Jugador *VecArchivo ){

    for(int i=0; i<5; i++)
        {
            jugadores.str("");
            jugadores<<VecArchivo[i].nombre<<".   .   .   .   .   .   .   .   ."<<VecArchivo[i].ptsTOTAL<<" pts";
            _jugadores[i].setString(jugadores.str() );
        }
}

void GUI::defaultRanking(){
    _cartelRanking.setFont(_CrayonFont);
    _cartelRanking.setFillColor(sf::Color::White);
    _cartelRanking.setCharacterSize(32);
    _cartelRanking.setString("RANKING");
    _cartelRanking.setPosition(sf::Vector2f( _mantito.getPosition().x + _mantito.getGlobalBounds().width/4 + 30, _mantito.getPosition().y + 4) );
    ///primer puesto
	_jugadores[0].setFont(_CrayonFont);
    _jugadores[0].setFillColor(sf::Color::White);
    _jugadores[0].setCharacterSize(24);
    _jugadores[0].setString(" ");
    _jugadores[0].setPosition(sf::Vector2f( _mantito.getPosition().x+20, _mantito.getPosition().y + 80) );

    ///segundo puesto
    _jugadores[1].setFont(_CrayonFont);
    _jugadores[1].setFillColor(sf::Color::White);
    _jugadores[1].setCharacterSize(24);
    _jugadores[1].setString(" ");
    _jugadores[1].setPosition(sf::Vector2f(_jugadores[0].getPosition().x, _jugadores[0].getCharacterSize() + _jugadores[0].getPosition().y + 16 ));

    ///tercer puesto
    _jugadores[2].setFont(_CrayonFont);
    _jugadores[2].setFillColor(sf::Color::White);
    _jugadores[2].setCharacterSize(24);
    _jugadores[2].setString(" ");
    _jugadores[2].setPosition(sf::Vector2f( _jugadores[1].getPosition().x, _jugadores[0].getCharacterSize() + _jugadores[1].getPosition().y + 16 ));

    ///cuarto puesto
    _jugadores[3].setFont(_CrayonFont);
    _jugadores[3].setFillColor(sf::Color::White);
    _jugadores[3].setCharacterSize(24);
    _jugadores[3].setString(" ");
    _jugadores[3].setPosition(sf::Vector2f(  _jugadores[2].getPosition().x, _jugadores[0].getCharacterSize() + _jugadores[2].getPosition().y + 16 ));

    ///quinto puesto
    _jugadores[4].setFont(_CrayonFont);
    _jugadores[4].setFillColor(sf::Color::White);
    _jugadores[4].setCharacterSize(24);
    _jugadores[4].setString(" ");
    _jugadores[4].setPosition(sf::Vector2f( _jugadores[3].getPosition().x, _jugadores[0].getCharacterSize() + _jugadores[3].getPosition().y + 16 ));

}

