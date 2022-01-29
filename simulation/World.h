//
// Created by g0bel1n on 07/12/2021.
//

#ifndef ANTS_FIGHT_CLUB_WORLD_H
#define ANTS_FIGHT_CLUB_WORLD_H

#include "markers/Marker.h"


#pragma once

#include <vector>
#include "ants/Ant_.h"
#include "chunks/chunk.h"


Chunk &get_chunk_ij(std::vector<Chunk> &chunks, int i, int j);

Chunk &get_chunk_xy(std::vector<Chunk> &chunks, float x, float y);

Chunk &get_chunk_pos(std::vector<Chunk> &chunks, sf::Vector2<float> pos);

class World {

public:

    World(int nb_ants, int nb_food);

    int get_nb_ants();

    int get_nb_food();

    std::vector<Ant_> ants;
    std::vector<Chunk> chunks;
    std::vector<Marker> foods;

    void add_ant();


    int get_food_available();

    sf::Texture texture;

    void update(sf::Time dt, std::vector<Obstacle> &obstacles);

    void AddMarker(sf::Vector2f position, int type);

private:


    int nb_ants;
    int nb_food;
    int nb_markers;


};


#endif //ANTS_FIGHT_CLUB_WORLD_H
