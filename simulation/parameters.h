//
// Created by g0bel1n on 23/01/2022.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
#ifndef AVENGERS_ANTGAME_SIMULATION_PARAMETERS_H
#define AVENGERS_ANTGAME_SIMULATION_PARAMETERS_H


namespace parameters {
    //WORLD PARAMETERS
    inline int NB_ANTS{20};
    inline int LENGTH{800};
    inline int WIDTH{1400};
    inline int CHUNKSIZE{250};
    inline int DEFAULT_NB_COLONIES{2};
    inline int DEFAULT_NB_ANTS_PER_COLONY{200};
    inline constexpr int FOOD_FOR_GENERATION{10};
    inline std::vector<sf::Color> DEFAULT_COLORS{sf::Color::White, sf::Color::Black, sf::Color::Green};
    inline std::vector<std::string> DEFAULT_COLORS_STR{"White", "Black", "Green"};
    inline bool markerGraphics{false};
    inline sf::Texture ant_texture;
    inline sf::Texture ant_texture_food;
    inline sf::Texture hole_texture;
    inline int fontsize;


    //ANT PARAMETERS
    inline float DEFAULT_ANT_SPEED{300.};
    inline sf::Vector2f DEFAULT_COLONY_POSITION(LENGTH / 2., 50.);
    inline constexpr float DETECTION_RADIUS{300.};
    inline constexpr float EATING_RADIUS{30.};
    inline float FREEDOM_COEFFICIENT{0.4};
    inline float TURN_COEFFICIENT{0.9};
    inline constexpr float DROPPING_RATE{0.01};
    inline constexpr float DIRECTION_CHANGE_DELTA{0.05};


//MARKER PARAMETERS
    inline constexpr float DECAY_RATE{.15}; // Percentage of intensity decrease per second
    inline constexpr float INTENSITY_INCREMENT = 10;
    inline constexpr float RADIUS = 10.f;
    inline float DETECTION_THRESHOLD = 0.5;
    inline constexpr double MARGINAL_PENALISATION = 7.;

    inline constexpr float DECOMPOSITION_THRESHOLD = 120.;


// OBSTACLE PARAMETERS
    inline constexpr float MAP_OCCUPATION{0.05};
}

#endif //AVENGERS_ANTGAME_SIMULATION_PARAMETERS_H
#pragma clang diagnostic pop    @