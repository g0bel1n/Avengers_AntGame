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

    void isTargeted();

    void HasBeenForgotten();

    void isEaten();
};


#endif //AVENGERS_ANTGAME_FOOD_H
