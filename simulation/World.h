//
// Created by g0bel1n on 29/01/2022.
//

#ifndef AVENGERS_ANTGAME_WORLD_H
#define AVENGERS_ANTGAME_WORLD_H


#include "Colony.h"

class World {

public:


    explicit World(int nb_colonies = parameters::DEFAULT_NB_COLONIES,
                   int nb_ants_per_colony = parameters::DEFAULT_NB_ANTS_PER_COLONY);

    //Methods
    void update(sf::Time &dt);

    void AddFood(sf::Vector2f position);

    int get_food_available();

    //Attributes
    std::vector<Colony> colonies;
    std::vector<Food> foods;
    std::vector<Obstacle> obstacles;

};


#endif //AVENGERS_ANTGAME_WORLD_H
