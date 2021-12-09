#include <SFML/Window.hpp>
#include <iostream>
#include "simulation/World.h"
#include "simulation/Renderer.h"
using namespace std;

#define PI 3.14159265


int main() {

    int height = 1000;
    int width = 1000;

    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    sf::Clock clock;
    sf::Font font;
    window.setTitle("Avengers AntGame - @G0bel1n");

    World world(height, width, 20, 20);
    Renderer renderer(world);


    if (!font.loadFromFile("/Users/g0bel1n/CLionProjects/ants_fight_club/ressources/Exclusive-Serif.ttf"))
    {
        // error...
    }
    sf::VertexArray quad(sf::Quads, 4);
    sf::Text text;
    text.setFont(font);
    text.setString("Hello");
    text.setPosition(10.f,1100.f);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);

    sf::Text text1;
    text1.setFont(font);
    text1.setString("Hello");
    text1.setPosition(300.f,1100.f);
    text1.setCharacterSize(50);
    text1.setFillColor(sf::Color::White);


    sf::RectangleShape circle (sf::Vector2f(50.f,10.f));
    circle.setFillColor(sf::Color::Yellow);

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
                }
            }
        }

        sf::Time dt = clock.restart();

        //sf::Vector2<int> mouse = sf::Mouse::getPosition(window);

        //sf::Vector2f delta_vect = (window.mapPixelToCoords(mouse) - circle.getPosition());

       // float angle = atan(delta_vect.y/delta_vect.x)*180/PI;
        //if (delta_vect.x<0){
           // angle-=180;
        //}
        text.setString("Ants : " + to_string(world.get_nb_ants()));
        text1.setString("Foods : " + to_string(world.get_nb_food()));

        world.update_ants(dt);
        renderer.update(world);
        circle.setPosition(circle.getPosition()+sf::Vector2<float>(dt.asSeconds()*500.f,0.0f));


        window.clear(sf::Color(104,157,113));

        for(int i=0; i<world.get_nb_food();i++){
            window.draw(renderer.markers_graphic[i]);
        }

        for(int i=0; i<world.get_nb_ants();i++){
            window.draw(renderer.ants_graphics[i]);
        }

        window.draw(text);
        window.draw(text1);

        window.display();

    }
    return 0;
}



