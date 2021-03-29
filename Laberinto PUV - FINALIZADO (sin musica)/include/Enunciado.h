
#ifndef ENUNCIADO_H
#define ENUNCIADO_H
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include "GUI.h"


class Enunciado
{
private:
    int _y;
    char _res[5][11]={ "30","0","3357","2","4" };
    char *_text;
    int _size;
    sf::String _trivias[5];
    sf::Text _enun[2];
    sf::Text _endTriv[3]; ///Correcto! tiempo agotado..! e Incorrecto!
    sf::Font _enunFont;
    bool estado;
    bool _endTrivia = false;
    int _id;
    bool idRandom;
    int correcto = -1; ///respuesta correcta (1), respuesta incorrecta (0), sin respuesta(-1)
    std::stringstream ss;
public:

    Enunciado();
    virtual ~Enunciado();
    bool getEstado();
    void abrirEnunVent(GUI* gui);
    void defaultTrivia();
    void addToCola(int);
    void removeFromCola(int);
    void validarResultado();
    void setPremio(int seg);
    void defaultTRIVIAS();
    void setEstado(bool est){ estado=est; }

    /// Sistema de colas (procesador de texto)

};



#endif // ENUNCIADO_H

