#ifndef ANTS_FIGHT_CLUB_UTILS_H
#define ANTS_FIGHT_CLUB_UTILS_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include "../simulation/parameters.h"

#define PI 3.14159265


float distancenul(sf::Vector2f vect1, sf::Vector2f vect2 ){
    float distance_x = pow(vect2.x-vect1.x,2);
    float distance_y = pow(vect2.y-vect1.y,2);
    return sqrt(distance_x+distance_y);
}


void fast_erase(std::vector<Marker>& vect, int pos) { /*Using the back-swap trick*/
    auto it = vect.begin() + pos;
    *it = std::move(vect.back());
    vect.pop_back();
}

float distance2(sf::Vector2f vect1, sf::Vector2f vect2 ){
    //(vect2.x-vect1.x)*(vect2.x-vect1.x) + (vect2.y-vect1.y)*(vect2.y-vect1.y)

    return sqrt((vect2.x-vect1.x)*(vect2.x-vect1.x) + (vect2.y-vect1.y)*(vect2.y-vect1.y));
}

float normalise_angle(float angle){

    float n_angle = angle;
    float sign = 1.;
    if (angle<0)sign=-1.;


    while(abs(n_angle)>PI){
        n_angle -= sign*2.*PI;
    }
    return n_angle;
}

float scalar_product(sf::Vector2f vect1, sf::Vector2f vect2){
    return vect1.x*vect2.x + vect1.y*vect2.y;
}

std::vector<std::vector<int>> neighbour_chunks(std::vector<int> chunk_ij) {
    std::vector<std::vector<int>> out;

    for (int i=-1; i<2; i++) {
        for (int j=-1; j<2; j++) {
            if ((chunk_ij[0] + i >= 0) && (chunk_ij[1] + j >= 0) && (chunk_ij[0] + i < parameters::WIDTH/parameters::CHUNKSIZE) && (chunk_ij[1] + j < parameters::LENGTH/parameters::CHUNKSIZE)) {
                out.push_back({chunk_ij[0] + i, chunk_ij[1] + j});
            }
        }
    }
    return out;

}

#endif //ANTS_FIGHT_CLUB_UTILS_H
