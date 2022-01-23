//
// Created by g0bel1n on 08/12/2021.
//

#pragma once
#include "Marker.h"
#include <math.h>
#include "../parameters.h"


using namespace parameters;

sf::Color marker_color(int marker_type){
    if (marker_type == 1){return sf::Color::Red;}
    else if(marker_type == 3){return sf::Color::Blue;}
    else if (marker_type == 4){return sf::Color::Green;}
    else if (marker_type == 2){return sf::Color::Yellow;}
    //else if (marker_type==-1){return sf::Color(104, 157, 113);}
    else if (marker_type==5){return sf::Color::Black;}
    else return sf::Color::Transparent;
}

float Marker::get_intensity() {
    return intensity;
}
Marker::Marker(sf::Vector2<float> position, int marker_type, float time_offset=0.) {

    this->position = position;
    this->marker_type=marker_type;
    this->intensity = INTENSITY_INCREMENT*pow(1-DECAY_RATE,time_offset);

    graphic = sf::CircleShape(intensity);
    graphic.setPosition(position);
    graphic.setFillColor(marker_color(marker_type));
}

void Marker::update(sf::Time& dt) {
    intensity *= pow((1-DECAY_RATE),dt.asSeconds());
    if (marker_type==3 || marker_type == 4){
        intensity *= pow((1-DECAY_RATE),dt.asSeconds());
        graphic.setRadius(intensity);
        if (intensity < DETECTION_THRESHOLD){
            marker_type=-1;
            intensity = 0.;
        }
    }

    if (changeColor){graphic.setFillColor(marker_color(marker_type));
        changeColor=false;

    }



}

