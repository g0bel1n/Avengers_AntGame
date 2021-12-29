#pragma once
#include <iostream>
#include "World.h"

#define MY_PATH std::string ("/Users/g0bel1n/CLionProjects/Avengers_AntGame")


World::World(int lenght, int width, int nb_ants, int nb_food) {

    world_lenght = lenght;
    world_width = width;

    this->nb_ants=nb_ants;
    this->nb_food = nb_food;
    sf::Vector2<float> aleat_position (50.,width/2.);


    for(int i=0; i<nb_ants;i++){

        texture.loadFromFile(MY_PATH+"/ressources/ant.png");
        Ant_ ant (aleat_position,i,world_width,world_lenght,nb_food);
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

void World::update_ants( sf::Time dt, std::vector<Obstacle>& obstacles) {

    for (int k=0; k<nb_ants;k++){
        ants[k].update(dt,markers, obstacles,foods);
    }

    for (int k=0; k<markers.size();k++){
        markers[k].update(dt);
        if (markers[k].marker_type==-1)markers.erase(markers.begin()+k);
    }

    for (int k=0; k<foods.size();k++){
        foods[k].update(dt);
    }

}

int World::get_food_available() {
    int food_avalaible = 0;
    for(int i=0; i<foods.size(); i++){
        if(foods[i].marker_type==1)food_avalaible++;
    }
    return food_avalaible;
}

void World::AddMarker(sf::Vector2f position, int type) {

    Marker marker_ (position, type, 0.);

    if(type==1)foods.push_back(marker_);
    else markers.push_back(marker_);


}

