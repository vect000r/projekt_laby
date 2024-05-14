#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

class Player : public sf::Sprite
{
public:
    Player(sf::Vector2f position, sf::Vector2f size)
    {
        sf::Texture texture;
        if(!texture.loadFromFile("player.png"))
        {
            std::cout << "Error loading player texture" << std::endl;
        
        }
        
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
            if (getPosition().x <= 0)
            {
                setPosition(0, getPosition().y);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            velocity.x = speed;
            if (getPosition().x + getScale().x >= window.getSize().x)
            {
                setPosition(window.getSize().x - getScale().x, getPosition().y);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            velocity.y = -speed;
            if (getPosition().y <= 0)
            {
                setPosition(getPosition().x, 0);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            velocity.y = speed;
            if (getPosition().y + getScale().y >= window.getSize().y)
            {
                setPosition(getPosition().x, window.getSize().y - getScale().y);
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

class Bullet : public sf::RectangleShape
{
public:
    Bullet(sf::Vector2f position, sf::Vector2f size, sf::Color color)
    {
        setSize(size);
        setFillColor(color);
        setPosition(position);
    }

    void moveBullet(sf::RenderWindow& window)
    {
        velocity.x = 0;
        velocity.y = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            velocity.y = -speed;
            if (getPosition().y <= 0)
            {
                setPosition(getPosition().x, 0);
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



int main()
{
    sf::RenderWindow window(sf::VideoMode(), "Screen", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    
    sf::Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("background.png"))
    {
        std::cout << "Error loading background texture" << std::endl;
    }
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setScale(2, 2);
    
    Player player(sf::Vector2f(100, 100), sf::Vector2f(5, 5));
    sf::Texture texture;
    if(!texture.loadFromFile("player.png"))
    {
        std::cout << "Error loading player texture" << std::endl;
    }
    player.setTexture(texture);
    
    
    
    std::vector<sf::CircleShape> bullets;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        float deltaTime = clock.restart().asSeconds();
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            bullets.push_back(sf::CircleShape());
            bullets.back().setRadius(5);
            bullets.back().setOrigin(5, 5);
            bullets.back().setPosition(player.getPosition()+sf::Vector2f(40, 0));
        }
        
        
        window.clear();
        window.draw(background);
        player.draw(window);
        player.movePlayer(window);
        player.update(deltaTime);
        
        
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].move(0, -5);
            window.draw(bullets[i]);
        }
        
        window.display();  
    }
}
