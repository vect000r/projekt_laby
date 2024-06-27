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
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](const Particle& particle) { return !particle.is_alive; }), particles.end()); // we remove every particle from the range that is not alive

void ParticleLogic::draw(sf::RenderWindow& window, sf::Texture texture)
{
    for (auto& particle : particles)
    {
        particle.particle_sprite.setTexture(texture);
        window.draw(particle.particle_sprite);
    }
}


