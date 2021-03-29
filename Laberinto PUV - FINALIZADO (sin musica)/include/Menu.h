#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>


class Menu
{
    private:
        int _opcionSeleccionada;
        const int _MaxOpc = 5;
        sf::Font _fuente;
        sf::Text _menu[5];

    public:
        Menu(float width, float height);
        //virtual ~Menu();
        //void cmd();
        //void update();
        void draw(sf::RenderWindow &window);
        void MoveDown();
        void MoveUp();
        int getOpcSeleccionada(){ return _opcionSeleccionada; }
};

#endif // MENU_H
