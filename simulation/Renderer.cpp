//
// Created by g0bel1n on 09/12/2021.
//

#include <iostream>
#include "Renderer.h"
#define PI 3.14159265

void Renderer::update(World &world) {

    for(int i=0; i<world.get_nb_food();i++){
        if (world.markers[i].marker_type==-1){
            markers_graphic[i].setFillColor(sf::Color(104,157,113));
        }
        if (world.markers[i].marker_type==2){
            markers_graphic[i].setFillColor(sf::Color::Yellow);
        }
        if (world.markers[i].marker_type==1){
            markers_graphic[i].setFillColor(sf::Color::Red);
        }
        markers_graphic[i].setPosition(world.markers[i].get_position());
    }
    for(int i=0; i<world.get_nb_ants();i++){
        ants_graphics[i].setPosition(world.ants[i].get_position());
        ants_graphics[i].setRotation(world.ants[i].get_angle()*180/PI);
    }
}

Renderer::Renderer(World& world) {

    texture.loadFromFile("../ressources/ant.png");


    for (int i = 0; i < world.get_nb_food(); i++) {
        sf::CircleShape graph_marker = sf::CircleShape(world.markers[0].radius);
        graph_marker.setFillColor(sf::Color(231, 62, 1));
        markers_graphic.push_back(graph_marker);
    }


    for (int i = 0; i < world.get_nb_ants(); i++) {
        sf::Sprite ant_graphics = sf::Sprite();
        ant_graphics.setColor(sf::Color::White);
        ant_graphics.setOrigin(300.,300.f);
        ant_graphics.setTexture(texture);
        ant_graphics.setScale(0.05f, 0.05f);
        std::cout << ant_graphics.getLocalBounds().width <<"\n";
        ants_graphics.push_back(ant_graphics);
    }

}