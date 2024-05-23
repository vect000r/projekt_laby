#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "classes.hpp"

void game_logic()
{
    sf::RenderWindow window(sf::VideoMode(), "Screen", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    
    sf::Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("projekt_laby/assets/background.png"))
    {
        std::cout << "Error loading background texture" << std::endl;
    }
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setScale(2, 2);
    
    Player player(sf::Vector2f(100, 100), sf::Vector2f(5, 5));
    Enemy enemy(sf::Vector2f(200, 200), sf::Vector2f(1, 1));
    
    sf::Texture player_texture;
    if(!player_texture.loadFromFile("projekt_laby/assets/player.png"))
    {
        std::cout << "Error loading player texture" << std::endl;
        
    }
    player.setTexture(player_texture);
    
    sf::Texture enemy_texture;
    if(!enemy_texture.loadFromFile("projekt_laby/assets/enemy.png"))
    {
        std::cout << "Error loading enemy texture" << std::endl;
    }
    enemy.setTexture(enemy_texture);
    
    
    std::vector<sf::Sprite> bullets;

    sf::Clock delta_clock;
    sf::Clock bullet_clock;
    sf::Time bullet_cooldown;

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
        bullet_cooldown = bullet_clock.getElapsedTime();

        sf::Texture bullet_texture;
            
        if(!bullet_texture.loadFromFile("projekt_laby/assets/bullet.png"))
        {
            std::cout << "Error loading bullet texture" << std::endl;
        }   
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& bullet_cooldown.asSeconds() >= 0.5)
        {
            bullet_clock.restart();
            bullets.push_back(sf::Sprite(bullet_texture));
            bullets.back().setScale(4, 4);
            bullets.back().setOrigin(5, 5);
            bullets.back().setPosition(player.getPosition()+sf::Vector2f(30, 0));
        }
        
        window.clear();
        window.draw(background);
        player.draw(window);
        enemy.draw(window);
        player.movePlayer(window);
        enemy.movePlayer(window);
        player.update(deltaTime);
        enemy.update(deltaTime);
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].move(0, -20);
            window.draw(bullets[i]);
        }
        
        window.display();  
    }
}