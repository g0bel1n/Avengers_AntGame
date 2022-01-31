//
// Created by g0bel1n on 29/01/2022.
//

#ifndef AVENGERS_ANTGAME_BASEELEMENT_H
#define AVENGERS_ANTGAME_BASEELEMENT_H

#pragma once

#include <SFML/Graphics.hpp>

class BaseElement {


public:

    sf::Vector2f position;
    bool changeColor = false;
    int state;

    // Abstract methods : inherited classes must have an update function
    virtual void update(sf::Time &dt) = 0;

};


#endif //AVENGERS_ANTGAME_BASEELEMENT_H
