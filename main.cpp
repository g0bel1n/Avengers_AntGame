#include <SFML/Window.hpp>
#include <iostream>
#include "simulation/World.h"
#include "simulation/obstacles/Obstacle.h"


using namespace std;

#define PI 3.14159265



int main() {



    int height = 1000;
    int width = 1000;



    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    sf::Clock clock;
    sf::Font font;
    window.setTitle("Avengers AntGame - @G0bel1n");
    int total_food = 100;
    World world(height, width, 15, total_food);



    if (!font.loadFromFile("/Users/g0bel1n/CLionProjects/ants_fight_club/ressources/Exclusive-Serif.ttf"))
    {
        // error...
    }



    sf::VertexArray quad(sf::Quads, 4);
    sf::Text text;

    bool pause = true;
    text.setFont(font);
    text.setString("Hello");
    text.setPosition(50, (float)height-100.);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);

    sf::Text text1;
    text1.setFont(font);
    text1.setString("Hello");
    text1.setPosition(width*3./6, height-100.);
    text1.setCharacterSize(50);
    text1.setFillColor(sf::Color::White);

    sf::Text text2;
    text2.setFont(font);
    text2.setString("Hello");
    text2.setCharacterSize(50);
    text2.setFillColor(sf::Color::White);

    sf::Text text3;
    text3.setFont(font);
    text3.setString("SPACE to start/Pause \nLeft Clic to add food \nRight clic to add obstacles" );
    text3.setCharacterSize(100);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(10 ,100);


    sf::RectangleShape circle (sf::Vector2f(50.f,10.f));
    circle.setFillColor(sf::Color::Yellow);


    sf::Texture colony_hole;
    colony_hole.loadFromFile("../ressources/Hole.PNG");

    sf::Sprite colony_base ;
    colony_base.setPosition(world.ants[0].home);
    colony_base.setOrigin(536./2.,204.);
    colony_base.setTexture(colony_hole);
    colony_base.setScale(0.2,0.2);
    cout<<colony_base.getLocalBounds().width;

    std::vector<Obstacle> obstacles;
    /*for (int i=0; i<2;i++)
    {
    Obstacle obstacle(sf::Vector2f(300.+i*100.,300. ), 100.);
    obstacle.texture.loadFromFile("../ressources/rock.jpeg");
    obstacles.push_back(obstacle);}
    for (int i=4; i<10;i++)
    {
        Obstacle obstacle(sf::Vector2f(300., i*100.), 100.);
        obstacle.texture.loadFromFile("../ressources/rock.jpeg");
        obstacles.push_back(obstacle);}*/




    circle.setPosition(sf::Vector2<float>(10.f,150.f));

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space && !pause) {

                    cout<<"PAUSSING";

                    pause = true;

                }

                else if (event.key.code == sf::Keyboard::Space && pause) {

                    pause = false;

                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {

                if (event.mouseButton.button == sf::Mouse::Right) {


                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    std::cout << "1 \n";

                    Obstacle obstacle(sf::Vector2f(event.mouseButton.x - 50., event.mouseButton.y - 50.), 100.);
                    obstacle.texture.loadFromFile("../ressources/rock.jpeg");
                    obstacles.push_back(obstacle);
                }

                if (event.mouseButton.button == sf::Mouse::Left) {

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


            text2.setPosition(world.ants[0].home + sf::Vector2f(50., 0.));


            text.setString("Food available: " + to_string(world.get_food_available()));

            float time = world.ants[0].get_lifetime();
            int minutes = 0;
            while (time > 60.) {
                time -= 60.;
                minutes += 1;
            }
            text1.setString("Time elapsed :  " + to_string(minutes) + "  min  " + to_string(time).substr(0, 3));

            text2.setString("Food accumulated to colonie : " + to_string(total_food - world.get_food_available()));
            world.update_ants(dt, obstacles);}



            window.clear(sf::Color(104, 157, 113));
            window.draw(colony_base);
            for (auto &marker: world.markers) { window.draw(marker.graphic); }
            for (auto &ant: world.ants) { window.draw(ant.graphics); }
            for (auto &food: world.foods) { window.draw(food.graphic); }
            for (auto &obstacle: obstacles) { window.draw(obstacle.graphics, &obstacle.texture); }
            // cout << "Nb of markers  : " << world.markers.size() << "\n";
            window.draw(text);
            window.draw(text1);

            if(pause)window.draw(text3);
            window.display();

    }
    return 0;
}



