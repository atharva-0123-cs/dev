#include <SFML/Graphics.hpp>
#include<iostream>
#include <cassert>
#include "ResourceHolder.hpp"


namespace Textures
{
 enum ID { Landscape, Airplane, Missile };
}
namespace Fonts
{
 enum ID { Arial, Times,DoctorGlitch};
}
namespace SoundBuffers
{
 enum ID { Distortion3};
}




class Game {
private:
  sf::RenderWindow mWindow;
  // sf::CircleShape mPlayer;
  // sf::Texture mTexture;
  

  sf::Sprite mPlayer;
  ResourceHolder<sf::Texture , Textures::ID > textures;

  sf::Text mText;
  ResourceHolder<sf::Font , Fonts::ID > fonts;
  

private:
    bool mIsMovingUp,
         mIsMovingDown,
         mIsMovingLeft,
         mIsMovingRight;

    float speed = 50.0f;

public:
  // static const int a = 10;
  Game();
  void run();

private:
  void processEvents();
  void update(sf::Time);
  void render();

private:
  void handelPlayerInput(sf::Keyboard::Key, bool);

};

Game::Game()  : 
    mWindow(sf::VideoMode(640, 480), "SFML SPACE")
    // ,mTexture() 
    ,mPlayer()
    ,mText()
{

  textures.load(Textures::Airplane,"Media/Textures/spaceship.png");
  fonts.load(Fonts::DoctorGlitch,"Media/Fonts/DoctorGlitch.otf");
  // textures.load(Textures::Airplane,"Media/Textures/spaceship.png"); --> assert test

  // if (!mTexture.loadFromFile("Media/Textures/spaceship.png"))
  // {
  // // Handle loading error
  // std::cout<<"Image is not present \n";
  // }

  mPlayer.setTexture(textures.get(Textures::Airplane));
  mPlayer.setPosition(400.f, 400.f);

  mText.setFont(fonts.get(Fonts::DoctorGlitch));
  mText.setString("Space Game");
  mText.setPosition(100.f,100.f);

  

  // mPlayer.setRadius(40.f);
  // mPlayer.setPosition(100.f, 100.f);
  // mPlayer.setFillColor(sf::Color::Cyan);
}

// processEvents
void Game::processEvents() 
{
  sf::Event event;
  while (mWindow.pollEvent(event)) {

    switch(event.type){

      case sf::Event::KeyPressed :
        handelPlayerInput(event.key.code , true);
        break;

      case sf::Event::KeyReleased :
        handelPlayerInput(event.key.code , false);
        break;

      case sf::Event::Closed :
        mWindow.close();
        break;
    }

    // if (event.type == sf::Event::Closed) {
    //   mWindow.close();
    // }
    // 
  }
}

void Game::handelPlayerInput(sf::Keyboard::Key key, bool isPressed){

  if(key == sf::Keyboard::W){
    mIsMovingUp = isPressed;
  }
  else if(key == sf::Keyboard::S){
    mIsMovingDown = isPressed;
  }
  else if(key == sf::Keyboard::A){
    mIsMovingLeft = isPressed;
  }
  else if(key == sf::Keyboard::D){
    mIsMovingRight = isPressed;
  }

}


// update
void Game::update(sf::Time deltaTime) {
  sf::Vector2f movement(0.f, 0.f);

  if (mIsMovingUp)
    movement.y -= speed;

  if (mIsMovingDown)
    movement.y += speed;

  if (mIsMovingLeft)
    movement.x -= speed;

  if (mIsMovingRight)
    movement.x += speed;

  mPlayer.move(movement * deltaTime.asSeconds());

  /*
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    mPlayer.move(0, -speed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    mPlayer.move(0, speed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    mPlayer.move(-speed, 0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    mPlayer.move(speed, 0);
    */
}

void Game::render() 
{
  mWindow.clear();

  mWindow.draw(mText);
  mWindow.draw(mPlayer);
  // mWindow.draw(mImage);

  mWindow.display();
}

// run
void Game::run() 
{

  sf::Clock clock;

  while (mWindow.isOpen()) {

    sf::Time deltaTime = clock.restart();
    //  std::cout<<"\n deltaTime :"<<deltaTime.asSeconds()<<"\n";
    processEvents();
    update(deltaTime);
    render();
  }
}

int main() 
{

  Game space;
  // std::cout<<Game::a<<"\n";
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
