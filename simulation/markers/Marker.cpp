//
// Created by g0bel1n on 08/12/2021.
//

#include "Marker.h"
#include <math.h>

sf::Color marker_color(int marker_type){
    if (marker_type == 1){return sf::Color::Red;}
    else if(marker_type == 3){return sf::Color::Blue;}
    else if (marker_type == 4){return sf::Color::Green;}
    else if (marker_type == 2){return sf::Color::Yellow;}
    else if (marker_type==-1){return sf::Color(104, 157, 113);}
    else if (marker_type==5){return sf::Color::Black;}
}

float Marker::get_intensity() {
    return std::max(20.-lifetime.asSeconds(),0.);
}
Marker::Marker(sf::Vector2<float> position, int marker_type, float time_offset) {

    this->position = position;
    lifetime = sf::Time::Zero;
    lifetime+=sf::seconds(time_offset*2);
    this->marker_type=marker_type;

    graphic = sf::CircleShape(get_intensity()/4.);
    graphic.setPosition(position);
    graphic.setFillColor(marker_color(marker_type));
}

void Marker::update(sf::Time& dt) {
    lifetime+=dt;
    if (marker_type==3 || marker_type == 4){
        graphic.setRadius(get_intensity()/4.);
        if (get_intensity() < death_threshold+0.1){
            marker_type=-1;
        }
    }

    if (changeColor){graphic.setFillColor(marker_color(marker_type));
        changeColor=false;

    }



}

