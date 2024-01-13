#include "Game.h"
#include "Components.h"
#include "Entity.h"
#include "Vec2.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include<iostream>
#include <math.h>
#include <memory>



Game::Game(const std::string& config)
{
    init(config);
}

void Game::init(const std::string& path)
{
    // TODO : read in the file here
    // use premade  PlayerConfig, EnemyConfig, BulletConfig

    // setup default wondow parameters
    m_window.create(sf::VideoMode(720,480), "Assignment2");
    m_window.setFramerateLimit(60);

    if(!m_font.loadFromFile("../fonts/Sansation.ttf"))
    {
        std::cout<<"Font Not Load"<<std::endl;
    }

    m_text.setFont(m_font);
    m_text.setPosition(24.f,24.f);
    m_text.setCharacterSize(16.f);

    spawnPlayer();
    
}

void Game::run()
{
    // TODO : add pause functionality in here
    // some systems should function while paused (rendering)
    // some systems shouldn't (movement / input)

     // Create a clock
    sf::Clock clock;

    // Variable to store elapsed time
    sf::Time elapsedTime;

    while (m_runnig)
    {
        m_entities.update();
        
        if (!m_pused)
        {
            sEnemySpawner();
            sMovement();
            sCollision();
            sLifespan();
            sUserInput();
        }

        sRender();

        // Update frame count
        m_frameCount++;
        // Get elapsed time
        elapsedTime = clock.getElapsedTime();

        // Update FPS every second
        if (elapsedTime.asSeconds() >= 1.0) 
        {
            // Calculate FPS
            float fps = static_cast<float>(m_frameCount) / elapsedTime.asSeconds();

            // Display FPS in the console
            // std::cout << "FPS: " << fps << std::endl;

          // Update the FPS text
            m_text.setString("FPS: " + std::to_string(static_cast<int>(fps)) + "." + std::to_string(static_cast<int>((fps - static_cast<int>(fps)) * 100)));

            // Reset the clock and frame count
            clock.restart();
            m_frameCount = 0;
        }

        // increment the current frame
        // may need to be moved when pause implemented
        m_currentFrame++;
    }  
}

void Game::setPaused(bool paused)
{
    m_pused = true;
}

// respawn the player in the middle of the screem
void Game::spawnPlayer()
{
 // TODO : Finsh adding all properties of the player with the correct values form the config

// We create every by calling EntityManger.addEntity(tag)
// This returns a std::shared_pointer<Entity>, so we use 'auto' to save typing
auto entity = m_entities.addEntity("player");

// Give this entity a Transform so it spawns at (200,200) with velocity (1,1) and angle 0
    
    float mx = m_window.getSize().x / 2.0f;
    float my = m_window.getSize().y / 2.0f;

    entity->cTransform = std::make_shared<CTrasform>(
        Vec2(mx,my),
        Vec2(1.0f,1.0f),
        0.0f
    );

// The Entity Shape will have radius 32, 8 sides, dark greay fill, red outline of thickness 4
    entity->cShape = std::make_shared<CShape>(
        32.0f, 8,
        sf::Color(10,10,10),
        sf::Color(255,0,0),
        4.0f
    );

// Add an input component to the player so that we use inputs
    entity->cInput = std::make_shared<CInput>();

// Scince we want this Entity to be our player, set our Game's player variable to be this Entity
// This goes slightyl against the EntityManger paradigm, but we the player so much sp it's worth it
    m_player = entity;

}

// Define a function to generate random float within a range
 float Game::randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
 }

