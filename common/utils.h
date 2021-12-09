//
// Created by g0bel1n on 09/12/2021.
//

#ifndef ANTS_FIGHT_CLUB_UTILS_H
#define ANTS_FIGHT_CLUB_UTILS_H
#include <SFML/Graphics.hpp>
#include <cmath>

float distance(sf::Vector2f vect1, sf::Vector2f vect2 ){
    float distance_x = pow(vect2.x-vect1.x,2);
    float distance_y = pow(vect2.y-vect1.y,2);
    return sqrt(distance_x+distance_y);
}


#endif //ANTS_FIGHT_CLUB_UTILS_H
