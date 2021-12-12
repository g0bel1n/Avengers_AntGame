//
// Created by g0bel1n on 12/12/2021.
//

#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f position, float length) {


    graphics = sf::VertexArray (sf::Quads, 4);

    graphics[0].position = position;
    graphics[1].position = position + sf::Vector2f (length,0.);
    graphics[2].position = position + sf::Vector2f (length,length);
    graphics[3].position = position + sf::Vector2f (0.,length);

    graphics[0].texCoords = sf::Vector2f (0.,0.);
    graphics[1].texCoords = sf::Vector2f (length,0.);
    graphics[2].texCoords = sf::Vector2f (length,length);
    graphics[3].texCoords =  sf::Vector2f (0.,length);

}