// spawn the enemy at the random location
void Game::spawnEnemy()
{
    // TODO : make sure the enemy is properly with the m_ememeyConfig variables
    auto entity = m_entities.addEntity("enemy");



    float px = randomFloat(0.0f, static_cast<float>(m_window.getSize().x));
    float py = randomFloat(0.0f, static_cast<float>(m_window.getSize().y));

    float vx = randomFloat(1.0f, 1.0f);
    float vy = randomFloat(1.0f, 1.0f);

    // std::cout<<ex<<" "<<ey<<"\n";


    entity->cTransform = std::make_shared<CTrasform>(
        Vec2(px,py),
        Vec2(vx, vy),
        0.0f
    );

    // The Entity Shape will have radius 32, 8 sides, dark greay fill, red outline of thickness 4
    entity->cShape = std::make_shared<CShape>(
        32.0f, 3.f,
        sf::Color(10,10,10),
        sf::Color(255,0,0),
        4.0f
    );

    //record when the most recent enemy was spawned
    m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
    // TODO : spawn small ememies at location of the input entity e

    // when we create the smaller enemy, we have to read the values of orignal enemy
    //  - spawn a number of small enemies equal to the vertices of orignal enemy e
    //  - set each small enemy to the same color as the orignal, half the size
    //  - small enemies are worth double points of orignal enemy

    int pointCount = e->cShape->circle.getPointCount();
    Vec2 positon = e->cTransform->pos;
    Vec2 velocity = e->cTransform->velocity;
    sf::Color color = e->cShape->circle.getFillColor();
    sf::Color outlineColor = e->cShape->circle.getOutlineColor();
    float outlineThickness = e->cShape->circle.getOutlineThickness();
    float radius = e->cShape->circle.getRadius();



    for(int i=0; i<pointCount; i++)
    {
            auto smallEnemies = m_entities.addEntity("smallEnemies");

            smallEnemies->cTransform = std::make_shared<CTrasform>(
            positon,
            Vec2(velocity.x * sin(((360.f/pointCount) + i * (360.f/pointCount)) * M_PI / 180.0f),
            velocity.y * cos(((360.f/pointCount) + i * (360.f/pointCount)) * M_PI / 180.0f)),
            0.0f
        );

        // The Entity Shape will have radius 32, 8 sides, dark greay fill, red outline of thickness 4
            smallEnemies->cShape = std::make_shared<CShape>(
            radius - 18.f, pointCount,
            color,
            outlineColor,
            outlineThickness
        );
    }
}

void Game::spawnBullet(std::shared_ptr<Entity>& e, const Vec2& target)
{
    // TODO : implement the spawing of a bullet which travels towards target
    //      - bullet spped is given as a scalar spped
    //      - you must set the velocity by using foumula in notes

    auto bullet = m_entities.addEntity("bullet");

    float dx = target.x - e->cTransform->pos.x;
    float dy = target.y - e->cTransform->pos.y;

    float angle = std::atan2(dy,dx);

    Vec2 velocity((5.f * std::cos(angle)),(5.f * std::sin(angle)));

    // std::cout<<angle<<"\n";

    bullet->cTransform = std::make_shared<CTrasform>(e->cTransform->pos, velocity, 0);
    bullet->cShape = std::make_shared<CShape>(4, 32, sf::Color(255,255,255), sf::Color(255,255,255), 2);

    bullet->cLifespan = std::make_shared<CLifespan>(80);
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
    // TODO : implement your own special weapon
}

