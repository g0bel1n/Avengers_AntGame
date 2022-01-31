//
// Created by g0bel1n on 07/12/2021.
//
#pragma once

#include "Ant_.h"
#include <cmath>
#include <iostream>
#include "../../common/utils.h"
#include "../Colony.h"


using namespace parameters;

#define PI 3.14159265

float Ant_::RandomAngle() {

    return ((float) rand() / RAND_MAX - 1.0 / 2.0) * angular_width * (PI / 180);
}

Ant_::Ant_(sf::Vector2<float> position, sf::Color &color, float ant_speed) {
    this->position = position;
    this->lifetime = 0;
    this->angle = (std::rand() % 360 - 180) * (PI / 180);
    this->direction = sf::Vector2<float>(cos(angle), sin(angle));
    this->ant_speed = ant_speed;

    graphics = sf::Sprite();

    graphics.setTexture(ant_texture);
    graphics.setColor(color);
    graphics.setOrigin(248., 159.f);

    graphics.setScale(0.05f, 0.05f);
    graphics.setPosition(position);
}

float Ant_::get_lifetime() {
    return this->lifetime;
}

bool Ant_::is_valid(sf::Vector2f position, std::vector<Obstacle> &obstacles) {
    float offset = 5.f;
    if (!((position.x > 0 + offset) && (position.x + offset < WIDTH) && (position.y > 0 + offset) &&
          (position.y + offset < LENGTH))) {
        return false;
    }
    for (auto &obstacle: obstacles) {
        if (position.x >= obstacle.graphics[0].position.x && position.x <= obstacle.graphics[1].position.x &&
            position.y >= obstacle.graphics[0].position.y && position.y <= obstacle.graphics[2].position.y) {
            return false;
        }

    }
    return true;
}

void Ant_::move_to(sf::Vector2<float> new_position, sf::Time dt, std::vector<Obstacle> &obstacles) {
    /* Check if the position we are trying to implement is valid, e.g. no obstacle */

    if (is_valid(new_position, obstacles)) {
        this->position = new_position;
    } else {
        this->angle += PI + RandomAngle();
        this->direction = sf::Vector2<float>(cos(angle), sin(angle));
        this->position += direction * ant_speed * dt.asSeconds();
        times_wall_hit++;
    }

}

