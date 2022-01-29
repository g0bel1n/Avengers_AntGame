//
// Created by g0bel1n on 29/01/2022.
//

#ifndef AVENGERS_ANTGAME_BASEELEMENT_H
#define AVENGERS_ANTGAME_BASEELEMENT_H

#pragma once

#include <SFML/Graphics.hpp>
#include <string>


class BaseElement {


public:

    sf::Vector2f position;
    sf::CircleShape graphic;
    bool changeColor = false;

    virtual void update(sf::Time &dt) = 0;

    int state;
};


#endif //AVENGERS_ANTGAME_BASEELEMENT_H
