#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

class MovableSprite : public sf::Sprite
{
public:
    void moveObject(sf::RenderWindow& window){};
    void update(float deltaTime){};
    void draw(sf::RenderWindow& window){};
    void shoot(sf::RenderWindow& window, sf::Texture bullet_texture){};
};

class Player : public MovableSprite
{
public:
    Player(sf::Vector2f position, sf::Vector2f size)
    {
        setScale(size);
        setPosition(position);
    }

    void moveObject(sf::RenderWindow& window)
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

    void shoot(sf::RenderWindow& window, sf::Texture bullet_texture)
    {
        bullet_cooldown = bullet_clock.getElapsedTime();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& bullet_cooldown.asSeconds() >= 0.5)
        {
            bullet_clock.restart();
            bullets.push_back(sf::Sprite(bullet_texture));
            bullets.back().setScale(4, 4);
            bullets.back().setOrigin(5, 5);
            bullets.back().setPosition(getPosition()+sf::Vector2f(0, 30));
        }

        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].move(20, 0);
            window.draw(bullets[i]);
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
    std::vector<sf::Sprite> bullets;
    sf::Clock bullet_clock;
    sf::Time bullet_cooldown;

};

/////////////////////
/////Enemy class/////
/////////////////////

class Enemy : public MovableSprite
{
public:
    Enemy(sf::Vector2f position, sf::Vector2f size)
    {
       setScale(size);
       setPosition(position);
    }

    void moveObject(sf::RenderWindow& window)
    {
        velocity.x = 0;
        velocity.y = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            velocity.x = -speed;
            if (getGlobalBounds().left <= 0)
            {
                setPosition(0, getPosition().y);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            velocity.x = speed;
            if (getGlobalBounds().left + getGlobalBounds().width >= window.getSize().x)
            {
                setPosition(window.getSize().x - getGlobalBounds().width, getPosition().y);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            velocity.y = -speed;
            if (getGlobalBounds().top <= 0)
            {
                setPosition(getPosition().x, 0);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            velocity.y = speed;
            if (getGlobalBounds().top + getGlobalBounds().height >= window.getSize().y)
            {
                setPosition(getGlobalBounds().left, window.getSize().y - getGlobalBounds().height);
            }
        }
    }

    void shoot(sf::RenderWindow& window, sf::Texture bullet_texture)
    {
        bullet_cooldown = bullet_clock.getElapsedTime();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& bullet_cooldown.asSeconds() >= 0.5)
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
    std::vector<sf::Sprite> enemy_bullets;
    sf::Clock bullet_clock;
    sf::Time bullet_cooldown;
};
////////////////////////
/////Asteroid class/////
////////////////////////

class Asteroid : public MovableSprite
{
public:
    Asteroid(sf::Vector2f position, sf::Vector2f size)
    {
        setScale(size);
        setPosition(position);
    }

    void moveObject(sf::RenderWindow& window)
    {
        velocity.x = -speed;
    }
    
    void draw(sf::RenderWindow& window)
    {
        window.draw(*this); 
    }

    void update(float deltaTime)
    {
        move(velocity.x * deltaTime, velocity.y * deltaTime);
    }

int hitPoints = 100;
~Asteroid() = default;

private:
    sf::Vector2f velocity;
    float speed = 400.0f;
};