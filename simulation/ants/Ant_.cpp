//
// Created by g0bel1n on 07/12/2021.
//

#include "Ant_.h"
#include <cmath>
#include <iostream>
#include <vector>

#include "../../common/utils.h"

#define PI 3.14159265


Ant_::Ant_(sf::Vector2<float> position, int ant_id,int width, int length) {
    this-> position = position;
    this -> lifetime = 0;
    this -> angle = (std::rand()%360-180)*(PI/180);
    this -> direction = sf::Vector2<float>(cos(angle), sin(angle));

    this->ant_id = ant_id;


    this->world_width = width;
    this-> world_height = length;

}

sf::Vector2<float> Ant_::get_position() {
    return this->position;
}

float Ant_::get_lifetime()  {
    return this->lifetime;
}
bool Ant_::is_valid(sf::Vector2f position){
    float offset = 30.f;
    return (position.x>0+offset) && (position.x+offset<world_height) && (position.y>0+offset) && (position.y+offset<world_width);
}

void Ant_::move_to(sf::Vector2<float> new_position, sf::Time dt) {

  if (is_valid(new_position)) {
        this->position = new_position;
    }
    else{
        this->angle -= 3*PI/4;
        this -> direction = sf::Vector2<float>(cos(angle), sin(angle));
        this->position += direction*speed*dt.asSeconds();
        times_wall_hit++;
        }

}



/*int Ant_::is_food(float radius, std::vector<Marker> markers){
    // iterate on the list
    for (int i =0; i <10;i++) {
        if (pow(markers[i].get_position().x-markers[i].radius- position.x, 2.0) + pow(markers[i].get_position()
        .y-markers[i].radius- position.y, 2.0) <= radius) {

            return i;
        }

    }
    return -1;
}*/



void Ant_::update(sf::Time dt, std::vector<Marker>& markers) {

    //int isfood = is_food(detection_radius, markers);

    if (last_changed>sf::seconds(direction_change_delta+ (std::rand()%5)/10.)){
        last_changed = sf::Time::Zero;
        this -> angle += (std::rand()%angular_width-angular_width/2)*(PI/180.);
        this -> direction = sf::Vector2<float>(cos(angle), sin(angle));
    }
    else if (check_env(markers)>=0 && !(target>0)){
        std::cout<<"seen";
        target = check_env(markers);
        sf::Vector2f target = markers[check_env(markers)].get_position();
        sf::Vector2f delta_vect = target-position;
        if ((angle>-PI/4 && angle<PI/4)||(angle>3*PI/4 && angle<5*PI/4)){
            this-> angle += atan(abs(delta_vect.x/delta_vect.y));
        }
        else{
            this-> angle += atan(abs(delta_vect.x/delta_vect.y));
        }
        this -> direction = sf::Vector2<float>(cos(angle), sin(angle));
    }

    sf::Vector2<float> new_position = this->position+this->direction*speed*dt.asSeconds();
    move_to(new_position,dt);
    lifetime += dt.asSeconds();
    last_changed+=dt;
}

float Ant_::get_angle() {
    return this->angle;
}

int Ant_::check_env(std::vector<Marker>& markers) {

    for (int i = 0; i < markers.size(); i++) {
        if (distance(markers[i].get_position(), position) <= detection_radius) {
            return i;
        }
        return -1;
    }
}








