#pragma once
#include <iostream>
#include "World.h"
#include "../simulation/simulation_parameters.h"


using namespace parameters;

void update_markers(sf::Time dt, Marker grid [LENGTH][WIDTH]){
    for(int i=0; i<LENGTH;i++){
        for(int j=0;j<WIDTH;j++){
            grid[i][j].update(dt);
        }
    }
}

World::World(int LENGTH, int WIDTH, int nb_ants, int nb_food) {

    this->nb_ants=nb_ants;
    this->nb_food = nb_food;
    sf::Vector2<float> aleat_position (50.,WIDTH/2.);


    for(int i=0; i<nb_ants;i++){

        texture.loadFromFile("../ressources/ant.png");
        Ant_ ant (aleat_position, i, nb_food);
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

void World::update_world( sf::Time dt, std::vector<Obstacle>& obstacles,Marker markers [LENGTH][WIDTH]) {

    for (int k=0; k<nb_ants;k++){
        ants[k].update(dt,markers, obstacles,foods);
    }
    update_markers(dt, markers);

}

int World::get_food_available() {
    int food_avalaible = 0;
    for(int i=0; i<foods.size(); i++){
        if(foods[i].is_active)food_avalaible++;
    }
    return food_avalaible;
}

void World::add_food(sf::Vector2f position) {
    Food food_ (position);
    foods.push_back(food_);

}

