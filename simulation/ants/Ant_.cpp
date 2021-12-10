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
    float offset = 5.f;
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
    //std::cout<<"ant : " << ant_id <<" ->  " << target <<"\n";

    if (last_changed>sf::seconds(direction_change_delta+ (std::rand()%5)/10.) && target==-1){
        last_changed = sf::Time::Zero;
        this -> angle += (std::rand()%angular_width-angular_width/2)*(PI/180.);
    }
    else if (check_env(markers,detection_radius)>=0 &&  markers[check_env(markers,detection_radius)].marker_type>=0 ) {
        if(check_env(markers,eating_radius)==target && target>=0 ){

            markers[target].marker_type = -1;
            target = -1;
            last_changed = sf::Time::Zero;
            this -> angle += PI;

        }

        else if (target==-1 || target!= check_env(markers,detection_radius)){

            if (target>=0){markers[target].marker_type=1;}
            target = check_env(markers,detection_radius);
            markers[target].marker_type=2;
            std::cout<<"ant : " << ant_id <<" ->  " << target <<"\n";

            sf::Vector2f target_position = markers[target].get_position();
            sf::Vector2f delta_vect = target_position-position;

/*            if ((angle>-PI/4 && angle<PI/4)||(angle>3*PI/4 && angle<5*PI/4)){
                this-> angle -= atan(abs(delta_vect.x/delta_vect.y)) ;
        }
            else{
                this-> angle -= atan(abs(delta_vect.y/delta_vect.x));
        }*/


            angle = atan(delta_vect.y/delta_vect.x);
            if (delta_vect.x<0){
            angle-=PI;}
        }
    }

    if (markers[target].marker_type<0){
        target=-1;
        this -> angle += (std::rand()%angular_width-angular_width/2)*(PI/180.);
    }

    this -> direction = sf::Vector2<float>(cos(angle), sin(angle));
    sf::Vector2<float> new_position = this->position+this->direction*speed*dt.asSeconds();
    move_to(new_position,dt);
    lifetime += dt.asSeconds();
    last_changed+=dt;
}

float Ant_::get_angle() {
    return this->angle;
}

int Ant_::check_env(std::vector<Marker>& markers, float radius) {
    int i = 0;
    float distance_;
    float min_distance=400.f;
    int min_index = -1;
    while (markers.size() > i) {
        distance_ = distance(markers[i].get_position(), position);
        if ( distance_<= radius && distance_<=min_distance ) {
            min_distance = distance_;
            min_index =i;
        }
        i++;
    }
    return min_index;
}








