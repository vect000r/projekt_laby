#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "classes.hpp"



Player::Player()
{
    setScale(sf::Vector2f(5, 5));
    setPosition(sf::Vector2f(0, 540));
}

   
    
void Player::moveObject(sf::RenderWindow& window)
{
    velocity.x = 0;
    velocity.y = 0;
    speed = 400.0f;
    is_moving = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        velocity.x = -speed;
        if (getGlobalBounds().left <= 0)
        {
            setPosition(0, getPosition().y);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocity.x = speed;
        if (getGlobalBounds().left + getGlobalBounds().width >= window.getSize().x)
        {
            setPosition(window.getSize().x - getGlobalBounds().width, getPosition().y);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        velocity.y = -speed;
        if (getGlobalBounds().top <= 0)
        {
            setPosition(getPosition().x, 0);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        velocity.y = speed;
        if (getGlobalBounds().top + getGlobalBounds().height >= window.getSize().y)
        {
            setPosition(getGlobalBounds().left, window.getSize().y - getGlobalBounds().height);
        }
    }
}

void Player::shoot(sf::RenderWindow& window, sf::Texture bullet_texture)
{
    bullet_cooldown = bullet_clock.getElapsedTime();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& bullet_cooldown.asSeconds() >= 0.5)
    {
        bullet_clock.restart();
        bullets.push_back(sf::Sprite(bullet_texture));
        bullets.back().setScale(4, 4);
        bullets.back().setOrigin(5, 5);
        bullets.back().setPosition(getPosition()+sf::Vector2f(0, 30));
        bullet_position_x = bullets.back().getPosition().x;
        bullet_position_y = bullets.back().getPosition().y;
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].move(20, 0);
        window.draw(bullets[i]);
    }
}
    
    
void Player::update(float deltaTime)
{
    move(velocity.x * deltaTime, velocity.y * deltaTime);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(*this); 
}

/////////////////////
/////Enemy class/////
/////////////////////

Enemy::Enemy(sf::Vector2f position, sf::Vector2f size)
{
    setScale(size);
    setPosition(position);
}

void Enemy::moveObject(sf::RenderWindow& window)
{
    enemy_velocity.x = -enemy_speed;
}

void Enemy::shoot(sf::RenderWindow& window, sf::Texture bullet_texture)
{
    bullet_cooldown = bullet_clock.getElapsedTime();

    if (bullet_cooldown.asSeconds() >= 0.5)
    {
        bullet_clock.restart();
        enemy_bullets.push_back(sf::Sprite(bullet_texture));
        enemy_bullets.back().setScale(4, 4);
        enemy_bullets.back().setOrigin(5, 5);
        enemy_bullets.back().setPosition(getPosition()+sf::Vector2f(100, 50));
    }

    for (int i = 0; i < enemy_bullets.size(); i++)
    {
        enemy_bullets[i].move(-20, 0);
        window.draw(enemy_bullets[i]);
    }
}
    
void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(*this); 
}

void Enemy::update(float deltaTime)
{
    move(enemy_velocity.x * deltaTime, enemy_velocity.y * deltaTime);
}

void Enemy::setSpeed(float speed)
{
    enemy_speed = speed;
}

////////////////////////
/////Asteroid class/////
////////////////////////



Asteroid::Asteroid(sf::Vector2f position, sf::Vector2f size)
{
    setScale(size);
    setPosition(position);
}

void Asteroid::moveObject(sf::RenderWindow& window)
{
    asteroid_velocity.x = -asteroid_speed;
}
    
void Asteroid::draw(sf::RenderWindow& window)
{
    window.draw(*this); 
}
    
void Asteroid::update(float deltaTime)
{
    move(asteroid_velocity.x * deltaTime, asteroid_velocity.y * deltaTime);
}

void Asteroid::setSpeed(float speed)
{
    asteroid_speed = speed;
}


//int hitPoints = 100;

