#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(), "Screen", sf::Style::Fullscreen);

    sf::Vector2f velocity(0.0f, 0.0f);
    sf::Clock clock;
    float speed = 400.0f;

    sf::RectangleShape player;
    player.setSize(sf::Vector2f(30, 30));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(100, 100);
    
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            velocity.x = -speed;
            if(player.getPosition().x <= 0)
            {
                player.setPosition(0, player.getPosition().y);
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {    
            velocity.x = speed;
            if(player.getPosition().x + player.getSize().x >= window.getSize().x)
            {    
                player.setPosition(window.getSize().x - player.getSize().x, player.getPosition().y);
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            velocity.y = -speed;
            if(player.getPosition().y <= 0)
            { 
                player.setPosition(player.getPosition().x, 0);
            }        
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            velocity.y = speed;
            if(player.getPosition().y + player.getSize().y >= window.getSize().y)
            {    
                player.setPosition(player.getPosition().x, window.getSize().y - player.getSize().y);
            }
        }
        else
        {
            velocity.x = 0;
            velocity.y = 0; 
        }

        float deltaTime = clock.restart().asSeconds();

        window.clear();
        player.move(velocity.x * deltaTime, velocity.y * deltaTime);
        window.draw(player);
        window.display();
    }
}