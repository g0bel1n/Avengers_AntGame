//
// Created by g0bel1n on 07/12/2021.
//

#include "World.h"

World::World(int lenght, int width, int nb_ants, int nb_food) {

    world_lenght = lenght;
    world_width = width;

    this->nb_ants=nb_ants;
    this->nb_food = nb_food;

    for(int i=0; i<nb_ants;i++){
        sf::Vector2<float> aleat_position ((float)(std::rand()%world_width),(float)(std::rand()%world_lenght
        ));
        Ant_ ant (aleat_position,i,world_width,world_lenght);
        ants.push_back(ant);
    }

    for(int i=0; i<nb_food;i++){
        sf::Vector2<float> aleat_position ((float)(std::rand()%world_width),(float)(std::rand()%world_lenght));
        Marker marker (aleat_position,i);
        markers.push_back(marker);
    }

}

int World::get_nb_ants() {
    return ants.size();
}

int World::get_nb_food() {
    return markers.size();
}

void World::update_ants( sf::Time dt) {

    for (int k=0; k<nb_ants;k++){

        ants[k].update(dt,markers);

    }

    for (int k=0; k<nb_food;k++){

        markers[k].update(dt);

    }

}
