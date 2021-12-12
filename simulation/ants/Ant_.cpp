//
// Created by g0bel1n on 07/12/2021.
//

#include "Ant_.h"
#include <cmath>
#include <iostream>
#include <vector>

#include "../../common/utils.h"

#define PI 3.14159265

float Ant_::RandomAngle(){
    return (std::rand()%angular_width-angular_width/2)*(PI/180);
}

Ant_::Ant_(sf::Vector2<float> position, int ant_id,int width, int length, int nb_food) {
    this-> position = position;
    this -> lifetime = 0;
    this -> angle = (std::rand()%360-180)*(PI/180);
    this -> direction = sf::Vector2<float>(cos(angle), sin(angle));
    this->nb_food = nb_food;

    this->ant_id = ant_id;
    this->home = position;

    this->world_width = width;
    this-> world_height = length;



    graphics = sf::Sprite();
    graphics.setColor(sf::Color::White);
    graphics.setOrigin(300.,300.f);

    graphics.setScale(0.05f, 0.05f);
    graphics.setPosition(position);

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

void Ant_::update(sf::Time dt, std::vector<Marker>& markers){

    // To avoid changing direction too often...
    if (last_changed>sf::seconds(direction_change_delta+ (std::rand()%5)/10.)){
        //If looking for food...
        if(ToFood){
            time_since_quitted_home+=dt.asSeconds();

            if (time_since_quitted_home>10){ToFood=false;}
            //Looking for food and didn't see it yet
            if (target==-1) {

                target = check_env(markers, detection_radius);
                //If it detects valid food, let's go to it
                if (target>=0 && markers[target].marker_type == 1 ) {
                    markers[target].changeColor =true;
                    markers[target].marker_type = 2;
                    sf::Vector2f delta_vect = markers[target].position-position;
                    this -> angle = atan(delta_vect.y/delta_vect.x);
                    last_changed=sf::Time::Zero;
                    std::cout<< "4 \n";


                }
                //If the ant can't see the food, it looks for markers left by others
                else{
                    float new_angle = sampleWorld(markers);
                    // 3 times out of 4, the ant takes a random direction
                    // if new_angle is a nan it is because there is no markers in the detection radius
                    if(!isnan(new_angle) && std::rand()%4!=0){
                        this -> angle =new_angle;
                    }
                    else{
                        this->angle += RandomAngle();
                    }
                        last_changed=sf::Time::Zero;
                }
            }

            // If we are looking for food but already going to the target...
            else{
                // Just checking if arrived. If not, keep going...
                if (target==check_env(markers,eating_radius)){

                    markers[target].marker_type = -1;
                    markers[target].changeColor =true;
                    target = -1;
                    have_food = true;
                    ToFood = false;
                    time_since_found_food=0.;
                    switchSkin=true;
                    last_changed = sf::Time::Zero;
                    this -> angle += PI;

                    texture_with_food.loadFromFile("../ressources/ant_with_food.png");
                    graphics.setTexture(texture_with_food);
                    switchSkin=false;

                }
                //if we are not there yet, lets still check if it is avalaible
                else if (markers[target].marker_type==-1){
                    target=-1;

                }

                else if (check_env(markers,detection_radius)!=target){

                    markers[target].marker_type = 1;
                    target=-1;
                }

            }
        }
        //If we are going home...
        else{
            time_since_found_food+=dt.asSeconds();
            //Let's look if we arrived
            if (distance(home,position)<=eating_radius){

                texture.loadFromFile("../ressources/ant.png");
                graphics.setTexture(texture);
                switchSkin=false;

                switchSkin=true;
                ToFood=true;
                have_food=false;

                this->angle += PI + RandomAngle();
                last_changed=sf::Time::Zero;
                time_since_quitted_home=0.;

                std::cout<< "1 \n";

            }

            //If we are not arrived, we might at least see it
            else if (distance(home,position)<=detection_radius){
                sf::Vector2f delta_vect = home-position;
                this -> angle = atan(delta_vect.y/delta_vect.x);
                if (delta_vect.x<0)angle-=PI;
                last_changed=sf::Time::Zero;

                std::cout<< "2 \n";
            }

            //If we cant see it, lets look for clues
            else{

                float new_angle = sampleWorld(markers);
                // 9 times out of 10, the ant takes a random direction
                // if new_angle is a nan it is because there is no markers in the detection radius
                if(!isnan(new_angle) && std::rand()%10!=0){
                    this -> angle =new_angle;
                    //std::cout<<"Following markers \n";
                }
                else{
                    this->angle += RandomAngle();
                    std::cout<< "3 \n";
                }
                last_changed=sf::Time::Zero;

            }

        }

    }


    this -> direction = sf::Vector2<float>(cos(angle), sin(angle));
    sf::Vector2<float> new_position = this->position+this->direction*speed*dt.asSeconds();
    move_to(new_position,dt);
    if (last_dropped>.05) {
        if(ToFood){
            AddMarker(markers,3,time_since_quitted_home);
        }
        else{ AddMarker(markers, 4, time_since_found_food);}
        last_dropped=0.;
    }

    lifetime += dt.asSeconds();
    last_changed+=dt;
    last_dropped+=dt.asSeconds();

    graphics.setPosition(position);
    graphics.setRotation(angle*180/PI);

}

float Ant_::get_angle() {
    return this->angle;
}

int Ant_::check_env(std::vector<Marker>& markers, float radius) {
    int i = 0;
    float distance_;
    float min_distance=1000.f;
    int min_index = -1;
    while (nb_food > i) {
        if(markers[i].marker_type>=0){
            distance_ = distance(markers[i].position, position);
            if ( distance_<= radius && distance_<=min_distance ) {
                min_distance = distance_;
                min_index =i;
            }}
        i++;
    }
    return min_index;
}

void Ant_::AddMarker(std::vector<Marker>& markers, int type, float time_offset){

    Marker marker (position,type, time_offset);
    markers.push_back(marker);

}

float Ant_::sampleWorld(std::vector<Marker> markers) {
    int  type;
    if(ToFood){type =4;}
    else{type = 3;}

    float bary_angle = 0.;
    float total_intensity=0.;
    for (int i=nb_food; i< markers.size();i++){
        if (markers[i].marker_type == type){
            float distance_ = distance(markers[i].position, position);
            if (distance_<= detection_radius&& distance_>eating_radius) {
                sf::Vector2f target_position = markers[i].position;
                sf::Vector2f delta_vect = target_position-position;
                float markers_angle = atan(abs(delta_vect.y/delta_vect.x));
                if(delta_vect.x<0)markers_angle-=PI;

                if(markers_angle<=angle+PI/2 && markers_angle>=angle-PI/2){
                    bary_angle+=markers[i].get_intensity()*markers_angle;
                    total_intensity+=markers[i].get_intensity();
                }



            }
        }
    }

    return bary_angle/(total_intensity);
}










