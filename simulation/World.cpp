#pragma once

#include <iostream>
#include "World.h"
#include <iostream>


using namespace parameters;

Chunk& get_chunk_ij(std::vector<Chunk>& chunks, int i, int j) {
    return chunks[j + LENGTH/CHUNKSIZE * i];
}

Chunk& get_chunk_xy(std::vector<Chunk>& chunks, float x, float y) {
    return get_chunk_ij(chunks, (int)(x/CHUNKSIZE), (int)(y/CHUNKSIZE));
}

Chunk& get_chunk_pos(std::vector<Chunk>& chunks, sf::Vector2<float> pos) {
    float x = std::max(std::min(pos.x, (float)WIDTH), (float)0);
    float y = std::max(std::min(pos.y, (float)LENGTH), (float)0);
    return get_chunk_ij(chunks, (int)(x/CHUNKSIZE), (int)(y/CHUNKSIZE));
}

World::World(int nb_ants, int nb_food) {


    this->nb_ants = nb_ants;
    this->nb_food = nb_food;

    std::vector<Chunk> chunks;
    for (int i = 0; i < WIDTH/CHUNKSIZE+1; i++) {
        for (int j = 0; j < LENGTH/CHUNKSIZE+1; j++) {
            chunks.push_back(Chunk({i, j}));

        }
    }

    this->chunks = chunks;

    for (int i = 0; i < nb_ants; i++) {

        texture.loadFromFile("../ressources/ant.png");
        Ant_ ant(COLONY_POS, i);
        ant.graphics.setTexture(texture);

        ants.push_back(ant);
    }
}

int World::get_nb_ants() {
    return ants.size();
}

int World::get_nb_food() {
    return foods.size();
}

void World::update(sf::Time dt, std::vector<Obstacle> &obstacles) {

    for (int k = 0; k < NB_ANTS; k++) {
        ants[k].update(dt, chunks, obstacles, foods);
    }

    for (int c = 0; c < chunks.size(); c++) {
        std::vector<Marker>& markers = chunks[c].getMarkers();
        for (int k = 0; k < markers.size(); k++) {
            markers[k].update(dt);
            if (markers[k].marker_type == -1)markers.erase(markers.begin() + k);
        }}


    for (int k = 0; k < foods.size(); k++) {
        foods[k].update(dt);
    }
}

int World::get_food_available() {
    int food_available = 0;
    for (int i = 0; i < foods.size(); i++) {
        if (foods[i].marker_type == 1)food_available++;
    }
    return food_available;
}

void World::AddMarker(sf::Vector2f position, int type) {

    if (type == 1)foods.push_back(Marker(position, type, nullptr, 0.)); /* Un food n'a pas de chunk */

    else {
        Chunk& fatherChunk = get_chunk_pos(chunks, position);
        fatherChunk.getMarkers().push_back(Marker(position, type, &fatherChunk, 0.));
    }


}

void World::add_ant() {

    texture.loadFromFile("../ressources/ant.png");
    Ant_ ant(COLONY_POS, 0);
    ant.graphics.setTexture(texture);
    ants.push_back(ant);

}

