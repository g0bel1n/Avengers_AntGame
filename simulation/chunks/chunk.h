//
// Created by Thomas Kientz on 29/01/2022.
//

#ifndef AVENGERS_ANTGAME_CHUNK_H
#define AVENGERS_ANTGAME_CHUNK_H

#include <SFML/Graphics.hpp>

class Marker;

class Chunk {
public:
    Chunk();

    Chunk(std::vector<int> grid_pos);
    Chunk(const Chunk& c);

    std::vector<Marker> &getMarkers();

    std::vector<int> getIJ();

    void clear();

    void add(Marker marker);

    int size();

private:
    std::vector<int> grid_pos;
    std::vector<Marker> markers;

};


#endif //AVENGERS_ANTGAME_CHUNK_H
