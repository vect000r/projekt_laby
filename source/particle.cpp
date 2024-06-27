#include "particle.hpp"
#include <iostream>

Particle::Particle(sf::Vector2f position, float scale)
{
    velocity = sf::Vector2f(0, 0);
    particle_sprite.setScale(scale, scale);
    particle_sprite.setPosition(position);
    lifespan = 1.0f;
    velocity.x = rand() % 200 - 100.0f;
    velocity.y = rand() % 200 - 100.0f;
}

void Particle::update(float deltaTime)
{
    particle_sprite.move(velocity * deltaTime);
    lifespan -= deltaTime; // with every frame we decrease the lifespan of the particle so that 
    if (lifespan <= 0)
    {
        is_alive = false;
    }
}
