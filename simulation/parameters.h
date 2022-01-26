//
// Created by g0bel1n on 23/01/2022.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
#ifndef AVENGERS_ANTGAME_SIMULATION_PARAMETERS_H
#define AVENGERS_ANTGAME_SIMULATION_PARAMETERS_H

namespace parameters {
    //WORLD PARAMETERS
    inline constexpr int NB_ANTS{20};
    inline int LENGTH{800};
    inline int WIDTH{1400};

    //ANT PARAMETERS
    inline constexpr float ANT_SPEED{300.};
    inline constexpr float DETECTION_RADIUS{150.};
    inline constexpr float EATING_RADIUS{10.};
    inline constexpr float ANT_LENGTH = 10.f;
    inline constexpr float ANT_WIDTH = 2.f;


    // MARKER PARAMETER
    inline constexpr float DECAY_RATE{0.1}; //Percentage of intensity decrease per second
    inline constexpr float INTENSITY_INCREMENT = 5;
    inline constexpr float RADIUS = 2.f;
    inline constexpr float DETECTION_THRESHOLD = 1.;

    // OBSTACLE PARAMETER

    inline constexpr float MAP_OCCUPATION{0.02};
}

#endif //AVENGERS_ANTGAME_SIMULATION_PARAMETERS_H
#pragma clang diagnostic pop