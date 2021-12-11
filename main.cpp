#include <SFML/Window.hpp>
#include <iostream>
#include "simulation/World.h"
using namespace std;

#define PI 3.14159265


int main() {


    int height = 1000;
    int width = 1000;

    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    sf::Clock clock;
    sf::Font font;
    window.setTitle("Avengers AntGame - @G0bel1n");

    World world(height, width, 50, 50);

    if (!font.loadFromFile("/Users/g0bel1n/CLionProjects/ants_fight_club/ressources/Exclusive-Serif.ttf"))
    {
        // error...
    }
    sf::VertexArray quad(sf::Quads, 4);
    sf::Text text;
    text.setFont(font);
    text.setString("Hello");
    text.setPosition(width/4, (float)height-100.);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);

    sf::Text text1;
    text1.setFont(font);
    text1.setString("Hello");
    text1.setPosition(width*3./4, height-100.);
    text1.setCharacterSize(50);
    text1.setFillColor(sf::Color::White);


    sf::RectangleShape circle (sf::Vector2f(50.f,10.f));
    circle.setFillColor(sf::Color::Yellow);


    sf::CircleShape colony_base(100.);
    colony_base.setOrigin(100.,100.);
    colony_base.setPosition(world.ants[0].home);
    colony_base.setFillColor(sf::Color::White);


    circle.setPosition(sf::Vector2<float>(10.f,150.f));

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {


                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    std::cout<< "1 \n";
                }
            }
        }

        sf::Time dt = clock.restart();


        text.setString("To Food : " + to_string(world.ants[0].ToFood));
        text1.setString("Target " + to_string(world.ants[0].target));

        world.update_ants(dt);
        circle.setPosition(circle.getPosition()+sf::Vector2<float>(dt.asSeconds()*500.f,0.0f));

        window.clear(sf::Color(104,157,113));
        window.draw(colony_base);
        for(auto & marker : world.markers) {window.draw(marker.graphic);}
        for(auto & ant : world.ants){window.draw(ant.graphics);}

        window.draw(text);
        window.draw(text1);
        window.display();
    }
    return 0;
}



