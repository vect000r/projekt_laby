#include "menu.hpp"
#include <iostream>

Menu::Menu()
{
    if(!font.loadFromFile("assets/Tiny5-Regular.ttf"))
    {
        std::cout << "Error loading font\n";
    }
    
    float width = 1920.0;
    float height = 1080.0;

    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setScale(2, 2);
    title.setString("Space Race");
    title.setPosition(sf::Vector2f(10, height / (ITEMS + 1) * 0.5));
    
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Green);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(10, height / (ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Exit");
    menu[1].setPosition(sf::Vector2f(10, height / (ITEMS + 1) * 2));

    selected_index = 0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
    window.draw(title);
    for (int i = 0; i < ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::moveUp()
{
    if (selected_index - 1 >= 0)
    {
        menu[selected_index].setFillColor(sf::Color::White);
        selected_index--;
        menu[selected_index].setFillColor(sf::Color::Green);
    }
}

void Menu::moveDown()
{
    if (selected_index + 1 < ITEMS)
    {
        menu[selected_index].setFillColor(sf::Color::White);
        selected_index++;
        menu[selected_index].setFillColor(sf::Color::Green);
    }
}

int Menu::getPressed()
{
    return selected_index;
}