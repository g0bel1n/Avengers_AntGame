//
// Created by g0bel1n on 29/01/2022.
//

#ifndef AVENGERS_ANTGAME_FOOD_H
#define AVENGERS_ANTGAME_FOOD_H

#include "BaseElement.h"


class Food : public BaseElement {

    float decomposition = 0.;

public:
    explicit Food(sf::Vector2<float> position);

    void update(sf::Time &dt) override;

    sf::CircleShape graphic;

    //Below lies the previous targeting system of food by ants. However, when the amount of ants got too important,
    // there was congestion. Therefore we decided to abandon it. It is signaled in the code by : @@.
    /*
    void isTargeted();
    void HasBeenForgotten();
    void isEaten(); */
};


#endif //AVENGERS_ANTGAME_FOOD_H
