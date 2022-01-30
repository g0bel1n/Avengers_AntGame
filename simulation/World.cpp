//
// Created by g0bel1n on 29/01/2022.
//

#include "World.h"


void World::update(sf::Time &dt) {

    for (auto &colony: colonies) {
        colony.update(dt, obstacles, foods);
    }

    for (int k = 0; k < foods.size(); k++) {
        foods[k].update(dt);
        if (foods[k].state == 0)foods.erase(foods.begin() + k);
    }
}

World::World(int nb_colonies, int nb_ants_per_colony) {

    for (int i = 0; i < nb_colonies; i++) {
        colonies.emplace_back(nb_ants_per_colony, parameters::DEFAULT_COLORS[i]);
    }


}

int World::get_food_available() {
    int food_available = 0;
    for (auto &food: foods) {
        if (food.state == 1)food_available++;
    }
    return food_available;
}

void World::AddFood(sf::Vector2f position) {
    foods.emplace_back(position); /* Un food n'a pas de chunk */

}
