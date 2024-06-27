#ifndef PARTICLE_LOGIC_H
#define PARTICLE_LOGIC_H

#include <vector>
#include "particle.hpp"

class ParticleLogic
{
public:
    std::vector<Particle> particles;
    void addParticle(sf::Vector2f position, float scale);
    void update(float deltaTime);
    void draw(sf::RenderWindow &window, sf::Texture texture);
};

#endif