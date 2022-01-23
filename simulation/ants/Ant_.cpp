//
// Created by g0bel1n on 07/12/2021.
//
#pragma once
#include "Ant_.h"
#include <cmath>
#include <iostream>
#include "../../common/utils.h"

using namespace parameters;

float Ant_::RandomAngle() {
    return (std::rand() % angular_width - angular_width / 2) * (PI / 180);
}

Ant_::Ant_(sf::Vector2<float> position, int ant_id, int nb_food) {
    this->position = position;
    this->lifetime = 0;
    this->angle = (std::rand() % 360 - 180) * (PI / 180);
    this->direction = sf::Vector2<float>(cos(angle), sin(angle));

    this->ant_id = ant_id;
    this->home = position;



    graphics = sf::Sprite();
    graphics.setColor(sf::Color::Red);
    graphics.setOrigin(300., 300.f);

    graphics.setScale(0.05f, 0.05f);
    graphics.setPosition(position);

}

float Ant_::get_lifetime() {
    return this->lifetime;
}

bool Ant_::is_valid(sf::Vector2f position_to_test, std::vector<Obstacle> &obstacles) {
    float offset = 5.f;
    if (!((position_to_test.x > 0 + offset) && (position_to_test.x + offset < LENGTH) && (position_to_test.y > 0 + offset) &&
          (position_to_test.y + offset < WIDTH)))
        return false;
    for (auto &obstacle: obstacles) {
        if (position_to_test.x >= obstacle.graphics[0].position.x && position_to_test.x <= obstacle.graphics[1].position.x &&
            position_to_test.y >= obstacle.graphics[0].position.y && position_to_test.y <= obstacle.graphics[2].position.y) {
            return false;
        }

    }
    return true;
}

void Ant_::move_to(sf::Vector2<float> new_position, sf::Time dt, std::vector<Obstacle> &obstacles,
                   Marker markers [LENGTH][WIDTH]) {

    if (is_valid(new_position, obstacles)) {
        this->position = new_position;
    } else {
        this->angle += PI/2;
        this->direction = sf::Vector2<float>(cos(angle), sin(angle));
        this->position += direction * ANT_SPEED * dt.asSeconds();
        //AddMarker(markers, 5,10.);
        //last_changed=sf::seconds(direction_change_delta+0.5);
        times_wall_hit++;
    }

}

