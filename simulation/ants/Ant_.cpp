//
// Created by g0bel1n on 07/12/2021.
//
#pragma once

#include "Ant_.h"
#include <cmath>
#include "../../common/utils.h"


using namespace parameters;

#define PI 3.14159265

float Ant_::RandomAngle() {
    return (std::rand() % angular_width - angular_width / 2) * (PI / 180);
}

Ant_::Ant_(sf::Vector2<float> position, int ant_id) {
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

bool Ant_::is_valid(sf::Vector2f position, std::vector<Obstacle> &obstacles) {
    float offset = 5.f;
    if (!((position.x > 0 + offset) && (position.x + offset < WIDTH) && (position.y > 0 + offset) &&
          (position.y + offset < LENGTH)))
        return false;
    for (auto &obstacle: obstacles) {
        if (position.x >= obstacle.graphics[0].position.x && position.x <= obstacle.graphics[1].position.x &&
            position.y >= obstacle.graphics[0].position.y && position.y <= obstacle.graphics[2].position.y) {
            return false;
        }

    }
    return true;
}

void Ant_::move_to(sf::Vector2<float> new_position, sf::Time dt, std::vector<Obstacle> &obstacles,
                   std::vector<Marker> &markers) {
    /* Check if the position we are trying to implement is valid, e.g. no obstacle */

    if (is_valid(new_position, obstacles)) {
        this->position = new_position;
    } else {
        this->angle += PI / 2;
        this->direction = sf::Vector2<float>(cos(angle), sin(angle));
        this->position += direction * ANT_SPEED * dt.asSeconds();
        // Adding repellent ? (to pursue)
        //AddMarker(markers, 5,10.);
        //last_changed=sf::seconds(direction_change_delta+0.5);
        times_wall_hit++;
    }

}

void
Ant_::update(sf::Time dt, std::vector<Marker> &markers, std::vector<Obstacle> &obstacles, std::vector<Marker> &foods) {
/* Kind of a decision tree to decide what is the next position */

    // To avoid changing direction too often...
    if (last_changed > sf::seconds(direction_change_delta + (std::rand() % 5) / 100.)) {
        //If looking for food...
        if (ToFood) {
            time_since_quitted_home += dt.asSeconds();

            //if (time_since_quitted_home>10){ToFood=false;}
            //Looking for food and didn't see it yet
            if (target == -1) {

                target = check_env(foods, DETECTION_RADIUS);
                //If it detects valid food, let's go to it
                if (target >= 0 && foods[target].marker_type == 1) {
                    foods[target].changeColor = true;
                    foods[target].marker_type = 2;
                    sf::Vector2f delta_vect = foods[target].position - position;
                    float new_angle = atan2(delta_vect.y, delta_vect.x);
                    this->angle = new_angle;
                    last_changed = sf::Time::Zero;

                }
                    //If the ant can't see the food, it looks for markers left by others
                else {
                    float new_angle = sampleWorld(markers);
                    // if new_angle is a nan it is because there is no markers in the detection radius
                    if (!isnan(new_angle)) {
                        this->angle = new_angle;
                    } else {
                        this->angle += RandomAngle();
                    }
                    last_changed = sf::Time::Zero;
                }
            }

                // If we are looking for food but already going to the target...
            else {
                // Just checking if arrived. If not, keep going...
                if (target == check_env(foods, EATING_RADIUS)) {

                    foods[target].marker_type = -1;
                    foods[target].changeColor = true;
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
                    //if we are not there yet, lets still check if it is avalaible
                else if (foods[target].marker_type == -1) {
                    target = -1;

                } else if (check_env(foods, DETECTION_RADIUS) != target) {

                    foods[target].marker_type = 1;
                    target = -1;
                }

            }
        }
            //If we are going home...
        else {
            time_since_found_food += dt.asSeconds();
            //Let's look if we arrived
            if (distance(home, position) <= EATING_RADIUS) {

                // Changing skin
                texture.loadFromFile("../ressources/ant.png");
                graphics.setTexture(texture);
                switchSkin = false;

                //Changing Objective
                ToFood = true;

                //Going away
                this->angle += PI + RandomAngle();
                last_changed = sf::Time::Zero;
                time_since_quitted_home = 0.;


            }

                //If we are not arrived, we might at least see it
            else if (distance(home, position) <= DETECTION_RADIUS) {
                sf::Vector2f delta_vect = home - position;
                float new_angle = atan2(delta_vect.y, delta_vect.x);
                last_changed = sf::Time::Zero;
                this->angle = new_angle;
            }

                //If we cannot see it, lets look for markers
            else {
                float new_angle = sampleWorld(markers);
                // if new_angle is a nan it is because there is no markers in the detection radius
                if (!isnan(new_angle)) {
                    this->angle = new_angle;
                } else {
                    this->angle += RandomAngle();
                }
                last_changed = sf::Time::Zero;

            }

        }

    }


    // Actually changing position according to the context-based new angle
    this->angle = normalise_angle(angle);
    this->direction = sf::Vector2<float>(cos(angle), sin(angle));
    sf::Vector2<float> new_position = this->position + this->direction * ANT_SPEED * dt.asSeconds();
    move_to(new_position, dt, obstacles, markers);
    if (last_dropped > .05) {
        if (ToFood) {
            AddMarker(markers, 3, time_since_quitted_home);
        } else { AddMarker(markers, 4, time_since_found_food); }
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

int Ant_::check_env(std::vector<Marker> &foods, float radius) {
    /* Look for the closest piece of food according to the radius*/

    int i = 0;
    float distance_;
    float min_distance = 1000.f;
    int min_index = -1;
    while (foods.size() > i) {
        if (foods[i].marker_type >= 0) {
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

void Ant_::AddMarker(std::vector<Marker> &markers, int type, float time_offset) {

    Marker marker(position, type, time_offset);
    markers.push_back(marker);

}


float Ant_::sampleWorld(std::vector<Marker> markers) {
    /* Calculate the barycenter of markers in the detection radius depending on the ant objective*/

    int type;
    if (ToFood) { type = 4; }
    else { type = 3; }

    float bary_angle = 0.;
    float total_intensity = 0.;
    for (int i = 0; i < markers.size(); i++) {
        if (markers[i].marker_type == type || markers[i].marker_type == 5) {
            float distance_ = distance(markers[i].position, position);
            if (distance_ <= DETECTION_RADIUS && distance_ > EATING_RADIUS) {
                sf::Vector2f target_position = markers[i].position;
                sf::Vector2f delta_vect = target_position - position;
                float markers_angle = atan2(delta_vect.y, delta_vect.x);
                markers_angle = normalise_angle(markers_angle);

                if (markers_angle <= angle + PI / 2 && markers_angle >= angle - PI / 2) {
                    bary_angle += markers[i].get_intensity() * markers_angle;
                    total_intensity += markers[i].get_intensity();
                }
            }
        }
    }

    return bary_angle / (total_intensity);
}

sf::Vector2f Ant_::get_position() {
    return position;
}









