#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "classes.hpp"
#include "textures.hpp"
#include "menu.hpp"
#include "game_over.hpp"
#include "particle_logic.hpp"

class Game
{
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Clock delta_clock;
    sf::Text game_over;
    sf::Font font;
    float deltaTime;
    sf::Clock asteroid_clock;
    sf::Clock enemy_clock;
    float asteroid_cooldown = 2.0f;
    float enemy_cooldown = 10.0f;
    bool player_hit = false;   
    Player player;
    Menu menu;
    GameOver game_over_menu;
    ParticleLogic particle_logic;
    sf::Texture backgroundTexture1;
    sf::Sprite background1;
    std::vector<Asteroid> asteroids;
    std::vector<Enemy> enemies;
    int score;
    bool playGame = false;
    void score_display(sf::RenderWindow& window, int score);
    void hit_points_bar(sf::RenderWindow& window, int hitPoints);
    void processEvents();
    void update();
    void render();
    template <typename T> 
    void spawnObjects(std::vector<T>& objects, sf::RenderWindow& window, sf::Texture& object_texture, sf::Clock& object_clock, float& object_speed, int& score, float& deltaTime, float& spawn_cooldown);


};

void game_logic();

#endif // GAME_CLASS_H
