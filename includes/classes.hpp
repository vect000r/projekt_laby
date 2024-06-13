#ifndef CLASSES_H
#define CLASSES_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

class MovableSprite : public sf::Sprite
{
public:
    void moveObject(sf::RenderWindow& window);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void shoot(sf::RenderWindow& window, sf::Texture bullet_texture);
};

class Player : public MovableSprite
{
public:
    int hitPoints = 100;
    float bullet_position_x;
    float bullet_position_y;
    std::vector<sf::Sprite> bullets;

    Player();

    bool is_moving = false;
    bool is_alive = true;
    
    void moveObject(sf::RenderWindow& window);
    void shoot(sf::RenderWindow& window, sf::Texture bullet_texture);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f velocity = sf::Vector2f(0, 0);
    float speed = 400.0f;
    sf::Clock bullet_clock;
    sf::Time bullet_cooldown;
};

class Enemy : public MovableSprite
{
public:
    Enemy(sf::Vector2f position, sf::Vector2f size);

    void moveObject(sf::RenderWindow& window);
    void shoot(sf::RenderWindow& window, sf::Texture bullet_texture);
    void draw(sf::RenderWindow& window);
    void update(float deltaTime);

private:
    sf::Vector2f enemy_velocity;
    float enemy_speed = 400.0f;
    std::vector<sf::Sprite> enemy_bullets;
    sf::Clock bullet_clock;
    sf::Time bullet_cooldown;
};

class Asteroid : public MovableSprite
{
public:
    float asteroid_speed = 200.0f;

    Asteroid(sf::Vector2f position, sf::Vector2f size);

    void moveObject(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void update(float deltaTime);

    int hitPoints = 100;
    ~Asteroid() = default;

private:
    sf::Vector2f asteroid_velocity = sf::Vector2f(0, 0);
};

#endif // CLASSES_H
