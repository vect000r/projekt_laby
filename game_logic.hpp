#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime> // for time()

#include "classes.hpp"
#include "textures.hpp"

void score_display(sf::RenderWindow& window, int score)
{
    sf::Font font;
    if (!font.loadFromFile("Tiny5-Regular.ttf"))
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

void hit_points_bar(sf::RenderWindow& window, int hitPoints)
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


void game_logic()
{
    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int score = 0;

    sf::RenderWindow window(sf::VideoMode(), "Screen", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    sf::Clock delta_clock;
    sf::Clock asteroid_clock; // Clock for spawning new asteroids

    float scrollSpeed = 200.f;

    Player player(sf::Vector2f(0, window.getSize().y / 2), sf::Vector2f(5, 5));
    //Enemy enemy(sf::Vector2f(0, 0), sf::Vector2f(1, 1));
    std::vector<Asteroid> asteroids;
    load_textures();

    sf::Texture backgroundTexture1;

    if (!backgroundTexture1.loadFromFile("background1.png"))
    {
        std::cout << "Error loading background texture" << std::endl;
    }

    sf::Sprite background1;
    background1.setTexture(backgroundTexture1);
    background1.setScale(2, 2);

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

        // poruszaj asteroidami w lewo i usuwaj je jeśli są poza ekranem 
        for(auto it = asteroids.begin(); it != asteroids.end();)
        {
            it->moveObject(window);
            it->update(deltaTime);
            if(it->getPosition().x < -it->getGlobalBounds().width)
            {
                it = asteroids.erase(it); 
            }
            else
            {
                it++;
            }
        
            if(score >= 100)
            {
                it->speed = 400.f;
            }
        
        }
        
        // mechanizm kolizji pocisków gracza z asteroidami
        // dla każdego pocisku gracza sprawdź czy trafił w asteroidę
        // jeśli asteroida i pocisk się przecinają to zmniejsz hp asteroidy i usuń pocisk
        // jeśli hp asteroidy <= 0 to usuń asteroidę
        // jeśli nie, to przejdź do następnej asteroidy
        // jeśli pocisk nie trafił w żadną asteroidę to przejdź do następnego pocisku

        for (auto bulletIt = player.bullets.begin(); bulletIt != player.bullets.end();)
        {
            bool bulletRemoved = false;
            for (auto asteroidIt = asteroids.begin(); asteroidIt != asteroids.end();)
            {
                if (bulletIt->getGlobalBounds().intersects(asteroidIt->getGlobalBounds()))
                {
                    asteroidIt->hitPoints-=20;
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

        if(player_hit)
        {
            player.hitPoints -= 20;
        }

        if(player.hitPoints <= 0)
        {
            window.close();
        }

        window.clear();

        window.draw(background1);
        player.draw(window);
        //enemy.draw(window);

        for (auto &asteroid : asteroids)
        {
             
            asteroid.draw(window);
            
        }

        score_display(window, score);
        hit_points_bar(window, player.hitPoints);
        
        
        player.moveObject(window);
        player.shoot(window, bullet_texture);

        player.update(deltaTime);

        window.display();
    }
}
