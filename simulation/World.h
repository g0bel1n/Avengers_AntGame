//
// Created by g0bel1n on 07/12/2021.
//

#ifndef ANTS_FIGHT_CLUB_WORLD_H
#define ANTS_FIGHT_CLUB_WORLD_H

#pragma once

#include <vector>
#include "ants/Ant_.h"

class World {

public:

    World(int nb_ants, int nb_food);

    int get_nb_ants();

    int get_nb_food();


    std::vector<Ant_> ants;
    std::vector<Marker> markers;
    std::vector<Marker> foods;

    void add_ant();


    int get_food_available();

    sf::Texture texture;

    void update(sf::Time dt, std::vector<Obstacle> &obstacles);

    void AddMarker(sf::Vector2f position, int type);

private:


    int nb_ants;
    int nb_food;


};


#endif //ANTS_FIGHT_CLUB_WORLD_H
