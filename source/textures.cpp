#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "textures.hpp"

sf::Texture player_texture;
sf::Texture enemy_texture;
sf::Texture asteroid_texture;
sf::Texture bullet_texture;
sf::Texture asteroid_particle_texture;
sf::Texture player_particle_texture;
sf::Texture enemy_bullet_texture;

void load_textures()
{
    if(!player_texture.loadFromFile("assets/player.png"))
    {
        std::cout << "Error loading player texture\n";
        
    }
    
    if(!enemy_texture.loadFromFile("assets/enemy.png"))
    {
        std::cout << "Error loading enemy texture\n";
        
    }

    if(!asteroid_texture.loadFromFile("assets/asteroid.png"))
    {
        std::cout << "Error loading asteroid texture\n";
        
    }

    if(!bullet_texture.loadFromFile("assets/bullet.png"))
    {
        std::cout << "Error loading bullet texture\n";
    } 

    if(!asteroid_particle_texture.loadFromFile("assets/asteroid_particle.png"))
    {
        std::cout << "Error loading asteroid particle texture\n";
    }

    if(!player_particle_texture.loadFromFile("assets/player_particle.png"))
    {
        std::cout << "Error loading player particle texture\n";
    }

    if(!enemy_bullet_texture.loadFromFile("assets/enemy_bullet.png"))
    {
        std::cout << "Error loading enemy bullet texture\n";
    }
}