void Game::sMovement()
{
    // TODO : implement all entity movement in this function
    //      you should read the m_player->cInput componenet to determine if the player is moving

    m_player->cTransform->velocity = {0.f,0.f};

    //implement  the player movement
    
        if(m_player->cShape->circle.getPosition().y >= m_player->cShape->circle.getRadius())
        {    
            if(m_player->cInput->up)
            {
                m_player->cTransform->velocity.y = -5;
            }
        }
        if(m_player->cShape->circle.getPosition().y <= m_window.getSize().y - m_player->cShape->circle.getRadius())
        {
            if(m_player->cInput->down)
            {
                m_player->cTransform->velocity.y = 5;
            }
        }

        if(m_player->cShape->circle.getPosition().x >= m_player->cShape->circle.getRadius() )
        {   if(m_player->cInput->left)
            {
                m_player->cTransform->velocity.x = -5;
            }
        }

        if(m_player->cShape->circle.getPosition().x <= m_window.getSize().x - m_player->cShape->circle.getRadius() )
        {

            if(m_player->cInput->right)
            {
                m_player->cTransform->velocity.x = 5;
            }
        }
        // sample movement speed update 
        m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
        m_player->cTransform->pos.y += m_player->cTransform->velocity.y;

        for(auto b : m_entities.getEntities("bullet"))
        {
            // b->cShape->circle.move(b->cTransform->velocity.x,b->cTransform->velocity.y);
            b->cTransform->pos.x += b->cTransform->velocity.x;
            b->cTransform->pos.y += b->cTransform->velocity.y;
        }

        for(auto e : m_entities.getEntities("enemy"))
        {
            if(e->cShape->circle.getPosition().x  <= e->cShape->circle.getRadius() ||
            e->cShape->circle.getPosition().x  >= m_window.getSize().x - e->cShape->circle.getRadius())
            {
                e->cTransform->velocity.x *= -1.0f;
            }

            if(e->cShape->circle.getPosition().y  <= e->cShape->circle.getRadius() ||
            e->cShape->circle.getPosition().y  >= m_window.getSize().y - e->cShape->circle.getRadius())
            {
                e->cTransform->velocity.y *= -1.0f;
            }

            // e->cShape->circle.move(e->cTransform->velocity.x , e->cTransform->velocity.y);
             e->cTransform->pos.x += e->cTransform->velocity.x;
             e->cTransform->pos.y += e->cTransform->velocity.y;       
        }

        for(auto smallEnemie : m_entities.getEntities("smallEnemies") )
        {
            smallEnemie->cTransform->pos.x += smallEnemie->cTransform->velocity.x;
            smallEnemie->cTransform->pos.y += smallEnemie->cTransform->velocity.y;  
        }

 }

 void Game::sLifespan()
 {
    // TODO : implement all the life span functionality
    //      for all entities
    //          if entity has no life span component skip it
    //          if entity has > 0 remaining lifespan , substract 1
    //          if it has lifespan and is alive
    //              scale its alpha channel properly
    //          if it has lifespan and its time is up
    //              destroy the entity   

    for(auto& e : m_entities.getEntities())
    {
        if(!e->cLifespan)
        {
            continue;
        }

        if(e->cLifespan->remaining > 0)
        {   
            e->cShape->circle.setFillColor(sf::Color(255,255,255, e->cLifespan->remaining));
            e->cLifespan->remaining -= 1;
        }

        if(e->cLifespan->remaining <= 0)
        {
            e->destroy();
        }

    }
    
 }



 void Game::sCollision()
 {
    // TODO : implement all proper collision between entities
    //         be sure to use collision radius and not shapes radius

    for(auto e : m_entities.getEntities("enemy"))
    {
        for(auto b : m_entities.getEntities("bullet"))
        {
            float dx = e->cTransform->pos.x - b->cTransform->pos.x;
            float dy = e->cTransform->pos.y - b->cTransform->pos.y;

            float distance = pow(dx,2) + pow(dy, 2);

            float re = e->cShape->circle.getRadius();
            float rb = b->cShape->circle.getRadius();

            float radiusSumSqure = pow((re + rb), 2);

            if(distance < radiusSumSqure)
            {
                spawnSmallEnemies(e);
                e->destroy();
                b->destroy();
            }
        }


            float dx = e->cTransform->pos.x - m_player->cTransform->pos.x;
            float dy = e->cTransform->pos.y - m_player->cTransform->pos.y;

            float distance = pow(dx,2) + pow(dy, 2);

            float re = e->cShape->circle.getRadius();
            float rp = m_player->cShape->circle.getRadius();

            float radiusSumSqure = pow((re + rp), 2);

            if(distance < radiusSumSqure)
            {
                float mx = m_window.getSize().x / 2.0f;
                float my = m_window.getSize().y / 2.0f;

                m_player->cTransform->pos.x = mx;
                m_player->cTransform->pos.y = my;
            }
    }

 }

 void Game::sEnemySpawner()
 {
    // TODO : code which implement enemy spawing should go here
    //      use (m_currentFrame - m_lastEnemySpawnTime) to determine 
    //      how long it has been since the last enemy spwan

    if((m_currentFrame - m_lastEnemySpawnTime) >= 100)
    {
        spawnEnemy();

        m_currentFrame = 0; 
        m_lastEnemySpawnTime = 0;  
    }
  
 }