void
Ant_::update(sf::Time dt, std::vector<Chunk> &chunks, std::vector<Obstacle> &obstacles, std::vector<Food> &foods,
             int &food_in_colony, float ant_speed, sf::Vector2f colony_pos) {

    this->ant_speed = ant_speed;

    if (distance(colony_pos, position) <= DETECTION_RADIUS) { time_since_quitted_home = 0; }
    //if (check_env(foods, DETECTION_RADIUS) != -1) { time_since_found_food = 0; }


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
                if (target >= 0 && foods[target].state == 1) {
                    //foods[target].isTargeted();
                    sf::Vector2f delta_vect = foods[target].position - position;
                    float new_angle = atan2(delta_vect.y, delta_vect.x);
                    this->angle = new_angle;
                    last_changed = sf::Time::Zero;

                }
                    //If the ant can't see the food, it looks for markers left by others
                else {
                    float new_angle = sampleWorld(chunks);
                    // if new_angle is a nan it is because there is no markers in the detection radius
                    if (!isnan(new_angle)) {
                        this->angle = FREEDOM_COEFFICIENT * (RandomAngle() + angle) + (1.0 - FREEDOM_COEFFICIENT) *
                                                                                      (TURN_COEFFICIENT * new_angle +
                                                                                       (1.0 - TURN_COEFFICIENT) *
                                                                                       angle);
                    } else {
                        this->angle += RandomAngle();

                    }
                    last_changed = sf::Time::Zero;
                }
            }

                // If we are looking for food but already going to the target...
            else {
                // Just checking if arrived. If not, keep going...
                if (check_env(foods, EATING_RADIUS) != -1) {

                    //foods[target].isEaten();
                    foods.pop_back();
                    target = -1;
                    ToFood = false;
                    time_since_found_food = 0.;
                    //switchSkin = true;
                    last_changed = sf::Time::Zero;
                    this->angle += PI + RandomAngle();;
                    graphics.setTexture(ant_texture_food);
                    //switchSkin = false;

                }
                    //if we are not there yet, lets still check if it is available
                    /*else if (foods[target].state == 0) {
                        target = -1;*/

                    //}
                else if (check_env(foods, DETECTION_RADIUS) == -1) {

                    //foods[target].HasBeenForgotten();
                    target = -1;
                }

            }
        }
            //If we are going home...
        else {
            time_since_found_food += dt.asSeconds();
            //Let's look if we arrived
            if (distance(colony_pos, position) <= 2 * dt.asSeconds() * ant_speed) {

                // Changing skin

                graphics.setTexture(ant_texture);
                //switchSkin = false;

                food_in_colony++;

                //Changing Objective
                ToFood = true;

                //Going away
                this->angle += PI + RandomAngle();
                last_changed = sf::Time::Zero;
                time_since_quitted_home = 0.;


            }

                //If we are not arrived, we might at least see it
            else if (distance(colony_pos, position) <= DETECTION_RADIUS) {
                sf::Vector2f delta_vect = colony_pos - position;
                float new_angle = atan2(delta_vect.y, delta_vect.x);
                last_changed = sf::Time::Zero;
                this->angle = new_angle;
            }

                //If we cannot see it, lets look for markers
            else {
                float new_angle = sampleWorld(chunks);
                // if new_angle is a nan it is because there is no markers in the detection radius
                if (!isnan(new_angle)) {
                    this->angle = FREEDOM_COEFFICIENT * (RandomAngle() + angle) + (1.0 - FREEDOM_COEFFICIENT) *
                                                                                  (TURN_COEFFICIENT * new_angle +
                                                                                   (1.0 - TURN_COEFFICIENT) * angle);
                } else {
                    this->angle += RandomAngle();
                }
                last_changed = sf::Time::Zero;

            }

        }

    }


    // Actually changing position according to the context-based new angle
    this->angle = constrainAngle(angle);

    this->direction = sf::Vector2<float>(cos(angle), sin(angle));
    sf::Vector2<float> new_position = this->position + this->direction * ant_speed * dt.asSeconds();
    move_to(new_position, dt, obstacles);
    if (last_dropped > .005) {
        if (ToFood) {
            AddMarker(chunks, 1, time_since_quitted_home);
        } else { AddMarker(chunks, 2, time_since_found_food); }
        last_dropped = 0.;
    }

    lifetime += dt.asSeconds();
    last_changed += dt;
    last_dropped += dt.asSeconds();

    graphics.setPosition(position);
    graphics.setRotation(angle * 180 / PI);

}

int Ant_::check_env(std::vector<Food> &foods, float radius) {
    /* Look for the closest piece of food according to the radius*/

    int i = 0;
    float distance_;
    float min_distance = 1000.f;
    int min_index = -1;
    while (foods.size() > i) {
        if (foods[i].state > 0) {
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

void Ant_::AddMarker(std::vector<Chunk> &chunks, int type, float time_offset) {

    Chunk &fatherChunk = get_chunk_pos(chunks, position);
    fatherChunk.add(Marker(position, type, &fatherChunk, time_offset));

}

int thread_i;

float Ant_::sampleWorld(std::vector<Chunk> &chunks) {
    /* Calculate the barycenter of markers in the detection radius depending on the ant objective*/

    int type;
    if (ToFood) { type = 2; }
    else { type = 1; }

    float bary_angle = 0.;
    float total_intensity = 0.;
    std::vector<std::vector<int>> close_chunks = neighbour_chunks(
            {(int) (position.x / CHUNKSIZE), (int) (position.y / CHUNKSIZE)});

    for (auto &close_chunk: close_chunks) {
        std::vector<Marker> &markers = get_chunk_ij(chunks, close_chunk[0], close_chunk[1]).getMarkers();


        for (Marker &marker: markers) {

            if (marker.state == type) {
                float distance_ = distance(marker.position, position);
                if (distance_ <= DETECTION_RADIUS) {
                    sf::Vector2f target_position = marker.position;
                    sf::Vector2f delta_vect = target_position - position;
                    float markers_angle = atan2(delta_vect.y, delta_vect.x);
                    markers_angle = constrainAngle(markers_angle);

                    if (abs(markers_angle - constrainAngle(angle)) <= PI * 2. / 3) {
                        bary_angle += marker.get_intensity() * markers_angle;
                        total_intensity += marker.get_intensity();
                    }
                }
            }
        }
    }
    return bary_angle / (total_intensity);
}









