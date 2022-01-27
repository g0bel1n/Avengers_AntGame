//
// Created by g0bel1n on 07/12/2021.
//



#ifndef ANTS_FIGHT_CLUB_ANTS_H
#define ANTS_FIGHT_CLUB_ANTS_H


#pragma once

#include "../markers/Marker.h"
#include "../obstacles/Obstacle.h"
#include "../parameters.h"


class Ant_ {

public:
    Ant_(sf::Vector2<float> position, int ant_id);

    void
    update(sf::Time dt, std::vector<Marker> &markers, std::vector<Obstacle> &obstacles, std::vector<Marker> &foods);

    float get_angle();

    sf::Vector2f get_position();

    float get_lifetime();

    int check_env(std::vector<Marker> &markers, float radius);


    sf::Vector2<float> size = sf::Vector2f(parameters::ANT_LENGTH, parameters::ANT_WIDTH);

    void
    move_to(sf::Vector2<float> position, sf::Time dt, std::vector<Obstacle> &obstacles, std::vector<Marker> &markers);

    bool switchSkin = false;
    bool ToFood = true;
    sf::Sprite graphics;

    void AddMarker(std::vector<Marker> &markers, int type, float time_offset);

    float RandomAngle();

    float sampleWorld(std::vector<Marker> markers);

    sf::Texture texture;
    sf::Texture texture_with_food;

    int target = -1; // Id of the food the ant is targeting
private:


    int ant_id; // "Identity" of the ant
    float lifetime; // Time the ant has been alive
    float time_since_quitted_home = 0.;
    float time_since_found_food = 0.;

    float last_dropped = 0.; // To regulate the flow of markers
    sf::Vector2f direction;
    sf::Vector2f position;
    float angle = 0.f;
    int times_wall_hit = 0;
    int angular_width = 45; // Angular range in wich the ant can go when random moving
    float direction_change_delta = .1f; // Time to wait before changing direction to avoid epileptic behaviour
    sf::Time last_changed = sf::Time::Zero; // Time since last change of direction


    bool is_valid(sf::Vector2f position, std::vector<Obstacle> &obstacles); // To check if the new position is valid
};


#endif //ANTS_FIGHT_CLUB_ANTS_H

