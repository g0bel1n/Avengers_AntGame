//
// Created by g0bel1n on 23/01/2022.
//

#ifndef AVENGERS_ANTGAME_SIMULATION_PARAMETERS_H
#define AVENGERS_ANTGAME_SIMULATION_PARAMETERS_H

namespace parameters
{
    //WORLD PARAMETERS
    inline constexpr int LENGTH {1400};
    inline constexpr int WIDTH {2500};

    //ANT PARAMETERS
    inline constexpr float ANT_SPEED {300.};
    inline constexpr float DETECTION_RADIUS {300.};
    inline constexpr float EATING_RADIUS {10.};
    inline constexpr float ANT_LENGTH = 10.f;
    inline constexpr float ANT_WIDTH = 2.f;


    // MARKER PARAMETER
    inline constexpr float DECAY_RATE {0.1}; //Percentage of intensity decrease per second
    inline constexpr float INTENSITY_INCREMENT = 5.;
    inline constexpr float RADIUS = 2.f;
    inline constexpr float DETECTION_THRESHOLD = 0.2;
}

#endif //AVENGERS_ANTGAME_SIMULATION_PARAMETERS_H