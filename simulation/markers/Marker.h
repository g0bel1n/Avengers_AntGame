//
// Created by g0bel1n on 08/12/2021.
//

#ifndef ANTS_FIGHT_CLUB_MARKER_H
#define ANTS_FIGHT_CLUB_MARKER_H
#include <SFML/Graphics.hpp>

class Marker {

public:
    Marker(sf::Vector2<float> position, int marker_type);

    float get_intensity();

    sf::Vector2f get_position();

    float radius = 30.f;
    int marker_type;

    void update(sf::Time& dt);



private:

    sf::Vector2<float> position;
    sf::Time lifetime;
    float coef = 10.f;


};



#endif //ANTS_FIGHT_CLUB_MARKER_H
