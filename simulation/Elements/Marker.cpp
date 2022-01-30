//
// Created by g0bel1n on 08/12/2021.
//

#pragma once

#include "Marker.h"
#include <math.h>
#include "../parameters.h"
#include "../chunks/chunk.h"


using namespace parameters;

float Marker::get_intensity() {
    return intensity;
}

Marker::Marker(sf::Vector2<float> position, int state, Chunk *myChunk, float time_offset = 0.) {

    this->position = position;
    this->intensity = INTENSITY_INCREMENT * pow(1 - DECAY_RATE, time_offset);
    this->myChunk = myChunk;

    this->state = state;

    graphic = sf::CircleShape(intensity);
    graphic.setPosition(position);
    graphic.setFillColor(color());


}

void Marker::update(sf::Time &dt) {

    /* Exponential decrease of the marker's intensity with time */
    intensity *= pow((1 - DECAY_RATE), dt.asSeconds());
    if (intensity < INTENSITY_INCREMENT * 0.2) {
        graphic.setRadius(intensity);
    }
    else {
        if (intensity < INTENSITY_INCREMENT * 0.4) {
            graphic.setRadius(intensity);
        }
        else {
            if (intensity < INTENSITY_INCREMENT * 0.6) {
                graphic.setRadius(intensity);
            }
            else {
                if (intensity < INTENSITY_INCREMENT * 0.8) {
                    graphic.setRadius(intensity);
                }
            }
        }
    }
    if (intensity < DETECTION_THRESHOLD) {
        state = 0;
        intensity = 0.;
    }

    if (changeColor) {
        graphic.setFillColor(color());
        changeColor = false;
    }


}

const sf::Color &Marker::color() {
    if (state == 1)return sf::Color::Blue;
    else return sf::Color::Green;  // if state=ToHome

}

