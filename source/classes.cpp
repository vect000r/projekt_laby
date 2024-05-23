#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Player : public sf::Sprite
{
public:
    Player(sf::Vector2f position, sf::Vector2f size)
    {
        setScale(size);
        setPosition(position);
    }

    void movePlayer(sf::RenderWindow& window)
    {
        velocity.x = 0;
        velocity.y = 0;
        


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

    void update(float deltaTime)
    {
        move(velocity.x * deltaTime, velocity.y * deltaTime);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(*this); 
    }

private:
    sf::Vector2f velocity;
    float speed = 400.0f;
};

class Enemy : public sf::Sprite
{
public:
    Enemy(sf::Vector2f position, sf::Vector2f size)
    {
       setScale(size);
       setPosition(position);
    }

    void moveEnemy(sf::RenderWindow& window)
    {
        velocity.x = rand() % 100 - 5;
        velocity.y = rand() % 100 - 5;
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(*this); 
    }

    void update(float deltaTime)
    {
        move(velocity.x * deltaTime, velocity.y * deltaTime);
    }

private:
    sf::Vector2f velocity;
    float speed = 400.0f;

};