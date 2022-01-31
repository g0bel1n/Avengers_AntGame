//
// Created by g0bel1n on 08/12/2021.
//

#ifndef ANTS_FIGHT_CLUB_MARKER_H
#define ANTS_FIGHT_CLUB_MARKER_H

#pragma once

#include <SFML/Graphics.hpp>
#include "BaseElement.h"
#include "../parameters.h"

class Chunk;

class Marker : public BaseElement {

public:

    Marker(sf::Vector2<float> position, int state, Chunk *myChunk, float time_offset);

    float get_intensity();

    sf::CircleShape graphic;


    sf::Vector2<float> position;

    void update(sf::Time &dt) override;


private:

    Chunk *myChunk;
    float intensity;

    const sf::Color &color();
};


#endif //ANTS_FIGHT_CLUB_MARKER_H
