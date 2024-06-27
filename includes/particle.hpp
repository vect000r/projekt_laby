#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Particle 
{
public:
    sf::Sprite particle_sprite;
    sf::Vector2f velocity;
    float lifespan;
    bool is_alive = true;
    Particle(sf::Vector2f position, float scale);
    void update(float deltaTime);
};

#endif