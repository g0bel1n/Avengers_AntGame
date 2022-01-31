//
// Created by g0bel1n on 07/12/2021.
//



#ifndef ANTS_FIGHT_CLUB_ANTS_H
#define ANTS_FIGHT_CLUB_ANTS_H


#pragma once

#include "../Elements/Marker.h"
#include "../obstacles/Obstacle.h"
#include "../parameters.h"
#include "../Elements/Food.h"


class Ant_ {

public:
    Ant_(sf::Vector2<float> position, sf::Color &color, float ant_speed);

    void
    update(sf::Time dt, std::vector<Chunk> &chunks, std::vector<Obstacle> &obstacles, std::vector<Food> &foods,
           int &food_in_colony, float ant_speed, sf::Vector2f colony_pos);

    float get_lifetime();


    int check_env(std::vector<Food> &foods, float radius);

    void
    move_to(sf::Vector2<float> position, sf::Time dt, std::vector<Obstacle> &obstacles);

    bool ToFood = true;
    sf::Sprite graphics;

    void AddMarker(std::vector<Chunk> &chunks, int type, float time_offset);

    float RandomAngle();

    float sampleWorld(std::vector<Chunk> &chunks);

    int target = -1; // Id of the food the ant is targeting
private:


    // "Identity" of the ant
    float lifetime; // Time the ant has been alive
    float time_since_quitted_home = 0.;
    float time_since_found_food = 0.;
    float ant_speed;

    float last_dropped = 0.; // To regulate the flow of markers
    sf::Vector2f direction;
    sf::Vector2f position;
    float angle = 0.f;
    int times_wall_hit = 0;
    int angular_width = 45; // Angular range in wich the ant can go when random moving
    float direction_change_delta = .05f; // Time to wait before changing direction to avoid epileptic behaviour
    sf::Time last_changed = sf::Time::Zero; // Time since last change of direction


    static bool
    is_valid(sf::Vector2f position, std::vector<Obstacle> &obstacles); // To check if the new position is valid
};


#endif //ANTS_FIGHT_CLUB_ANTS_H

