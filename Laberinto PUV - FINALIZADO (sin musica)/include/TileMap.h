#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include <iostream>


class TileMap : public sf::Drawable, public sf::Transformable
{
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    bool bandera = true;
    float intensidad = 255;
    void setDesvanecerGema(sf::Vertex* quad);
public:
    TileMap();
    ///Se crea un metodo el cual permimta definir/cargar las caracteristicas del mapa: textura o tileset, tamaño en pixeles
    /// de cada "tile", la matriz del nivel para ubicar cada tile segun corresponda el numerito, la anchura y la altura.
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, bool gemas=false);

};
#endif // TILEMAP_H
