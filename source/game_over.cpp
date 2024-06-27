#include "game_over.hpp"
#include <iostream>

GameOver::GameOver()
{
    if (!font.loadFromFile("assets/Tiny5-Regular.ttf"))
    {
        std::cout << "Error loading font\n";
    }

    float height = 1080.0;

    title.setFont(font);
    title.setString("Game Over");
    title.setScale(2,2);
    title.setFillColor(sf::Color::Red);
    title.setPosition(sf::Vector2f(10, height / (ITEMS + 1) * 0.5));

    menu[0].setFont(font);
    menu[0].setString("Play Again");
    menu[0].setFillColor(sf::Color::White);
    menu[0].setPosition(sf::Vector2f(10, height / (ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setString("Exit");
    menu[1].setFillColor(sf::Color::White);
    menu[1].setPosition(sf::Vector2f(10, height / (ITEMS + 1) * 2));

    selected_index = 0;
}

GameOver::~GameOver(){}

void GameOver::draw(sf::RenderWindow &window)
{
    window.draw(title);
    for (int i = 0; i < ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void GameOver::moveUp()
{
    if (selected_index - 1 >= 0)
    {
        menu[selected_index].setFillColor(sf::Color::White);
        selected_index--;
        menu[selected_index].setFillColor(sf::Color::Green);
    }
}

void GameOver::moveDown()
{
    if (selected_index + 1 < ITEMS)
    {
        menu[selected_index].setFillColor(sf::Color::White);
        selected_index++;
        menu[selected_index].setFillColor(sf::Color::Green);
    }
}

int GameOver::getPressed()
{
    return selected_index;
}

