#include "particle_logic.hpp"

void ParticleLogic::addParticle(sf::Vector2f position, float scale)
{
    particles.push_back(Particle(position, scale));
}
 
void ParticleLogic::update(float deltaTime)
{
    for (auto& particle : particles)
    {
        particle.update(deltaTime);
    }
    particles.erase(
        std::remove_if(particles.begin(), particles.end(), [](const Particle& particle) { return !particle.is_alive; }), particles.end()); // usuwamy wszystkie particle w zakresie particles.begin() do particles.end() które nie są żywe
}

void ParticleLogic::draw(sf::RenderWindow& window, sf::Texture texture)
{
    for (auto& particle : particles)
    {
        particle.particle_sprite.setTexture(texture);
        window.draw(particle.particle_sprite);
    }
}


