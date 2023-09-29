#include <SFML/Graphics.hpp>


int main() {
  sf::RenderWindow window(sf::VideoMode(640, 540),
  "SFML works!", sf::Style::Default);

  //Circle
  sf::CircleShape circle(50.0f);
  circle.setFillColor(sf::Color::Green);

  //Rectangle
  sf::RectangleShape rectangle(sf::Vector2f(100, 50));
  rectangle.setPosition(30,30);
  rectangle.setFillColor(sf::Color::Cyan);


  float speed = 5.0f;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
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
    window.draw(rectangle);
    window.display();
  }

  return 0;
}
