#include <SFML/Window.hpp>
#include <iostream>
#include "simulation/World.h"
#include "simulation/Renderer.h"
using namespace std;

#define PI 3.14159265



int main() {


    int height = 1200;
    int width = 1200;

    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    sf::Clock clock;
    sf::Font font;



    World world(height, width, 10, 1);
    Renderer renderer(world);


    if (!font.loadFromFile("/Users/g0bel1n/CLionProjects/ants_fight_club/ressources/Exclusive-Serif.ttf"))
    {
        // error...
    }


// create a quad
    sf::VertexArray quad(sf::Quads, 4);
    sf::Text text;
    text.setFont(font);
    text.setString("Hello");
    text.setPosition(10.f,10.f);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::White);
    sf::RectangleShape circle (sf::Vector2f(50.f,10.f));
    circle.setFillColor(sf::Color::Yellow);
    //sf::CircleShape marker(50.f);


    /*vector<marker> all_markers;
    vector<sf::CircleShape> markers_rep;

    for (int i=0 ; i<10;i++) {

        sf::Vector2<float> position ((float)(std::rand()%1000),(float)(std::rand()%1000));

        std::cout<< position.x <<"\n";
        all_markers.push_back(marker(position,1));
        markers_rep.push_back(sf::CircleShape(30.f));
        markers_rep[i].setPosition(position);
        markers_rep[i].setFillColor(sf::Color::Red);


    }*/

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
        text.setString(to_string(world.ants[0].get_lifetime()));

        /*for (int i =0;i<=4;i++){

            quad[i].position += (velocity_vect * dt.asSeconds());
        }*/
        //sf::Vector2f velocity_vect(cos(angle*PI/180)*speed, sin(angle*PI/180)*speed);
/*        all_markers = ant.update(dt, all_markers);
        circle.setPosition(ant.get_position());
        circle.setRotation(ant.get_angle()*180/PI);*/


/*        int count_marker = 10;
        for(int i=0 ; i<10;i++){

            if(all_markers[i].marker_type==0){

                markers_rep[i].setFillColor(sf::Color::Yellow);
                count_marker-=1;
            }

            window.draw(markers_rep[i]);
        }
        if (count_marker==0){
            window.close();
        }
        window.draw(circle);*/


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

        window.display();



    }
    return 0;
}



