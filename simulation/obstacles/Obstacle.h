//
// Created by g0bel1n on 12/12/2021.
//

#ifndef ANTS_FIGHT_CLUB_OBSTACLE_H
#define ANTS_FIGHT_CLUB_OBSTACLE_H
#include <SFML/Graphics.hpp>

class Obstacle {

public:

    Obstacle(sf::Vector2f position, float lenght);
    sf::VertexArray graphics;
    sf::Texture texture;

};


#endif //ANTS_FIGHT_CLUB_OBSTACLE_H
