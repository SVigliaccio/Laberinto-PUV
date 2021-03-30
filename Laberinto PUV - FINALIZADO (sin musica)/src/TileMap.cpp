#include "TileMap.h"
#include <SFML/Graphics.hpp>
#include <iostream>

TileMap::TileMap()
{
    //ctor
}

    ///Se crea un metodo el cual permimta definir/cargar las caracteristicas del mapa: textura o tileset, tamaño en pixeles
    /// de cada "tile", la matriz del nivel para ubicar cada tile segun corresponda el numerito, la anchura y la altura.
bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, bool gemas)
{
        if (!m_tileset.loadFromFile(tileset)) return false;/// Si al intentar guardar la textura en m_tileset da error, retorna false.

        m_vertices.setPrimitiveType(sf::Quads); ///El tipo primitivo se declara como cuadrado (4 vertices).
        m_vertices.resize(width * height * 4); /// Cantidad total de vertices que hay en el mapa. Por eso 16*8*4 = 512(vertices).

        for (unsigned int i = 0; i < width; ++i) /// Recorre anchuras (filas, o posx)
            for (unsigned int j = 0; j < height; ++j) ///Recorre alturas (columnas, o posy)
            {

                int tileNumber = tiles[i + j * width];/// guarda el num del tile de la posicion que esten iterando los for.

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

                if(gemas && ( tileNumber == 5 || tileNumber == 8 || tileNumber == 11 ) ){
                setDesvanecerGema(quad);

                }
            }

    return true;
}


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }
void TileMap::setDesvanecerGema(sf::Vertex* quad){
    if(intensidad>=140 && intensidad<=255 && bandera == true){ ///Si la intensidad es menor a 5, se va por el else.
    intensidad-=5;
    }else{
    intensidad+=5; ///Cuando la intensidad es <15, viene por el else y coloca la bandera en false hasta que el valor sea de 255, ahi vuelve a entrar en la primera condicion del IF.
    bandera = false;
    if(intensidad==255){bandera=true;} ///si no se usa la bandera, una vez que llegue del 255 al 0, siempre va a estar iterando entre 5 y 0, entonces pareceria que nunca se vuelve a dibujar la gema.
    }
    sf::Color desvanecer(255, 255, 255, intensidad );
    quad[0].color = desvanecer;
    quad[1].color = desvanecer;
    //quad[2].color = desvanecer;
    //quad[3].color = desvanecer;
}
