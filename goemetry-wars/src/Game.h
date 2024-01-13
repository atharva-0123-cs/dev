#pragma once

#include "Entity.h"
#include "EntityManger.h"

#include <SFML/Graphics.hpp>

struct PlayerConfig  {
    int SR, CR, FR, FG, FB, OR,OB,OT,V;
    float S;
};

struct EnemyConfig {
    int SR, CR, OR, OG, OB, OT, VIM, VMAX, L, SI;
    float SMIN, SMAX;
};

struct BulletConfig {
    int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L;
    float S;
};

class Game 
{
    sf::RenderWindow    m_window; 
    EntityManger        m_entities;
    sf::Font            m_font;
    sf::Text            m_text;
    PlayerConfig        m_playerConfig;
    EnemyConfig         m_enemyConfig;
    BulletConfig        m_bulletConfig;
    int                 m_score = 0;
    int                 m_currentFrame = 0;
    int                 m_lastEnemySpawnTime = 0;
    bool                m_pused = false;
    bool                m_runnig = true;
    int                 m_frameCount = 0;

    std::shared_ptr<Entity> m_player;

    void init(const std::string& config); // initialize the Game
    void setPaused(bool paused);

    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity>& entity, const Vec2& mousePos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

    float randomFloat(float min, float max);

public:

    Game(const std::string& config);

    void run();

};