#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>
#include <iostream>

struct ESTADOS{
    bool
    QUIETO = true,
    CAMINANDODERECHA = false,
    CAMINANDOIZQUIERDA = false,
    CAMINANDOARRIBA = false,
    CAMINANDOABAJO = false;
};


class Personaje
{
    private:
    sf::RectangleShape _personaje;
    sf::Vector2i vecPos;
    sf::Texture _pjTexture;

    public:

        Personaje();
        sf::RectangleShape& getPersonaje();
        void SetQUIETO(); ///Estado quieto en true, todos los otros en false.
        void cmd();
        void update();
        ESTADOS estado;
        sf::Vector2i getVecPos();
        void setMovTexture();

};



#endif // PERSONAJE_H
