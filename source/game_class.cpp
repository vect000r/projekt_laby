
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "classes.hpp"
#include "textures.hpp"
#include "game_class.hpp"

Game::Game()
{
    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    score = 0;

    window.create(sf::VideoMode(), "Screen", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    
    if(!backgroundTexture1.loadFromFile("assets/background1.png"))
    {
        std::cout << "Error loading background1 texture" << std::endl;
    }
    background1.setTexture(backgroundTexture1);
    background1.setScale(2, 2);
    
    load_textures();
    
    delta_clock.restart();
    asteroid_clock.restart();

    scrollSpeed = 200.f;

    player.setTexture(player_texture);

    // Initialize some asteroids at the beginning
    for (int i = 0; i < 5; i++)
    {
        sf::Vector2f position(window.getSize().x + 10, std::rand() % window.getSize().y);
        sf::Vector2f size(1, 1);
        Asteroid asteroid(position, size);
        asteroid.setTexture(asteroid_texture);
        asteroids.push_back(asteroid);
    }
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}


    

void Game::score_display(sf::RenderWindow& window, int score) 
{
    sf::Font font;
    if (!font.loadFromFile("assets/Tiny5-Regular.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Score: " + std::to_string(score));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);

    window.draw(text);
}

void Game::hit_points_bar(sf::RenderWindow& window, int hitPoints)
{
    sf::RectangleShape bar;
    bar.setSize(sf::Vector2f(200, 20));
    bar.setFillColor(sf::Color::Red);
    bar.setPosition(window.getSize().x - 210, 10);

    window.draw(bar);

    sf::RectangleShape hp;
    hp.setSize(sf::Vector2f(hitPoints * 2, 20));
    hp.setFillColor(sf::Color::Green);
    hp.setPosition(window.getSize().x - 210, 10);

    window.draw(hp);
}
    
void Game::processEvents()
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
}

void Game::update()
{
    float deltaTime = delta_clock.restart().asSeconds();
    
    player.moveObject(window);
    player.update(deltaTime);
    
    // Spawn new asteroids periodically
    if (asteroid_clock.getElapsedTime().asSeconds() > 2.0f) // spawn every second
    {
        sf::Vector2f position(window.getSize().x + 10, std::rand() % window.getSize().y);
        sf::Vector2f size(1, 1);
        Asteroid new_asteroid(position, size);
        new_asteroid.setTexture(asteroid_texture);
        asteroids.push_back(new_asteroid);
        asteroid_clock.restart();
    }

    // Move and remove asteroids that are off-screen
    for (auto it = asteroids.begin(); it != asteroids.end();)
    {
        it->moveObject(window);
        it->update(deltaTime);
        if (it->getPosition().x < -it->getGlobalBounds().width)
        {
            it = asteroids.erase(it);
        }
        else
        {
            it++;
        }

        if (score >= 100)
        {
            it->asteroid_speed = 400.f;
        }
    }

    // Check collision between player bullets and asteroids
    for (auto bulletIt = player.bullets.begin(); bulletIt != player.bullets.end();)
    {
        bool bulletRemoved = false;
        for (auto asteroidIt = asteroids.begin(); asteroidIt != asteroids.end();)
        {
            if (bulletIt->getGlobalBounds().intersects(asteroidIt->getGlobalBounds()))
            {
                asteroidIt->hitPoints -= 20;
                bulletIt = player.bullets.erase(bulletIt);
                bulletRemoved = true;
                if (asteroidIt->hitPoints <= 0)
                {
                    score += 10;
                    asteroidIt = asteroids.erase(asteroidIt);
                }
                else
                {
                    asteroidIt++;
                }
                break;
            }
            else
            {
                asteroidIt++;
            }
        }
        if (!bulletRemoved)
        {
            bulletIt++;
        }
    }

    // Check collision between player and asteroids
    bool player_hit = false;
    for (auto asteroidIt = asteroids.begin(); asteroidIt != asteroids.end();)
    {
        if (player.getGlobalBounds().intersects(asteroidIt->getGlobalBounds()))
        {
            player_hit = true;
            asteroidIt = asteroids.erase(asteroidIt);
        }
        else
        {
            asteroidIt++;
        }
    }

    if (player_hit)
    {
        player.hitPoints -= 20;
    }

    if (player.hitPoints <= 0)
    {
        window.close();
    }
}

void Game::render()
{
    window.clear();
       
    window.draw(background1);
    player.draw(window);
    player.shoot(window, bullet_texture); 
    for (auto &asteroid : asteroids)
    {
        asteroid.draw(window);
    }

    score_display(window, score);
    hit_points_bar(window, player.hitPoints);

    window.display();
    
};

void game_logic()
{
    Game game;
    game.run();
}