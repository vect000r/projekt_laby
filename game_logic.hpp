#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "classes.hpp"
#include <cmath>

void game_logic()
{
    sf::RenderWindow window(sf::VideoMode(), "Screen", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    
    sf::Clock delta_clock;
    sf::Clock bullet_clock;
    sf::Time bullet_cooldown;
    sf::Texture backgroundTexture;
    
    float scrollSpeed = 200.f;
    
    if(!backgroundTexture.loadFromFile("background.png"))
    {
        std::cout << "Error loading background texture" << std::endl;
    }
    
    sf::Sprite background1;
    background1.setTexture(backgroundTexture);
    background1.setScale(2, 2);
    
    sf::Sprite background2;
    background2.setTexture(backgroundTexture);
    background2.setScale(2, 2);

    Player player(sf::Vector2f(0, 0), sf::Vector2f(5, 5));
    Enemy enemy(sf::Vector2f(0, 0), sf::Vector2f(1, 1));
    
    sf::Texture player_texture;
    if(!player_texture.loadFromFile("player.png"))
    {
        std::cout << "Error loading player texture" << std::endl;
        
    }
    player.setTexture(player_texture);
    
    sf::Texture enemy_texture;
    if(!enemy_texture.loadFromFile("enemy.png"))
    {
        std::cout << "Error loading enemy texture" << std::endl;
        
    }
    enemy.setTexture(enemy_texture);
    
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
        
        
        float deltaTime = delta_clock.restart().asSeconds();
        background1.move(-scrollSpeed * deltaTime, 0.f);
        background2.move(-scrollSpeed * deltaTime, 0.f);
        
        if (background1.getPosition().x + backgroundTexture.getSize().x < 0) {
            background1.setPosition(background2.getPosition().x + backgroundTexture.getSize().x, 0.f);
        }
        if (background2.getPosition().x + backgroundTexture.getSize().x < 0) {
            background2.setPosition(background1.getPosition().x + backgroundTexture.getSize().x, 0.f);
        }

        sf::Texture bullet_texture;
            
        if(!bullet_texture.loadFromFile("bullet.png"))
        {
            std::cout << "Error loading bullet texture" << std::endl;
        }   
        
        window.clear();
        window.draw(background1);
        window.draw(background2);

        player.draw(window);
        enemy.draw(window);
        
        player.movePlayer(window);
        player.shoot(window, bullet_texture);
        
        enemy.movePlayer(window);
        enemy.shoot(window, bullet_texture);
        
        player.update(deltaTime);
        enemy.update(deltaTime);
        
        
        window.display();  
    }
}