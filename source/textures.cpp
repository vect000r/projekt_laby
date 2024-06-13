#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "textures.hpp"

sf::Texture player_texture;
sf::Texture enemy_texture;
sf::Texture asteroid_texture;
sf::Texture bullet_texture;


void load_textures()
{
    if(!player_texture.loadFromFile("assets/player.png"))
    {
        std::cout << "Error loading player texture" << std::endl;
        
    }
    
    if(!enemy_texture.loadFromFile("assets/enemy.png"))
    {
        std::cout << "Error loading enemy texture" << std::endl;
        
    }

    if(!asteroid_texture.loadFromFile("assets/asteroid.png"))
    {
        std::cout << "Error loading asteroid texture" << std::endl;
        
    }

    if(!bullet_texture.loadFromFile("assets/bullet.png"))
    {
        std::cout << "Error loading bullet texture" << std::endl;
        } 

}