void Game::sRender()
{
    // TODO : change the code below to draw all the entities
    // a sample drawing of the layer Entity
    m_window.clear();

    
    //set the positon of the player bsed on the entity's transform->angle
    m_player->cShape->circle.setPosition(m_player->cTransform->pos.x,m_player->cTransform->pos.y);

    // set the rotation of the shape based on the entity's transform->angle
    m_player->cTransform->angle += 1.0f;
    m_player->cShape->circle.setRotation(m_player->cTransform->angle);

    auto enemies = m_entities.getEntities("enemy");
    auto bullets = m_entities.getEntities("bullet");

    for(auto& e : enemies)
    {
         e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
         e->cTransform->angle += 1.0f;
         e->cShape->circle.setRotation(e->cTransform->angle);
    }

    for(auto& e : enemies)
    {
        m_window.draw(e->cShape->circle);

    }

    for(auto& b : bullets)
    {
         b->cShape->circle.setPosition(b->cTransform->pos.x, b->cTransform->pos.y);
    }
    
    for(auto& b : bullets)
    {
        m_window.draw(b->cShape->circle);

    }

    m_window.draw(m_player->cShape->circle);
    m_window.draw(m_text);

    for(auto& smallEnemie : m_entities.getEntities("smallEnemies"))
    {
        smallEnemie->cShape->circle.setPosition(smallEnemie->cTransform->pos.x,
        smallEnemie->cTransform->pos.y);

        smallEnemie->cTransform->angle += 1.0f;
        smallEnemie->cShape->circle.setRotation(smallEnemie->cTransform->angle);

        m_window.draw(smallEnemie->cShape->circle);
    }

    m_window.display();

}

void Game::sUserInput()
{
    // TODO : handle user input here
    //      note that you should only be setting the player's input component variables here
    //      you should implement the player's movement logic here
    //      the movement system will read the variables you set in this function

    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // this event triggers when the window is closed
        if (event.type == sf::Event::Closed)
        {
            m_runnig = false;
        }

        // this event triggers when a key is pressed
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::W :
                    // std::cout<<"W is pressed"<<"\n";
                    m_player->cInput->up = true;
                    break;

                case sf::Keyboard::S :
                    // std::cout<<"W is pressed"<<"\n";
                    m_player->cInput->down = true;
                    break;

                case sf::Keyboard::A :
                    // std::cout<<"W is pressed"<<"\n";
                    m_player->cInput->left = true;
                    break;

                case sf::Keyboard::D :
                    // std::cout<<"W is pressed"<<"\n";
                    m_player->cInput->right = true;
                    break;

                default: break;
            }
        }

        // this event triggers when  a key is relased
        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::W :
                    // std::cout<<"W is relased"<<"\n";
                    m_player->cInput->up = false;
                    break;

                case sf::Keyboard::S :
                    // std::cout<<"W is relased"<<"\n";
                    m_player->cInput->down = false;
                    break;

                case sf::Keyboard::A :
                    // std::cout<<"W is relased"<<"\n";
                    m_player->cInput->left = false;
                    break;

                case sf::Keyboard::D :
                    // std::cout<<"W is relased"<<"\n";
                    m_player->cInput->right = false;
                    break;

                default: break;
            }
        }

        if(event.type == sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout<<"Letf mouse button clicked \n";
                sf::Vector2i localPosition = sf::Mouse::getPosition(m_window);
                spawnBullet(m_player, Vec2(localPosition.x,localPosition.y));
            }

            if(event.mouseButton.button == sf::Mouse::Right)
            {
                std::cout<<"Right mouse button clicked \n";
            }
        }
    }    
}
