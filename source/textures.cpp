#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

//sf::Texture backgroundTexture1;
//sf::Texture backgroundTexture2;
sf::Texture player_texture;
sf::Texture enemy_texture;
sf::Texture asteroid_texture;
sf::Texture bullet_texture;
//sf::Sprite background1;
//sf::Sprite background2;

void load_textures()
{
    

    if(!player_texture.loadFromFile("player.png"))
    {
        std::cout << "Error loading player texture" << std::endl;
        
    }
    
    if(!enemy_texture.loadFromFile("enemy.png"))
    {
        std::cout << "Error loading enemy texture" << std::endl;
        
    }

    if(!asteroid_texture.loadFromFile("asteroid.png"))
    {
        std::cout << "Error loading asteroid texture" << std::endl;
        
    }

    if(!bullet_texture.loadFromFile("bullet.png"))
    {
        std::cout << "Error loading bullet texture" << std::endl;
        } 

}