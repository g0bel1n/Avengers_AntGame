//
// Created by g0bel1n on 07/12/2021.
//

#ifndef ANTS_FIGHT_CLUB_WORLD_H
#define ANTS_FIGHT_CLUB_WORLD_H

#include "Elements/Marker.h"


#pragma once

#include <vector>
#include "ants/Ant.h"
#include "chunks/chunk.h"
#include "Elements/Food.h"


Chunk &get_chunk_ij(std::vector<Chunk> &chunks, int i, int j);

Chunk &get_chunk_pos(std::vector<Chunk> &chunks, sf::Vector2<float> pos);

class Colony {

public:

    Colony(int nb_ants, sf::Color color,
           sf::Vector2f colony_pos = parameters::DEFAULT_COLONY_POSITION,
           float ant_speed = parameters::DEFAULT_ANT_SPEED);

    //Methods
    int get_nb_ants();

    void add_ant();

    void delete_ant();

    void update(sf::Time dt, std::vector<Obstacle> &obstacles, std::vector<Food> &foods);


    // Attributes
    int food_in_colony{};
    int ant_generated = 0;
    float ant_speed{};
    sf::Vector2f colony_pos;

    std::vector<Ant> ants;
    std::vector<Chunk> chunks;

    // Colony Graphic object
    sf::Sprite colony_base;

private:
    sf::Color color;
};


#endif //ANTS_FIGHT_CLUB_WORLD_H
