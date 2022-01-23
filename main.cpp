#include <SFML/Window.hpp>
#include <iostream>
#include "simulation/World.h"


using namespace std;

#define PI 3.14159265


int main() {

    int height = 800;
    int width = 1200;
    bool pause = true;
    int total_food = 0;


    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    sf::Clock clock;
    sf::Font font;
    window.setTitle("Avengers AntGame - @G0bel1n");


    //Generating the world
    World world(width, height, 20, total_food);


    if (!font.loadFromFile( "../ressources/pricedown.otf")) {
        cout<<"Could not load the font...";
    }

    //Loading the grass background
    sf::Texture SoilTex;
    SoilTex.loadFromFile("../ressources/soil.jpeg");

    sf::Sprite Background(SoilTex);
    Background.setPosition(0,0);
    Background.setScale(width/3448.,height/3448.);


    //Text SFML-Objects that will display :

    // the amount of food available
    sf::Text text;
    text.setFont(font);
    text.setString("Hello");
    text.setPosition(50, (float) height - 100.);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);

    // The time elapsed
    sf::Text text1;
    text1.setFont(font);
    text1.setString("Hello");
    text1.setPosition(width * 3. / 6, height - 100.);
    text1.setCharacterSize(40);
    text1.setFillColor(sf::Color::White);

    // The amount of food in the colony
    sf::Text text2;
    text2.setFont(font);
    text2.setString("Hello");
    text2.setCharacterSize(40);
    text2.setPosition(world.ants[0].home + sf::Vector2f(50., 0.));
    text2.setFillColor(sf::Color::White);


    //Basic commands
    sf::Text text3;
    text3.setFont(font);
    text3.setString("SPACE to start/Pause \nLeft Click to add food \nRight click to add obstacles");
    text3.setCharacterSize(40);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(10, 10);



    // Texture of the colony Hole
    sf::Texture colony_hole;
    colony_hole.loadFromFile("../ressources/Hole.PNG");

    //Colony Graphic object
    sf::Sprite colony_base;
    colony_base.setPosition(world.ants[0].home);
    colony_base.setOrigin(536. / 2., 204.);
    colony_base.setTexture(colony_hole);
    colony_base.setScale(0.2, 0.2);
    cout << colony_base.getLocalBounds().width;

    // The vector Obstacle (Reminder : send it to World.h)
    std::vector<Obstacle> obstacles;


    //Main Loop
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space && !pause) {

                    cout << "PAUSING";

                    pause = true;

                } else if (event.key.code == sf::Keyboard::Space && pause) {

                    pause = false;

                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {

                if (event.mouseButton.button == sf::Mouse::Right) {

                    Obstacle obstacle(sf::Vector2f(event.mouseButton.x - 50., event.mouseButton.y - 50.), 100.);
                    obstacle.texture.loadFromFile("../ressources/rock.jpeg");
                    obstacles.push_back(obstacle);
                }

                if (event.mouseButton.button == sf::Mouse::Left) {



                    // The following for-loop is there to add a "block" of food, instead of a line
                    sf::Vector2f to_pos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    float x_offset = 10.;

                    for (int i = 0; i < 10; i++) {
                        if (i % 5 == 0) {
                            x_offset = -x_offset;
                            to_pos += sf::Vector2f(0., 10.f);
                        }

                        to_pos += sf::Vector2f(x_offset, 0.);

                        world.AddMarker(to_pos, 1);
                    }
                    total_food += 10;
                }
            }
        }

        sf::Time dt = clock.restart();
        if (!pause) {

            text.setString("Food available: " + to_string(world.get_food_available()));

            float time = world.ants[0].get_lifetime();

            //To display a time in minutes
            int minutes = 0;
            while (time > 60.) {
                time -= 60.;
                minutes += 1;
            }

            //These objects need to be updated only when the simulation is running
            text1.setString("Time elapsed :  " + to_string(minutes) + "  min  " + to_string(time).substr(0, 3));
            text2.setString(to_string(total_food - world.get_food_available()));
            world.update_ants(dt, obstacles);
        }



        window.clear();

        window.draw(Background);
        window.draw(colony_base);
        for (auto &marker: world.markers) { window.draw(marker.graphic); }
        for (auto &ant: world.ants) { window.draw(ant.graphics); }
        for (auto &food: world.foods) { window.draw(food.graphic); }
        for (auto &obstacle: obstacles) { window.draw(obstacle.graphics, &obstacle.texture); }
        // cout << "Nb of markers  : " << world.markers.size() << "\n";
        window.draw(text);
        window.draw(text1);
        window.draw(text2);

        if (pause) window.draw(text3);

        window.display();

    }
    return 0;
}



