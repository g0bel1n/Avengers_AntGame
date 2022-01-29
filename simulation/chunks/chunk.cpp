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
    std::cout << "Je suis un chunk en " << grid_pos[0] << grid_pos[1] << std::endl;
}

std::vector<Marker> &Chunk::getMarkers() {
    return markers;
}


std::vector<int> Chunk::getIJ() {
    return grid_pos;
}

