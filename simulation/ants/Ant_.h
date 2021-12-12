//
// Created by g0bel1n on 07/12/2021.
//



#ifndef ANTS_FIGHT_CLUB_ANTS_H
#define ANTS_FIGHT_CLUB_ANTS_H

#include <SFML/Graphics.hpp>
#include "../markers/Marker.h"
#include "../obstacles/Obstacle.h"

class Ant_ {

public:
    Ant_(sf::Vector2<float> position,int ant_id, int width, int length, int nb_food);

    void update(sf::Time dt, std::vector<Marker>& markers, std::vector<Obstacle>& obstacles);

    sf::Vector2f get_position();
    float get_angle() ;
    float get_lifetime() ;

    int check_env(std::vector<Marker>& markers, float radius);

    float ant_length = 50.f;
    float ant_width = 10.f;

    int world_height;
    int world_width;

    sf::Vector2<float> size = sf::Vector2f(ant_length,ant_width);
    void move_to(sf::Vector2<float> position, sf::Time dt, std::vector<Obstacle>& obstacles);
    bool have_food = false;
    bool switchSkin = false;
    bool ToFood=true;
    sf::Vector2f home;
    sf::Sprite graphics;

    void AddMarker(std::vector<Marker>& markers, int type, float time_offset);
    float RandomAngle();
    float sampleWorld(std::vector<Marker> markers);

    sf::Texture texture;
    sf::Texture texture_with_food;

    int target =-1;
private:


    int nb_food;
    int ant_id;
    float lifetime{};
    float time_since_quitted_home =0.;
    float time_since_found_food =0.;

    float last_dropped=0.;
    sf::Vector2f direction;
    sf::Vector2f position;
    float speed = 300.f ;
    float angle = 0.f;
    int times_wall_hit =0;
    int angular_width = 45;
    float direction_change_delta = 0.1f;
    sf::Time last_changed = sf::Time::Zero;

    float detection_radius = 300.f;
    float eating_radius = 10.f;

    bool is_valid(sf::Vector2f position, std::vector<Obstacle>& obstacles);
};


#endif //ANTS_FIGHT_CLUB_ANTS_H

