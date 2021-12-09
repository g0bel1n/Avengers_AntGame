//
// Created by g0bel1n on 07/12/2021.
//

#include "Ant_.h"
#include <cmath>
#include <iostream>
#include <vector>
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
        this->angle -= PI/2;
        this -> direction = sf::Vector2<float>(cos(angle), sin(angle));
        this->position += direction*speed*dt.asSeconds();
        times_wall_hit++;
        }

}



int Ant_::is_food(float radius, std::vector<Marker> markers){
    // iterate on the list
    for (int i =0; i <10;i++) {
        if (pow(markers[i].get_position().x-markers[i].radius- position.x, 2.0) + pow(markers[i].get_position()
        .y-markers[i].radius- position.y, 2.0) <= radius) {

            return i;
        }

    }
    return -1;
}



void Ant_::update(sf::Time dt, std::vector<Marker>& markers) {

    //int isfood = is_food(detection_radius, markers);

    if (last_changed>sf::seconds(direction_change_delta+ (std::rand()%5)/10.)){
        last_changed = sf::Time::Zero;
        this -> angle += (std::rand()%angular_width-angular_width/2)*(PI/180.);
        this -> direction = sf::Vector2<float>(cos(angle), sin(angle));
    }



/*    else if (isfood>=0 && markers[isfood].marker_type ==1 ){

        sf::Vector2f delta_vect = (markers[isfood].get_position() - position);
        this->angle = atan(delta_vect.y/delta_vect.x);
        if (delta_vect.x<0){angle-=PI;}
        std::cout<<"Angle vis à vis de la target  :  " << angle << "\n";
        this -> direction = sf::Vector2<float>(cos(angle), sin(angle));
        last_changed = sf::Time::Zero;
        std::cout << "is food" << isfood << "\n";
        hunting=true;
        markers[isfood].marker_type=0;

        position += direction*speed*dt.asSeconds();
        move_to(position,dt);

    }*/

    sf::Vector2<float> new_position = this->position+direction*speed*dt.asSeconds();
    move_to(new_position,dt);
    lifetime += dt.asSeconds();
    last_changed+=dt;
}

float Ant_::get_angle() {
    return this->angle;
}








