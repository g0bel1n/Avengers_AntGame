//
// Created by g0bel1n on 29/01/2022.
//

#include "Food.h"
#include "../parameters.h"

using namespace parameters;

Food::Food(sf::Vector2<float> position) {

    this->position = position;

    graphic = sf::CircleShape(RADIUS);
    graphic.setPosition(position);
    graphic.setFillColor(sf::Color::Red);
    state = 1;
}

void Food::update(sf::Time &dt) {
    decomposition += dt.asSeconds();
    if (decomposition > DECOMPOSITION_THRESHOLD) { state = 0; }
}


/*
void Food::isEaten() {
    state = 0;
}

void Food::isTargeted() {
    state = 2;
    graphic.setFillColor(sf::Color::Yellow);
}

void Food::HasBeenForgotten() {
    state = 1;
    graphic.setFillColor(sf::Color::Red);

}*/
