#pragma once

#include <iostream>
#include "Colony.h"


using namespace parameters;

Chunk &get_chunk_ij(std::vector<Chunk> &chunks, int i, int j) {
    return chunks[j + LENGTH / CHUNKSIZE * i];
}

Chunk &get_chunk_pos(std::vector<Chunk> &chunks, sf::Vector2<float> pos) {
    float x = std::max(std::min(pos.x, (float) WIDTH), (float) 0);
    float y = std::max(std::min(pos.y, (float) LENGTH), (float) 0);
    return get_chunk_ij(chunks, (int) (x / CHUNKSIZE), (int) (y / CHUNKSIZE));
}

void fast_erase(std::vector<Marker> &vect, int pos) { /*Using the back-swap trick*/
    auto it = vect.begin() + pos;
    *it = std::move(vect.back());
    vect.pop_back();
}

Colony::Colony(int nb_ants, sf::Color color, sf::Vector2f colony_pos,
               float ant_speed) {

    food_in_colony = 0;
    this->colony_pos = colony_pos;
    this->ant_speed = ant_speed;
    this->color = color;


    // Building Chunks
    std::vector<Chunk> chunks;
    for (int i = 0; i < WIDTH / CHUNKSIZE + 1; i++) {
        for (int j = 0; j < LENGTH / CHUNKSIZE + 1; j++) {
            chunks.push_back(Chunk({i, j}));
        }
    }
    this->chunks = chunks;

    // Generating ants
    for (int i = 0; i < nb_ants; i++) {
        Ant ant(colony_pos, color, ant_speed);
        ants.push_back(ant);
    }


    //Setting up the colony graphics
    colony_base.setTexture(hole_texture);
    colony_base.setPosition(colony_pos);
    colony_base.setOrigin(536. / 2., 204.);
    colony_base.setColor(color);
    colony_base.setScale(0.2, 0.2);
}

int Colony::get_nb_ants() {
    return ants.size();
}

void Colony::update(sf::Time dt, std::vector<Obstacle> &obstacles, std::vector<Food> &foods) {

    //Update ants
    for (auto &ant: ants) {
        ant.update(dt, chunks, obstacles, foods, food_in_colony, ant_speed, colony_pos);
    }

    //Update Chunks
    for (auto &chunk: chunks) {
        std::vector<Marker> &markers = chunk.getMarkers();
        for (int k = 0; k < markers.size(); k++) {
            markers[k].update(dt);
            if (markers[k].state == 0) fast_erase(markers, k);
        }
    }

    // Generate ants according to food in the colony
    if (food_in_colony >= FOOD_FOR_GENERATION) {
        add_ant();
        ant_generated += 1;
        food_in_colony -= FOOD_FOR_GENERATION;
    }

}

void Colony::add_ant() {
    Ant ant(colony_pos, color, ant_speed);
    ants.push_back(ant);
}

//Delete the last ant
void Colony::delete_ant() {
    ants.pop_back();
}