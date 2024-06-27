#include <iostream>
#include <vector>
#include "classes.hpp"
#include "textures.hpp"
#include "game_class.hpp"
#include "menu.hpp"
#include "game_over.hpp"
#include "particle_logic.hpp"

Game::Game()
{
    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(nullptr))); // time(nullptr) returns the current tune and I cast it to the unsigned type
    score = 0;

    window.create(sf::VideoMode(), "Screen", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    
    if(!backgroundTexture1.loadFromFile("assets/background1.png"))
    {
        std::cout << "Error loading background1 texture" << std::endl;
    }
    background1.setTexture(backgroundTexture1);
    background1.setScale(2, 2);
    
    sf::Font font;
    if (!font.loadFromFile("assets/Tiny5-Regular.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }

    load_textures();
    
    delta_clock.restart();
    asteroid_clock.restart();
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
        if (playGame == false && player.hitPoints > 0)
        {
            menu.draw(window);
            window.display();
        }
        
        if (playGame == false && player.hitPoints <= 0)
        {
            game_over_menu.draw(window);
            window.display();
        }
        
        window.clear();
        processEvents();
        
        if (playGame)
        {
            update();
            render();
        }
    }
}


    

void Game::score_display(sf::RenderWindow& window, int score) 
{
    
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
    
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                if (playGame == false)
                    menu.moveUp();
                
                if (playGame == false && player.hitPoints <= 0)
                    game_over_menu.moveUp();
            } 
            else if (event.key.code == sf::Keyboard::Down)
            {
                if (playGame == false)
                    menu.moveDown();
                
                if (playGame == false && player.hitPoints <= 0)
                    game_over_menu.moveDown();
            }
            else if (event.key.code == sf::Keyboard::Return)
            {
                if(menu.getPressed() == 0 || game_over_menu.getPressed() == 0)
                {
                    playGame = true;
                    player.hitPoints = 100;
                    score = 0;
                    asteroids.clear();
                    enemies.clear();
                    player.setPosition(100, window.getSize().y / 2);
                }
                else if(menu.getPressed() == 1 || game_over_menu.getPressed() == 1)
                {
                    window.close();
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
    }
}

template <typename T>
void Game::spawnObjects(std::vector<T>& objects, sf::RenderWindow& window, sf::Texture& object_texture, sf::Clock& object_clock,float& object_speed ,int& score, float& deltaTime, float& spawn_cooldown)
{
    // Spawn new objects periodically
    if (object_clock.getElapsedTime().asSeconds() > spawn_cooldown) // spawn everytime the cooldown allows it 
    {
        score += 5; // for every object spawned the player gets 5 points
        sf::Vector2f position(window.getSize().x + 10, std::rand() % window.getSize().y);
        sf::Vector2f size(1, 1);
        T new_object(position, size);
        new_object.setTexture(object_texture);
        
        objects.push_back(new_object);
        object_clock.restart();
    }

    // Move and remove objects that are off-screen
    for (auto it = objects.begin(); it != objects.end();)
    {
        it->moveObject(window);
        it->update(deltaTime);
        if (it->getPosition().x < -it->getGlobalBounds().width)
        {
            it = objects.erase(it);
        }
        else
        {
            it++;
        }

        if (score >= 100)
        {
            int speedIncrement = score / 50;
            it->setSpeed(object_speed = 100.0f + (speedIncrement * 100.0f));
        }
    }
}



void Game::update()
{
    float deltaTime = delta_clock.restart().asSeconds();
    
    spawnObjects<Asteroid>(asteroids, window, asteroid_texture, asteroid_clock, asteroids.back().asteroid_speed, score, deltaTime, asteroid_cooldown);
    spawnObjects<Enemy>(enemies, window, enemy_texture, enemy_clock, enemies.back().enemy_speed, score, deltaTime, enemy_cooldown);
    
    player.moveObject(window);
    player.update(deltaTime);
    particle_logic.update(deltaTime);
    
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
                particle_logic.addParticle(asteroidIt->getPosition(), 1.0f);
                
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

    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();)
    {
        for (auto enemy_bulletIt = enemyIt->enemy_bullets.begin(); enemy_bulletIt != enemyIt->enemy_bullets.end();)
        {
            if (enemy_bulletIt->getGlobalBounds().intersects(player.getGlobalBounds()))
            {
                player_hit = true;
                enemy_bulletIt = enemyIt->enemy_bullets.erase(enemy_bulletIt);
                break; 
            }
            else
            {
                enemy_bulletIt++;
            }
        }
        
        if (player_hit)
        {
            break; 
        }
        
        enemyIt++;
    }
    
    // Check collision between player bullets and enemies
    for (auto bulletIt = player.bullets.begin(); bulletIt != player.bullets.end();)
    {
        bool bulletRemoved = false;
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();)
        {
            if (bulletIt->getGlobalBounds().intersects(enemyIt->getGlobalBounds()))
            {
                enemyIt->hitPoints -= 20;
                bulletIt = player.bullets.erase(bulletIt);
                bulletRemoved = true;
                particle_logic.addParticle(enemyIt->getPosition(), 1.0f);
                
                if (enemyIt->hitPoints <= 0)
                {
                    score += 20;
                    
                    enemyIt = enemies.erase(enemyIt);
                }
                else
                {
                    enemyIt++;
                }
                break;
            }
            else
            {
                enemyIt++;
            }
        }
        if (!bulletRemoved)
        {
            bulletIt++;
        }
    }

    if (player_hit)
    {
        player.hitPoints -= 20;
    }

    if (player.hitPoints <= 0)
    {
        playGame = false;
    }
}

void Game::render()
{
    menu.draw(window);
    window.clear();
    window.draw(background1);
    
    if (player_hit)
    {
        for (int i = 0; i < 3; i++)
        {
            particle_logic.addParticle(player.getPosition(), 4.0f);
        }
        particle_logic.draw(window, player_particle_texture);
        playGame = true;
        player_hit = false;
    }
    
    particle_logic.draw(window, asteroid_particle_texture);
    player.draw(window);
    player.shoot(window, bullet_texture); 
    
    for (auto &asteroid : asteroids)
    {
        asteroid.draw(window);
    }

    for (auto &enemy : enemies)
    {
        enemy.draw(window);
        enemy.shoot(window, enemy_bullet_texture);
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
