//
// Created by g0bel1n on 08/12/2021.
//

#ifndef ANTS_FIGHT_CLUB_MARKER_H
#define ANTS_FIGHT_CLUB_MARKER_H

#pragma once
#include <SFML/Graphics.hpp>
#include "../simulation_parameters.h"

class Marker {

public:

    Marker();
    void add_intensity_ToHome(float incr);
    void add_intensity_ToFood(float incr);

    float get_intensity_ToHome();
    float get_intensity_ToFood();

    sf::CircleShape graphic;

    void update(sf::Time &dt);
    bool show;

private:


    float intensity_ToHome =0.;
    float intensity_ToFood=0.;



};


#endif //ANTS_FIGHT_CLUB_MARKER_H
