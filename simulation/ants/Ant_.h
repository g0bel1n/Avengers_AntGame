//
// Created by g0bel1n on 07/12/2021.
//



#ifndef ANTS_FIGHT_CLUB_ANTS_H
#define ANTS_FIGHT_CLUB_ANTS_H


#pragma once
#include "../food/Food.h"
#include "../markers/Marker.h"
#include "../obstacles/Obstacle.h"
#include "../simulation_parameters.h"

using namespace parameters;


class Ant_ {

public:
    Ant_(sf::Vector2<float> position, int ant_id, int nb_food);

    void
    update(sf::Time dt, Marker markers [LENGTH][WIDTH], std::vector<Obstacle> &obstacles, std::vector<Food> &foods);

    float get_angle();

    sf::Vector2f get_position();

    float get_lifetime();

    int food_search(std::vector<Food> &foods, float radius);

    float ant_length = 10.f;
    float ant_width = 2.f;

    sf::Vector2<float> size = sf::Vector2f(ant_length, ant_width);

    void
    move_to(sf::Vector2<float> position, sf::Time dt, std::vector<Obstacle> &obstacles, Marker markers [LENGTH][WIDTH]);

    bool switchSkin = false;
    bool ToFood = true;
    sf::Vector2f home;
    sf::Sprite graphics;


    float RandomAngle();

    float MarkersDetection(Marker markers [LENGTH][WIDTH]);

    sf::Texture texture;
    sf::Texture texture_with_food;

    int target = -1;
private:


    int ant_id;
    float lifetime{};
    float time_since_quitted_home = 0.;
    float time_since_found_food = 0.;

    float last_dropped = 0.;
    sf::Vector2f direction;
    sf::Vector2f position;

    float angle = 0.f;
    int times_wall_hit = 0;
    int angular_width = 45;
    float direction_change_delta = .1f;
    sf::Time last_changed = sf::Time::Zero;


    bool is_valid(sf::Vector2f position_to_test, std::vector<Obstacle> &obstacles);
};


#endif //ANTS_FIGHT_CLUB_ANTS_H

