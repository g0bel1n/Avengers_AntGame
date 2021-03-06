//
// Created by Thomas Kientz on 29/01/2022.
//

#include "chunk.h"
#include "../Elements/Marker.h"
#include <iostream>

Chunk::Chunk() {
    std::cout << "Je suis un chunk sans argument" << std::endl;
}

Chunk::Chunk(std::vector<int> grid_pos) {
    this->grid_pos = grid_pos;
}

Chunk::Chunk(const Chunk& c){
    this->grid_pos = c.grid_pos;
    this->markers = c.markers;
}

std::vector<Marker> &Chunk::getMarkers() {
    return markers;
}


std::vector<int> Chunk::getIJ() {
    return grid_pos;
}

void Chunk::clear() {
    markers.clear();

}

int Chunk::size() {
    return markers.size();

}

void Chunk::add(Marker marker) {
    markers.push_back(marker);
}

