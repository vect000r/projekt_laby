#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define ITEMS 2

class Menu
{
public:
    Menu();
    ~Menu();

    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getPressed();
private:
    int selected_index;
    sf::Font font;
    sf::Text menu[ITEMS];
    sf::Text title;
};

#endif // MENU_H