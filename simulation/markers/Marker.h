//
// Created by g0bel1n on 08/12/2021.
//

#ifndef ANTS_FIGHT_CLUB_MARKER_H
#define ANTS_FIGHT_CLUB_MARKER_H

#include <SFML/Graphics.hpp>

class Marker {

public:
    Marker(sf::Vector2<float> position, int marker_type, float time_offset);

    float get_intensity();

    float radius = 2.f;
    int marker_type;

    sf::Vector2<float> position;

    sf::CircleShape graphic;
    bool changeColor = false;


    void update(sf::Time &dt);

    float death_threshold = 0.;


private:

    sf::Time lifetime;


};


#endif //ANTS_FIGHT_CLUB_MARKER_H
