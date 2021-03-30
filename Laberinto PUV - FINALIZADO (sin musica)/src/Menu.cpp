#include "Menu.h"

#include <SFML/Graphics.hpp>
#include <iostream>

Menu::Menu(float width, float height)
{
    if (!_fuente.loadFromFile("Fuente\\Black Crayon.ttf"))
	{
		///error al abrir la fuente
	}
    int tam = 50;
    int tamExtra = 60;
	_menu[0].setFont(_fuente);
	_menu[0].setFillColor(sf::Color::Red);
	_menu[0].setCharacterSize(tam);
	_menu[0].setString("Jugar");
	_menu[0].setPosition(sf::Vector2f( (width / 2 ) - (_menu[0].getGlobalBounds().width/2) - 20, height / 5 )); //height = 640

	_menu[1].setFont(_fuente);
	_menu[1].setFillColor(sf::Color::White);
	_menu[1].setCharacterSize(tam);
	_menu[1].setString("Ranking");
	_menu[1].setPosition(sf::Vector2f( _menu[0].getPosition().x, _menu[0].getPosition().y + tamExtra ));

	_menu[2].setFont(_fuente);
	_menu[2].setFillColor(sf::Color::White);
	_menu[2].setCharacterSize(tam);
	_menu[2].setString("Controles");
	_menu[2].setPosition(sf::Vector2f(_menu[0].getPosition().x, _menu[1].getPosition().y + tamExtra ));

	_menu[3].setFont(_fuente);
	_menu[3].setFillColor(sf::Color::White);
	_menu[3].setCharacterSize(tam);
	_menu[3].setString("Creditos");
	_menu[3].setPosition(sf::Vector2f(_menu[0].getPosition().x, _menu[2].getPosition().y + tamExtra ));

	_menu[4].setFont(_fuente);
	_menu[4].setFillColor(sf::Color::White);
	_menu[4].setCharacterSize(tam);
	_menu[4].setString("Salir");
	_menu[4].setPosition(sf::Vector2f(_menu[0].getPosition().x, _menu[3].getPosition().y + 100 ));

	_opcionSeleccionada = 0;
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < _MaxOpc; i++)
	{
		window.draw(_menu[i]);
	}
}

void Menu::MoveUp()
{
	if (_opcionSeleccionada - 1 >= 0)
	{
		_menu[_opcionSeleccionada].setFillColor(sf::Color::White);
		_opcionSeleccionada--;
		_menu[_opcionSeleccionada].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (_opcionSeleccionada + 1 < _MaxOpc)
	{
		_menu[_opcionSeleccionada].setFillColor(sf::Color::White);
		_opcionSeleccionada++;
		_menu[_opcionSeleccionada].setFillColor(sf::Color::Red);
	}
}
