//
// Created by g0bel1n on 09/12/2021.
//

#ifndef ANTS_FIGHT_CLUB_RENDERER_H
#define ANTS_FIGHT_CLUB_RENDERER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "World.h"

class Renderer {

public:

    Renderer(World& world);



    void update(World& world);


    std::vector<sf::CircleShape> markers_graphic;
    std::vector<sf::Sprite> ants_graphics;

    sf::Texture texture;

    sf::Texture texture_with_food;





};


#endif //ANTS_FIGHT_CLUB_RENDERER_H
