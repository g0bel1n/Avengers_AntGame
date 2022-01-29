#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include "simulation/World.h"
#include "simulation/parameters.h"

//TO DO
// Add saved map feature
using namespace parameters;

using namespace std;


int main() {

    ofstream data_file("../data.csv");
    data_file << "Time;dt loop;dt update;nb_markers;" + to_string(NB_ANTS) << endl;

    bool pause = true;
    int total_food = 0;
    bool began = false;


    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Avengers AntGame");
    sf::Vector2u size = window.getSize();
    WIDTH = size.x;
    LENGTH = size.y;

    sf::Clock clock;
    sf::Clock drawing_clock;
    sf::Clock updating_clock;
    sf::Font font;
    window.setTitle("Avengers AntGame - @G0bel1n");


    //Generating the world
    World world(NB_ANTS, total_food);

    std::cout << "IJ of first : " << world.chunks[0].getIJ()[0] << world.chunks[0].getIJ()[1] << std::endl;

    std::cout << "IJ of IJ 0 : " << get_chunk_ij(world.chunks, 0, 0).getIJ()[0]
              << get_chunk_ij(world.chunks, 0, 0).getIJ()[0] << std::endl;

    if (!font.loadFromFile("../ressources/pricedown.otf")) {
        cout << "Could not load the font...";
    }

    //Loading the grass background
    sf::Texture SoilTex;
    SoilTex.loadFromFile("../ressources/soil.jpeg");

    sf::Sprite Background(SoilTex);
    Background.setPosition(0, 0);
    Background.setScale(WIDTH / 3448., LENGTH / 3448.);

    sf::VertexArray quad(sf::Quads, 4);

    quad[0].position = sf::Vector2f(WIDTH - 800, 10);
    quad[1].position = sf::Vector2f(WIDTH - 10, 10);
    quad[2].position = sf::Vector2f(WIDTH - 10, 410);
    quad[3].position = sf::Vector2f(WIDTH - 800, 410);

    quad[0].color = sf::Color(255, 255, 255, 100);
    quad[1].color = sf::Color(255, 255, 255, 100);
    quad[2].color = sf::Color(255, 255, 255, 100);
    quad[3].color = sf::Color(255, 255, 255, 100);

    sf::Text ant_speed;
    ant_speed.setFont(font);
    ant_speed.setString("ANTS SPEED : " + to_string((int) ANT_SPEED));
    ant_speed.setPosition(WIDTH - 700, 30);
    ant_speed.setCharacterSize(50);
    ant_speed.setFillColor(sf::Color::Black);

    sf::Text colony_size;
    colony_size.setFont(font);
    colony_size.setString("Number of Ants : " + to_string((int) NB_ANTS));
    colony_size.setPosition(WIDTH - 700, 100);
    colony_size.setCharacterSize(50);
    colony_size.setFillColor(sf::Color::Black);

    sf::Text nb_markers;
    nb_markers.setFont(font);
    int total_markers = 0;
    for (int c = 0; c < world.chunks.size(); c++) { total_markers += world.chunks[c].getMarkers().size(); }
    nb_markers.setString("Number of Markers : " + to_string((int) total_markers));
    nb_markers.setPosition(WIDTH - 700, 170);
    nb_markers.setCharacterSize(50);
    nb_markers.setFillColor(sf::Color::Black);

    //Text SFML-Objects that will display :

    // the amount of food available
    sf::Text
            text;
    text.setFont(font);
    text.setString("amount of food available");
    text.setPosition(WIDTH - 700, 310);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Black);

    // The time elapsed
    sf::Text text1;
    text1.setFont(font);
    text1.setString("time elapsed");
    text1.setPosition(WIDTH - 700, 240);;
    text1.setCharacterSize(50);
    text1.setFillColor(sf::Color::Black);

    // The amount of food in the colony
    sf::Text text2;
    text2.setFont(font);
    text2.setString("amount of food in the colony");
    text2.setCharacterSize(40);
    text2.setPosition(COLONY_POS + sf::Vector2f(50., 0.));
    text2.setFillColor(sf::Color::White);


    // Basic commands
    sf::Text text3;
    text3.setFont(font);
    text3.setString(
            "SPACE to start/Pause \nLeft Click to add food \nRight click to add obstacles \nC to  clear the obstacles \nM to  clear the markers \nLeft/Right arrow to Erase/Create new ants \nDown/Up to reduce/increase the speed of the ants ");
    text3.setCharacterSize(60);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(WIDTH / 3., LENGTH / 3.);



    // Texture of the colony Hole
    sf::Texture colony_hole;
    colony_hole.loadFromFile("../ressources/Hole.PNG");

    // Colony Graphic object
    sf::Sprite colony_base;
    colony_base.setPosition(COLONY_POS);
    colony_base.setOrigin(536. / 2., 204.);
    colony_base.setTexture(colony_hole);
    colony_base.setScale(0.2, 0.2);
    cout << colony_base.getLocalBounds().width;

    // The vector Obstacle (Reminder : send it to World.h)
    std::vector<Obstacle> obstacles;


    bool draw_obstacle = false;
    //Main Loop
    while (window.isOpen()) {


        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;


        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            switch (event.type) {
                case (sf::Event::Closed):
                    data_file.close();
                    window.close();
                    break;

                case (sf::Event::KeyPressed):

                    switch (event.key.code) {
                        case (sf::Keyboard::Space):
                            if (pause) pause = !pause;
                            else {
                                cout << "PAUSING";
                                pause = true;
                            }
                            break;
                        case sf::Keyboard::C:
                            obstacles.clear();
                            break;
                        case sf::Keyboard::M:
                            for (int c = 0; c < world.chunks.size(); c++) { world.chunks[c].getMarkers().clear(); }
                            break;
                        case sf::Keyboard::F:
                            world.foods.clear();
                            break;
                        case sf::Keyboard::Q:
                            data_file.close();
                            window.close();
                            system("python3 -m pip install 'matplotlib'");
                            system("python3 -m pip install 'pandas'");
                            system("python3 '../plot_data.py'");
                            system("open ../data.png");
                            break;
                        case sf::Keyboard::Up:
                            ANT_SPEED += 100.;
                            ant_speed.setString("ANTS SPEED : " + to_string((int) ANT_SPEED));
                            break;
                        case sf::Keyboard::Down:
                            if (ANT_SPEED >= 100.)ANT_SPEED -= 100.;
                            ant_speed.setString("ANTS SPEED : " + to_string((int) ANT_SPEED));
                            break;
                        case sf::Keyboard::Right:
                            world.add_ant();
                            NB_ANTS += 1;
                            colony_size.setString("Number of Ants : " + to_string((int) NB_ANTS));
                            break;
                        case sf::Keyboard::Left:
                            if (NB_ANTS >= 1) {
                                world.ants.pop_back();
                                NB_ANTS -= 1;
                                colony_size.setString("Number of Ants : " + to_string((int) NB_ANTS));
                            }
                            break;
                        case sf::Keyboard::D:
                            COLONY_POS = (sf::Vector2f) sf::Mouse::getPosition(window);
                            colony_base.setPosition(COLONY_POS);
                            text2.setPosition(COLONY_POS + sf::Vector2f(50., 0.));
                            window.draw(colony_base);
                            if (!began) {
                                world.ants.clear();
                                int recreate_N_ants = 0;
                                while (recreate_N_ants <= NB_ANTS) {
                                    world.add_ant();
                                    recreate_N_ants += 1;
                                }

                            }
                            break;
                    }

                case (sf::Event::MouseButtonPressed) :

                    if (event.mouseButton.button == sf::Mouse::Right) {
                        draw_obstacle = true;

                        Obstacle obstacle(sf::Vector2f(event.mouseButton.x,
                                                       event.mouseButton.y),
                                          LENGTH * MAP_OCCUPATION);
                        obstacle.texture.loadFromFile("../ressources/rock.jpeg");
                        obstacles.push_back(obstacle);

                    }

                    if (event.mouseButton.button == sf::Mouse::Left) {

                        draw_obstacle = false;


                        // The following for-loop is there to add a "block" of food, instead of a line
                        sf::Vector2f to_pos = sf::Vector2f(event.mouseButton.x - 20, event.mouseButton.y - 20);
                        float x_offset = 10.;

                        for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {

                                world.AddFood(to_pos + sf::Vector2f(i * x_offset, j * x_offset));
                            }
                        }
                        total_food += 10;
                    }
                    break;

                case (sf::Event::MouseButtonReleased):
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        draw_obstacle = false;
                    }
                    break;

                case sf::Event::MouseMoved:
                    if (draw_obstacle) {


                        Obstacle obstacle(sf::Vector2f(event.mouseMove.x,
                                                       event.mouseMove.y),
                                          LENGTH * MAP_OCCUPATION);
                        obstacle.texture.loadFromFile("../ressources/rock.jpeg");
                        obstacles.push_back(obstacle);

                    }
                    break;
            }

        }
        // Calculating the time elapsed during last loop
        sf::Time dt = clock.restart();
        if (!pause) {

            // Might need to decrease the number of markers when passing a critical value (aroud 3500)
            /*if (world.markers.size() > 3000) {
                for (int i = 0; i <= 100; i++)world.markers.erase(world.markers.begin());
            }*/

            began = true;

            text.setString("Food available: " + to_string(world.get_food_available()));

            float time = world.ants[0].get_lifetime();

            // To display a time in minutes
            int minutes = 0;
            while (time > 60.) {
                time -= 60.;
                minutes += 1;
            }

            //These objects need to be updated only when the simulation is running
            text1.setString(
                    "Time elapsed :  " + to_string(minutes) + "  min  " + to_string(time).substr(0, 3));
            text2.setString(to_string(food_in_colony));

            updating_clock.restart();
            world.update(dt, obstacles);
            float updating_delay = updating_clock.restart().asSeconds();
            if (updating_delay > 0.3)cout << "updating time" << updating_delay << "\n";

            int total_markers = 0;
            for (int c = 0; c < world.chunks.size(); c++) { total_markers += world.chunks[c].getMarkers().size(); }
            nb_markers.setString("Number of Markers : " + to_string((int) total_markers));

            data_file
                    << to_string(minutes) + ":" + to_string(time) + ";" + to_string(dt.asSeconds()) + ";" +
                       to_string(updating_delay) + ";" + to_string(total_markers) << endl;
        }


        window.clear();

        drawing_clock.restart();
        // Drawing every object
        window.draw(Background);
        window.draw(colony_base);
        for (auto &chunk: world.chunks) {
            for (auto &marker: chunk.getMarkers()) { window.draw(marker.graphic); }
        }
        for (auto &ant: world.ants) { window.draw(ant.graphics); }
        for (auto &food: world.foods) { window.draw(food.graphic); }
        for (auto &obstacle: obstacles) { window.draw(obstacle.graphics, &obstacle.texture); }

        window.draw(quad);

        window.draw(text);
        window.draw(text1);
        window.draw(text2);
        window.draw(ant_speed);
        window.draw(colony_size);
        window.draw(colony_base);
        window.draw(nb_markers);

        float drawing_delay = drawing_clock.restart().asSeconds();
        if (drawing_delay > 0.2)cout << "drawing time" << drawing_delay << "\n";
        if (pause) window.draw(text3);

        window.display();

    }
    return 0;
}



