//
// Created by g0bel1n on 09/12/2021.
//

#ifndef ANTS_FIGHT_CLUB_UTILS_H
#define ANTS_FIGHT_CLUB_UTILS_H
#include <SFML/Graphics.hpp>
#include <cmath>

#define PI 3.14159265


float distance(sf::Vector2f vect1, sf::Vector2f vect2 ){
    float distance_x = pow(vect2.x-vect1.x,2);
    float distance_y = pow(vect2.y-vect1.y,2);
    return sqrt(distance_x+distance_y);
}

float normalise_angle(float angle){

    float n_angle = angle;
    float sign = 1.;
    if (angle<0)sign=-1.;


    while(abs(n_angle)>PI){
        n_angle -= sign*2.*PI;
    }
    return n_angle;
}

float scalar_product(sf::Vector2f vect1, sf::Vector2f vect2){
    return vect1.x*vect2.x + vect1.y*vect2.y;
}



#endif //ANTS_FIGHT_CLUB_UTILS_H
