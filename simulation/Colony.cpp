#pragma once

#include <iostream>
#include "Colony.h"


using namespace parameters;

Chunk &get_chunk_ij(std::vector<Chunk> &chunks, int i, int j) {
    return chunks[j + LENGTH / CHUNKSIZE * i];
}

Chunk &get_chunk_xy(std::vector<Chunk> &chunks, float x, float y) {
    return get_chunk_ij(chunks, (int) (x / CHUNKSIZE), (int) (y / CHUNKSIZE));
}

Chunk &get_chunk_pos(std::vector<Chunk> &chunks, sf::Vector2<float> pos) {
    float x = std::max(std::min(pos.x, (float) WIDTH), (float) 0);
    float y = std::max(std::min(pos.y, (float) LENGTH), (float) 0);
    return get_chunk_ij(chunks, (int) (x / CHUNKSIZE), (int) (y / CHUNKSIZE));
}

Colony::Colony(int nb_ants, sf::Color color, sf::Texture hole_text, sf::Font font, sf::Vector2f colony_pos,
               float ant_speed) {


    food_in_colony = 0;
    this->nb_ants = nb_ants;
    this->colony_pos = colony_pos;
    this->nb_markers = 0;
    this->ant_speed = ant_speed;
    this->color = color;


    std::vector<Chunk> chunks;
    for (int i = 0; i < WIDTH / CHUNKSIZE + 1; i++) {
        for (int j = 0; j < LENGTH / CHUNKSIZE + 1; j++) {
            chunks.push_back(Chunk({i, j}));

        }
    }

    this->chunks = chunks;

    for (int i = 0; i < nb_ants; i++) {

        Ant_ ant(colony_pos, i, color, ant_speed);
        ants.push_back(ant);
    }

    colony_hole = hole_text;

    colony_base.setPosition(colony_pos);
    colony_base.setOrigin(536. / 2., 204.);
    colony_base.setColor(color);
    colony_base.setScale(0.2, 0.2);
}

int Colony::get_nb_ants() {
    return ants.size();
}

void Colony::update(sf::Time dt, std::vector<Obstacle> &obstacles, std::vector<Food> &foods) {

    for (auto &ant: ants) {
        ant.update(dt, chunks, obstacles, foods, food_in_colony, ant_speed, colony_pos);
    }

    for (int c = 0; c < chunks.size(); c++) {
        std::vector<Marker> &markers = chunks[c].getMarkers();
        for (int k = 0; k < markers.size(); k++) {
            markers[k].update(dt);
            if (markers[k].state == 0)markers.erase(markers.begin() + k);
        }
    }

    if (food_in_colony >= FOOD_FOR_GENERATION) {
        add_ant();
        ant_generated += 1;
        food_in_colony -= FOOD_FOR_GENERATION;
    }

}


void Colony::add_ant() {

    Ant_ ant(colony_pos, 0, color, ant_speed);
    ants.push_back(ant);


}

void Colony::delete_ant() {
    ants.pop_back();
}

void Colony::apply_texture() {

    for (auto &ant: ants)ant.apply_texture();
    colony_base.setTexture(colony_hole);
}

