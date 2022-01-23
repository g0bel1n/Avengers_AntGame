//
// Created by g0bel1n on 23/01/2022.
//

#ifndef AVENGERS_ANTGAME_FOOD_H
#define AVENGERS_ANTGAME_FOOD_H

#pragma once
#include <SFML/Graphics.hpp>

class Food {

public:
    Food(sf::Vector2<float> position);

    float radius = 2.f;

    sf::Vector2<float> position;

    sf::CircleShape graphic;
    bool is_active = true;
    bool is_not_taken = false;
    void eaten();

};



#endif //AVENGERS_ANTGAME_FOOD_H
