//
// Created by g0bel1n on 07/12/2021.
//

#include <iostream>
#include "World.h"

World::World(int lenght, int width, int nb_ants, int nb_food) {

    world_lenght = lenght;
    world_width = width;

    this->nb_ants=nb_ants;
    this->nb_food = nb_food;
    sf::Vector2<float> aleat_position (130.,30.);


    for(int i=0; i<nb_ants;i++){

        texture.loadFromFile("../ressources/ant.png");
        Ant_ ant (aleat_position,i,world_width,world_lenght,nb_food);
        ant.graphics.setTexture(texture);

        ants.push_back(ant);
    }
     //aleat_position = sf::Vector2<float>((float)(std::rand()%world_width),(float)(std::rand()%world_lenght));
    aleat_position = sf::Vector2<float>((float)(world_width-200),(float)(world_lenght-200));
float x_offset=10.;
    for(int i=0; i<nb_food;i++){
        if (i%10==0){
            x_offset=-x_offset;
            aleat_position += sf::Vector2f (0.,10.f);
        }
        Marker marker (aleat_position,1,0.);
        aleat_position += sf::Vector2f (x_offset,0.);

        markers.push_back(marker);
    }

}

int World::get_nb_ants() {
    return ants.size();
}

int World::get_nb_food() {
    return nb_food;
}

void World::update_ants( sf::Time dt, std::vector<Obstacle>& obstacles) {

    for (int k=0; k<nb_ants;k++){

        ants[k].update(dt,markers, obstacles);

    }

    for (int k=0; k<markers.size();k++){

        markers[k].update(dt);
        int nb_deleted =0;
        if (k>=nb_food && markers[k].marker_type==-1){
            nb_deleted++;
            markers.erase(markers.begin()+k);
        }
    }

}

int World::get_food_available() {
    int food_avalaible = 0;
    for(int i=0; i<nb_food; i++){
        if(markers[i].marker_type==1)food_avalaible++;
    }
    return food_avalaible;
}

