//
// Created by g0bel1n on 08/12/2021.
//

#include "Marker.h"
#include <math.h>

float Marker::get_intensity() {
    return exp(-lifetime.asSeconds()*coef);
}

Marker::Marker(sf::Vector2<float> position, int marker_type) {

    this->position = position;
    lifetime = sf::Time::Zero;
    this->marker_type=marker_type;

}

sf::Vector2f Marker::get_position() {
    return position;
}

void Marker::update(sf::Time& dt) {

}
