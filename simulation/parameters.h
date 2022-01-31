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
    inline sf::Texture hole_texture;


    //ANT PARAMETERS
    inline float DEFAULT_ANT_SPEED{300.};
    inline sf::Vector2f DEFAULT_COLONY_POSITION(LENGTH / 2., 50.);
    inline constexpr float DETECTION_RADIUS{250.};
    inline constexpr float EATING_RADIUS{30.};
    inline float FREEDOM_COEFFICIENT{0.2};
    inline float TURN_COEFFICIENT{1.};


//MARKER PARAMETERS
    inline constexpr float MIN_DECAY{.07}; //Percentage of intensity decrease per second
    inline constexpr float MAX_DECAY{.17};
    inline constexpr float DECAY_DECAY{.2};

    inline constexpr float BASE_INTENSITY = 5;
    inline constexpr float RADIUS = 10.f;
    inline float DETECTION_THRESHOLD = 1.5;

    inline constexpr float DECOMPOSITION_THRESHOLD = 120.;


// OBSTACLE PARAMETERS
    inline constexpr float MAP_OCCUPATION{0.05};
}

#endif //AVENGERS_ANTGAME_SIMULATION_PARAMETERS_H
#pragma clang diagnostic pop