#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 540), "SFML works!");                                           
    sf::CircleShape circle(100.0f);
    circle.setFillColor(sf::Color::Green);

    float speed = 5.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

	// Keyboard Input
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            circle.move(0, -speed);

	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            circle.move(0, speed);

         if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            circle.move(-speed, 0);

         if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            circle.move(speed, 0);

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}








































