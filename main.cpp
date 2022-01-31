#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include "simulation/Colony.h"
#include "simulation/World.h"
#include "simulation/parameters.h"

//TO DO
// Add saved map feature
// CLEAN THE CODE (delete useless funcs etc)


using namespace parameters;

using namespace std;


int main() {

    ofstream data_file("../data.csv");
    data_file << "Time;dt loop;dt update;nb_markers;" + to_string(DEFAULT_NB_ANTS_PER_COLONY) << endl;

    bool pause = true;
    int total_food = 0;
    bool began = false;


    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Avengers AntGame");
    sf::Vector2u size = window.getSize();

    if (size.x < 3500)WIDTH = size.x;
    if (size.y < 2000)LENGTH = size.y;

    fontsize = LENGTH * 3e-2;

    sf::Clock clock;
    sf::Clock drawing_clock;
    sf::Clock updating_clock;
    sf::Font font;
    if (!font.loadFromFile("../ressources/pricedown.otf")) {
        cout << "Could not load the font...";
    }
    window.setTitle("Avengers AntGame - @G0bel1n");

    ant_texture.loadFromFile("../ressources/ant.png");
    ant_texture_food.loadFromFile("../ressources/ant_food.png");
    hole_texture.loadFromFile("../ressources/Hole.PNG");



    //Generating the world
    World world = World(1);




    //Loading the grass background
    sf::Texture SoilTex;
    SoilTex.loadFromFile("../ressources/soil.jpeg");

    sf::Sprite Background(SoilTex);
    Background.setPosition(0, 0);
    Background.setScale(WIDTH / 3448., LENGTH / 3448.);

    sf::VertexArray colony_info_quad(sf::Quads, 4);

    colony_info_quad[0].position = sf::Vector2f(WIDTH * 0.75, 0.03 * LENGTH + fontsize);
    colony_info_quad[1].position = sf::Vector2f(WIDTH * 0.75 + 12 * fontsize, 0.03 * LENGTH + fontsize);
    colony_info_quad[2].position = sf::Vector2f(WIDTH * 0.75 + 12 * fontsize,
                                                0.03 * LENGTH + 6 * (fontsize + 0.006 * LENGTH));
    colony_info_quad[3].position = sf::Vector2f(WIDTH * 0.75, 0.03 * LENGTH + 6 * (fontsize + 0.006 * LENGTH));

    colony_info_quad[0].color = sf::Color(255, 255, 255, 100);
    colony_info_quad[1].color = sf::Color(255, 255, 255, 100);
    colony_info_quad[2].color = sf::Color(255, 255, 255, 100);
    colony_info_quad[3].color = sf::Color(255, 255, 255, 100);

    sf::VertexArray simulation_info_quad(sf::Quads, 4);

    simulation_info_quad[0].position = sf::Vector2f(WIDTH / 2 - WIDTH / 3, LENGTH * 0.91);
    simulation_info_quad[1].position = sf::Vector2f(WIDTH / 2 + WIDTH / 3, LENGTH * 0.91);
    simulation_info_quad[2].position = sf::Vector2f(WIDTH / 2 + WIDTH / 3, LENGTH * 0.97);
    simulation_info_quad[3].position = sf::Vector2f(WIDTH / 2 - WIDTH / 3, LENGTH * 0.97);

    simulation_info_quad[0].color = sf::Color(255, 255, 255, 100);
    simulation_info_quad[1].color = sf::Color(255, 255, 255, 100);
    simulation_info_quad[2].color = sf::Color(255, 255, 255, 100);
    simulation_info_quad[3].color = sf::Color(255, 255, 255, 100);


    sf::Text colony_active;
    colony_active.setFont(font);
    colony_active.setString(DEFAULT_COLORS_STR[0] + " colony");
    colony_active.setPosition(WIDTH * 0.76, 0.03 * LENGTH + (fontsize + 0.006 * LENGTH));
    colony_active.setCharacterSize(fontsize);
    colony_active.setFillColor(sf::Color::Black);

    sf::Text ant_speed;
    ant_speed.setFont(font);
    ant_speed.setString("ANTS SPEED : " + to_string((int) DEFAULT_ANT_SPEED));
    ant_speed.setPosition(WIDTH * 0.76, 0.03 * LENGTH + 2 * (fontsize + 0.006 * LENGTH));
    ant_speed.setCharacterSize(fontsize);
    ant_speed.setFillColor(sf::Color::Black);

    sf::Text colony_size;
    colony_size.setFont(font);
    colony_size.setString("Number of Ants : " + to_string((int) DEFAULT_NB_ANTS_PER_COLONY));
    colony_size.setPosition(WIDTH * 0.76, 0.03 * LENGTH + 3 * (fontsize + 0.006 * LENGTH));
    colony_size.setCharacterSize(fontsize);
    colony_size.setFillColor(sf::Color::Black);

    sf::Text
            ant_generated;
    ant_generated.setFont(font);
    ant_generated.setString("Ants generated");
    ant_generated.setPosition(WIDTH * 0.76, 0.03 * LENGTH + 4 * (fontsize + 0.006 * LENGTH));
    ant_generated.setCharacterSize(fontsize);
    ant_generated.setFillColor(sf::Color::Black);

    // The amount of food in the colony
    sf::Text food_in_col;
    food_in_col.setFont(font);
    food_in_col.setString("0");
    food_in_col.setPosition(WIDTH * 0.76, 0.03 * LENGTH + 5 * (fontsize + 0.006 * LENGTH));;
    food_in_col.setCharacterSize(fontsize);
    food_in_col.setFillColor(sf::Color::Black);

    sf::Text nb_markers;
    nb_markers.setFont(font);
    int total_markers = 0;
    nb_markers.setString("Number of markers : 0");
    nb_markers.setPosition(WIDTH / 2 - WIDTH / 3 + 10, LENGTH * 0.93);
    nb_markers.setCharacterSize(fontsize);
    nb_markers.setFillColor(sf::Color::Black);

    //Text SFML-Objects that will display :

    // the amount of food available
    sf::Text
            text;
    text.setFont(font);
    text.setString("Food available : 0");
    text.setPosition((WIDTH / 2 - WIDTH / 3) * 5. / 2, LENGTH * 0.93);
    text.setCharacterSize(fontsize);
    text.setFillColor(sf::Color::Black);



    // The time elapsed
    sf::Text text1;
    text1.setFont(font);
    text1.setString("time elapsed");
    text1.setPosition((WIDTH / 2 - WIDTH / 3) * 11. / 3, LENGTH * 0.93);;
    text1.setCharacterSize(fontsize);
    text1.setFillColor(sf::Color::Black);





    // Basic commands
    sf::Text text3;
    text3.setFont(font);
    text3.setString(
            "SPACE to start/Pause \nLeft Click to add food \nRight click to add obstacles \nC to  clear the obstacles \nM to  clear the markers \nLeft/Right arrow to Erase/Create new ants \nDown/Up to reduce/increase the speed of the ants \nG to toggle marker graphics ");
    text3.setCharacterSize(fontsize);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(WIDTH / 3., LENGTH / 3.);

    int active_colony = 0;


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
                        case (sf::Keyboard::Enter):
                            if (active_colony + 1 == world.colonies.size())active_colony = 0;
                            else active_colony++;
                            ant_speed.setString(
                                    "ANTS SPEED : " + to_string((int) world.colonies[active_colony].ant_speed));
                            colony_size.setString(
                                    "Number of Ants : " + to_string((int) world.colonies[active_colony].get_nb_ants()));
                            food_in_col.setString("Food in colony : " +
                                                  to_string((int) world.colonies[active_colony].food_in_colony));
                            ant_generated.setString("Ants generated : " +
                                                    to_string((int) world.colonies[active_colony].ant_generated));

                            colony_active.setString(DEFAULT_COLORS_STR[active_colony] + " colony");
                            break;
                        case (sf::Keyboard::Space):
                            if (pause) pause = !pause;
                            else {
                                cout << "PAUSING";
                                pause = true;
                            }
                            break;
                        case sf::Keyboard::C:
                            world.obstacles.clear();
                            break;
                        case sf::Keyboard::M:
                            for (auto &colony: world.colonies) {
                                for (auto &chunk: colony.chunks) chunk.clear();
                            }
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
                            world.colonies[active_colony].ant_speed += 100.;
                            ant_speed.setString(
                                    "ANTS SPEED : " + to_string((int) world.colonies[active_colony].ant_speed));
                            break;
                        case sf::Keyboard::Down:
                            if (world.colonies[active_colony].ant_speed >= 100.)
                                world.colonies[active_colony].ant_speed -= 100.;
                            ant_speed.setString(
                                    "ANTS SPEED : " + to_string((int) world.colonies[active_colony].ant_speed));
                            break;
                        case sf::Keyboard::Right:
                            world.colonies[active_colony].add_ant();
                            colony_size.setString(
                                    "Number of Ants : " + to_string((int) world.colonies[active_colony].get_nb_ants()));
                            break;
                        case sf::Keyboard::Left:
                            if (world.colonies[active_colony].get_nb_ants() >= 1) {
                                world.colonies[active_colony].delete_ant();
                                colony_size.setString("Number of Ants : " +
                                                      to_string((int) world.colonies[active_colony].get_nb_ants()));
                            }
                            break;

                        case sf::Keyboard::G:
                            markerGraphics = !markerGraphics;
                            break;

                        case sf::Keyboard::D:

                            sf::Vector2f colony_pos = (sf::Vector2f) sf::Mouse::getPosition(window);

                            world.colonies[active_colony].colony_base.setPosition(colony_pos);
                            world.colonies[active_colony].colony_pos = colony_pos;
                            window.draw(world.colonies[active_colony].colony_base);
                            if (!began) {
                                world.colonies[active_colony].ants.clear();
                                int recreate_N_ants = 0;
                                while (recreate_N_ants < DEFAULT_NB_ANTS_PER_COLONY) {
                                    world.colonies[active_colony].add_ant();
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
                                          DETECTION_RADIUS);
                        obstacle.texture.loadFromFile("../ressources/rock.jpeg");
                        world.obstacles.push_back(obstacle);

                    }

                    if (event.mouseButton.button == sf::Mouse::Left) {

                        draw_obstacle = false;


                        // The following for-loop is there to add a "block" of food, instead of a line
                        sf::Vector2f to_pos = sf::Vector2f(event.mouseButton.x - 20, event.mouseButton.y - 20);
                        float x_offset = 1.;

                        for (int i = 0; i < 10; i++) {
                            for (int j = 0; j < 10; j++) {

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
                        world.obstacles.push_back(obstacle);

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

            float time = world.colonies[0].ants[0].get_lifetime();

            // To display a time in minutes
            int minutes = 0;
            while (time > 60.) {
                time -= 60.;
                minutes += 1;
            }

            //These objects need to be updated only when the simulation is running
            text1.setString(
                    "Time elapsed :  " + to_string(minutes) + "  min  " + to_string(time).substr(0, 3));


            updating_clock.restart();
            world.update(dt);
            float updating_delay = updating_clock.restart().asSeconds();
            if (updating_delay > 0.3)cout << "updating time" << updating_delay << "\n";

            nb_markers.setString("Number of Markers : " + to_string((int) total_markers));

            data_file
                    << to_string(minutes) + ":" + to_string(time) + ";" + to_string(dt.asSeconds()) + ";" +
                       to_string(updating_delay) + ";" + to_string(total_markers) << endl;
        }


        ant_speed.setString(
                "ANTS SPEED : " + to_string((int) world.colonies[active_colony].ant_speed));
        colony_size.setString(
                "Number of Ants : " + to_string((int) world.colonies[active_colony].get_nb_ants()));
        food_in_col.setString("Food in colony : " +
                              to_string((int) world.colonies[active_colony].food_in_colony));
        ant_generated.setString("Ants generated : " +
                                to_string((int) world.colonies[active_colony].ant_generated));

        window.clear();

        drawing_clock.restart();
        // Drawing every object
        window.draw(Background);
        total_markers = 0;


        for (auto &colony: world.colonies) {


            for (auto &chunk: colony.chunks) {
                for (auto &marker: chunk.getMarkers()) {
                    if (markerGraphics) { window.draw(marker.graphic); }
                    total_markers += 1;

                }
            }
            window.draw(colony.colony_base);
            for (auto &ant: colony.ants) {
                window.draw(ant.graphics);
            }

        }

        for (auto &food: world.foods) { window.draw(food.graphic); }
        for (auto &obstacle: world.obstacles) { window.draw(obstacle.graphics, &obstacle.texture); }

        window.draw(colony_info_quad);
        window.draw(simulation_info_quad);

        window.draw(text);
        window.draw(text1);
        window.draw(ant_speed);
        window.draw(colony_size);
        window.draw(nb_markers);
        window.draw(food_in_col);
        window.draw(ant_generated);
        window.draw(colony_active);

        float drawing_delay = drawing_clock.restart().asSeconds();
        if (drawing_delay > 0.2)cout << "drawing time" << drawing_delay << "\n";
        if (pause) window.draw(text3);

        window.display();

    }
    return 0;
}



