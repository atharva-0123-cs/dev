#include <SFML/Graphics.hpp>

class Game {
private:
  sf::RenderWindow mWindow;
  sf::CircleShape mPlayer;
  float speed = 5.0f;

public:
  Game();
  void run();

private:
  void processEvents();
  void update();
  void render();
};

Game::Game() : mWindow(sf::VideoMode(640, 480), "SFML SPACE"), mPlayer() {
  mPlayer.setRadius(40.f);
  mPlayer.setPosition(100.f, 100.f);
  mPlayer.setFillColor(sf::Color::Cyan);
}

// processEvents
void Game::processEvents() {
  sf::Event event;
  while (mWindow.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      mWindow.close();
    }

    // 
  }
}

// update
void Game::update() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    mPlayer.move(0, -speed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    mPlayer.move(0, speed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    mPlayer.move(-speed, 0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    mPlayer.move(speed, 0);
}

void Game::render() {
  mWindow.clear();
  mWindow.draw(mPlayer);
  mWindow.display();
}

// run
void Game::run() {

  while (mWindow.isOpen()) {
    processEvents();
    update();
    render();
  }
}

int main() {

  Game space;
  space.run();

  // sf::RenderWindow window(sf::VideoMode(640, 540), "SFML Space Game",
  //                         sf::Style::Default);
  // Circle
  // sf::CircleShape circle(50.0f);
  // circle.setFillColor(sf::Color::Green);
  // Rectangle
  // sf::RectangleShape rectangle(sf::Vector2f(100, 50));
  // rectangle.setPosition(30, 30);
  // rectangle.setFillColor(sf::Color::Cyan);
  // float speed = 5.0f;
  // while (window.isOpen()) {
  //   sf::Event event;
  //   while (window.pollEvent(event)) {
  //     if (event.type == sf::Event::Closed)
  //       window.close();
  //   }
  //   // Keyboard Input
  //   if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  //     circle.move(0, -speed);
  //   if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  //     circle.move(0, speed);
  //   if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  //     circle.move(-speed, 0);
  //   if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  //     circle.move(speed, 0);
  //   window.clear();
  //   window.draw(circle);
  //   window.draw(rectangle);
  //   window.display();
  // }

  return 0;
}
