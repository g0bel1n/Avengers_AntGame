//
// Created by g0bel1n on 23/01/2022.
//

#include "Food.h"
#pragma once
#include <math.h>


Food::Food(sf::Vector2<float> position) {

    this->position = position;
    graphic = sf::CircleShape(radius);
    graphic.setPosition(position);
    graphic.setFillColor(sf::Color::Red);
}

void Food::eaten() {
    graphic.setFillColor(sf::Color::Transparent);
    is_active=false;
}
