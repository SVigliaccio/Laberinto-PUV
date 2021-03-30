#include "Personaje.h"

#include <SFML/Graphics.hpp>
#include <iostream>


Personaje::Personaje()
{
    _personaje.setSize(sf::Vector2f(32,32));
    _personaje.setPosition(sf::Vector2f(0,32));
    _pjTexture.loadFromFile("imagenes\\Enano.png"); /// 0 = EnanoIzquierda, 1 = EnanoDerecha, 2 = EnanoAbajo, 3 = EnanoArriba, 4 = EnanoFeliz
    _personaje.setTexture(&_pjTexture);
    _personaje.setTextureRect(sf::IntRect(32,0,32,32) );    /// 1era variable = posicion inicial X de recorte de Textura.
/// 2da variable = posicion inicial Y de refcorte de Textura.
/// 3ra y 4ta variable = cuanto de la textura se va a recortar.
}

sf::RectangleShape& Personaje::getPersonaje(){
    return _personaje;
}

void Personaje::cmd(){
    if(estado.QUIETO){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            estado.CAMINANDOIZQUIERDA = true;
            estado.QUIETO = false;
            return;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            estado.CAMINANDOARRIBA = true;
            estado.QUIETO = false;
            return;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            estado.CAMINANDODERECHA = true;
            estado.QUIETO = false;
            return;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            estado.CAMINANDOABAJO = true;
            estado.QUIETO = false;
            return;
        }
    }
}
void Personaje::SetQUIETO(){
    estado.QUIETO = true;
    estado.CAMINANDOARRIBA = false;
    estado.CAMINANDODERECHA = false;
    estado.CAMINANDOIZQUIERDA = false;
    estado.CAMINANDOABAJO = false;
}

void Personaje::update(){
    if(estado.QUIETO){
        _personaje.move(0,0);
    }
    if(estado.CAMINANDOARRIBA){
        _personaje.move(0,-32);
    }
    if(estado.CAMINANDOIZQUIERDA){
        _personaje.move(-32,0);
    }
    if(estado.CAMINANDODERECHA){
        _personaje.move(32,0);
    }
    if(estado.CAMINANDOABAJO){
        _personaje.move(0,32);
    }

    this->SetQUIETO();
}

void Personaje::setMovTexture(){
    if(estado.QUIETO || estado.CAMINANDOABAJO){ _personaje.setTextureRect(sf::IntRect(64,0,32,32) ); }
    if(estado.CAMINANDOARRIBA){ _personaje.setTextureRect(sf::IntRect(96,0,32,32) ); }
    if(estado.CAMINANDOIZQUIERDA){ _personaje.setTextureRect(sf::IntRect(0,0,32,32) ); }
    if(estado.CAMINANDODERECHA){ _personaje.setTextureRect(sf::IntRect(32,0,32,32) ); }
 }

sf::Vector2i Personaje::getVecPos(){
    this->vecPos.x = _personaje.getPosition().x/32;
    this->vecPos.y = _personaje.getPosition().y/32;
    return vecPos;
}
