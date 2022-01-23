//
// Created by g0bel1n on 08/12/2021.
//

#pragma once

#include <cmath>
#include "Marker.h"

using namespace parameters;

Marker::Marker(){
    graphic = sf::CircleShape(RADIUS);
    graphic.setFillColor(sf::Color::Black);
}

void Marker::update(sf::Time& dt) {
    intensity_ToHome *= (1-DECAY_RATE)*dt.asSeconds();
    intensity_ToFood *= (1-DECAY_RATE)*dt.asSeconds();

    if (intensity_ToFood> DETECTABILITY_THRESHOLD || intensity_ToHome> DETECTABILITY_THRESHOLD)show=true;
    else show=false;
    }

void Marker::add_intensity_ToHome(float time_penalty) {
    intensity_ToHome+= INTENSITY_INCREMENT*pow((1-DECAY_RATE),time_penalty);
}

void Marker::add_intensity_ToFood(float time_penalty) {
    intensity_ToFood+= INTENSITY_INCREMENT*pow((1-DECAY_RATE),time_penalty);
}

float Marker::get_intensity_ToHome() {
    return intensity_ToHome;
}

float Marker::get_intensity_ToFood() {
    return intensity_ToFood;
}