void
Ant_::update(sf::Time dt, Marker markers [LENGTH][WIDTH], std::vector<Obstacle> &obstacles, std::vector<Food> &foods) {

    // To avoid changing direction too often...
    if (last_changed > sf::seconds(direction_change_delta + (std::rand() % 5) / 100.)) {
        //If looking for food...
        if (ToFood) {
            time_since_quitted_home += dt.asSeconds();

            //if (time_since_quitted_home>10){ToFood=false;}
            //Looking for food and didn't see it yet
            if (target == -1) {

                target = food_search(foods, DETECTION_RADIUS);
                //If it detects valid food, let's go to it
                if (target >= 0 && !foods[target].is_not_taken) {
                    foods[target].is_not_taken = false;
                    sf::Vector2f delta_vect = foods[target].position - position;
                    float new_angle = atan2(delta_vect.y , delta_vect.x);
                    this->angle = new_angle;
                    last_changed = sf::Time::Zero;
                    std::cout << "4 \n";


                }
                    //If the ant can't see the food, it looks for markers left by others
                else {
                    float new_angle = MarkersDetection(markers);
                    // if new_angle is a nan it is because there is no markers in the detection radius
                    if (!isnan(new_angle)) {
                        this->angle = new_angle;
                        std::cout << "5 \n";
                    } else {
                        this->angle += RandomAngle();
                        std::cout << "6 \n";
                    }
                    last_changed = sf::Time::Zero;
                }
            }

                // If we are looking for food but already going to the target...
            else {
                // Just checking if arrived. If not, keep going...
                if (target == food_search(foods, EATING_RADIUS)) {
                    std::cout << "8 \n";

                    foods[target].eaten();
                    target = -1;
                    ToFood = false;
                    time_since_found_food = 0.;
                    switchSkin = true;
                    last_changed = sf::Time::Zero;
                    this->angle += PI;

                    texture_with_food.loadFromFile("../ressources/ant_with_food.png");
                    graphics.setTexture(texture_with_food);
                    switchSkin = false;

                }
                    //if we are not there yet, lets check if it is still avalaible
                else if (!foods[target].is_not_taken) {
                    target = -1;

                } else if (food_search(foods, DETECTION_RADIUS) != target) {

                    foods[target].is_not_taken = false;
                    target = -1;
                }

            }
        }
            //If we are going home...
        else {
            time_since_found_food += dt.asSeconds();
            //Let's look if we arrived
            if (distance(home, position) <= EATING_RADIUS) {

                texture.loadFromFile("../ressources/ant.png");
                graphics.setTexture(texture);
                switchSkin = false;

                switchSkin = true;
                ToFood = true;

                this->angle += PI + RandomAngle();
                last_changed = sf::Time::Zero;
                time_since_quitted_home = 0.;

                std::cout << "1 \n";

            }

                //If we are not arrived, we might at least see it
            else if (distance(home, position) <= DETECTION_RADIUS) {
                sf::Vector2f delta_vect = home - position;
                float new_angle = atan2(delta_vect.y , delta_vect.x);
                /*if (new_angle <= angle + PI / 2 && new_angle >= angle - PI / 2)this->angle = new_angle;
                else this->angle= new_angle +PI  ;*/
                last_changed = sf::Time::Zero;
                this->angle = new_angle;

                std::cout << "2 \n";
            }

                //If we cant see it, lets look for clues
            else {

                float new_angle = MarkersDetection(markers);
                // 9 times out of 10, the ant takes a random direction
                // if new_angle is a nan it is because there is no markers in the detection radius
                if (!isnan(new_angle)) {
                    this->angle = new_angle;
                    std::cout<<"Following markers \n";
                } else {
                    this->angle += RandomAngle();
                    std::cout << "3 \n";
                }
                last_changed = sf::Time::Zero;

            }

        }

    }


    this->angle = normalise_angle(angle);
    this->direction = sf::Vector2<float>(cos(angle), sin(angle));
    sf::Vector2<float> new_position = this->position + this->direction * ANT_SPEED * dt.asSeconds();
    move_to(new_position, dt, obstacles, markers);
    if (last_dropped > .05) {

        int i = (int)position.y;
        int j = (int)position.x;

        if (ToFood)markers[i][j].add_intensity_ToFood(time_since_quitted_home);
        else markers[i][j].add_intensity_ToHome(time_since_found_food);
        last_dropped = 0.;
    }

    lifetime += dt.asSeconds();
    last_changed += dt;
    last_dropped += dt.asSeconds();

    graphics.setPosition(position);
    graphics.setRotation(angle * 180 / PI);

}

float Ant_::get_angle() {
    return this->angle;
}

int Ant_::food_search(std::vector<Food> &foods, float radius) {
    int i = 0;
    float distance_;
    float min_distance = 1000.f;
    int min_index = -1;
    while (foods.size() > i) {
        if (foods[i].is_active == true) {
            distance_ = distance(foods[i].position, position);
            if (distance_ <= radius && distance_ <= min_distance) {
                min_distance = distance_;
                min_index = i;
            }
        }
        i++;
    }
    return min_index;
}


float Ant_::MarkersDetection(Marker markers [LENGTH][WIDTH]) {

    float bary_angle = 0.;
    float total_intensity = 0.;

    int x_min =fmax((int)(position.x-DETECTION_RADIUS),0);
    int x_max =fmax((int)(position.x+DETECTION_RADIUS),WIDTH);
    int y_min =fmax((int)(position.y-DETECTION_RADIUS),0);
    int y_max =fmax((int)(position.y+DETECTION_RADIUS),LENGTH);

    for (int i = y_min;i<y_max; i++) {
        for (int j = x_min; j < x_max; j++) {

            float distance_ = distance(sf::Vector2f(j, i), position);
            if (distance_ <= DETECTION_RADIUS && distance_ > EATING_RADIUS) {

                sf::Vector2f target_position = sf::Vector2f(j, i);
                sf::Vector2f delta_vect = target_position - position;
                float markers_angle = atan2(delta_vect.y, delta_vect.x);
                markers_angle = normalise_angle(markers_angle);
                if (markers_angle <= angle + PI / 2 && markers_angle >= angle - PI / 2) {

                    if (ToFood) {
                        bary_angle += markers[i][j].get_intensity_ToFood() * markers_angle;
                        total_intensity += markers[i][j].get_intensity_ToFood();
                    } else {
                        bary_angle += markers[i][j].get_intensity_ToHome() * markers_angle;
                        total_intensity += markers[i][j].get_intensity_ToHome();
                    }
                }
            }
        }
    }

    return bary_angle / (total_intensity);
}

sf::Vector2f Ant_::get_position() {
    return position;
}









