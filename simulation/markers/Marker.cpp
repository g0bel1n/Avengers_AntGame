//
// Created by g0bel1n on 08/12/2021.
//

#include "Marker.h"
#include <math.h>

float Marker::get_intensity() {
    return std::max(15.-lifetime.asSeconds(),0.);
}
Marker::Marker(sf::Vector2<float> position, int marker_type, float time_offset) {

    this->position = position;
    lifetime = sf::Time::Zero;
    lifetime+=sf::seconds(time_offset*2);
    this->marker_type=marker_type;

}

void Marker::update(sf::Time& dt) {
    lifetime+=dt;
    if (marker_type==3 || marker_type == 4){
        if (get_intensity() < death_threshold){
            marker_type=-1;
        };
    }

}
