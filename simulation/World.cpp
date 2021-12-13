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
    sf::Vector2<float> aleat_position (lenght/2.,width/2.);


    for(int i=0; i<nb_ants;i++){

        texture.loadFromFile("../ressources/ant.png");
        Ant_ ant (aleat_position,i,world_width,world_lenght,nb_food);
        ant.graphics.setTexture(texture);

        ants.push_back(ant);
    }
     //aleat_position = sf::Vector2<float>((float)(std::rand()%world_width),(float)(std::rand()%world_lenght));
    aleat_position = sf::Vector2<float>((float)(world_width-200),(float)(world_lenght-200));
float x_offset=10.;
    for(int i=0; i<nb_food/2;i++){
        if (i%10==0){
            x_offset=-x_offset;
            aleat_position += sf::Vector2f (0.,10.f);
        }
        Marker food (aleat_position,1,0.);
        aleat_position += sf::Vector2f (x_offset,0.);

        foods.push_back(food);
    }

    aleat_position = sf::Vector2<float>((float)(200),(float)(world_lenght-200));

    for(int i=0; i<nb_food/2;i++){
        if (i%10==0){
            x_offset=-x_offset;
            aleat_position += sf::Vector2f (0.,10.f);
        }
        Marker marker (aleat_position,1,0.);
        aleat_position += sf::Vector2f (x_offset,0.);

        foods.push_back(marker);
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

