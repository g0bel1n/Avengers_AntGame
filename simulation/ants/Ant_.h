//
// Created by g0bel1n on 07/12/2021.
//



#ifndef ANTS_FIGHT_CLUB_ANTS_H
#define ANTS_FIGHT_CLUB_ANTS_H

#include <SFML/Graphics.hpp>
#include "../markers/Marker.h"

class Ant_ {

public:
    Ant_(sf::Vector2<float> position,int ant_id, int width, int length);

    void update(sf::Time dt, std::vector<Marker>& markers);

    sf::Vector2f get_position();
    float get_angle() ;
    float get_lifetime() ;

    int is_food(float radius, std::vector<Marker> markers);

    int check_env(std::vector<Marker>& markers, float radius);

    float ant_length = 50.f;
    float ant_width = 10.f;

    int world_height;
    int world_width;

    sf::Vector2<float> size = sf::Vector2f(ant_length,ant_width);
    bool hunting = false;
    void move_to(sf::Vector2<float> position, sf::Time dt);

private:


    int ant_id;
    int target =-1;
    float lifetime{};
    sf::Vector2f direction;
    sf::Vector2f position;
    float speed = 50.f ;
    float angle = 0.f;
    int times_wall_hit =0;
    int angular_width = 45;
    float direction_change_delta = 0.1f;
    sf::Time last_changed = sf::Time::Zero;

    float detection_radius = 50.f;
    float eating_radius = 10.f;

    bool is_valid(sf::Vector2f position);
};


#endif //ANTS_FIGHT_CLUB_ANTS_H

