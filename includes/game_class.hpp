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

class Game
{
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Clock delta_clock;
    float deltaTime;
    sf::Clock asteroid_clock;
    float scrollSpeed;
    Player player;
    Menu menu;
    sf::Texture backgroundTexture1;
    sf::Sprite background1;
    std::vector<Asteroid> asteroids;
    int score;
    bool playGame = false;
    void score_display(sf::RenderWindow& window, int score);
    void hit_points_bar(sf::RenderWindow& window, int hitPoints);
    void processEvents();
    void update();
    void render();
};

void game_logic();

#endif // GAME_CLASS_H
