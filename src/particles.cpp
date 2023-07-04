#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "particles.hpp"

Particles::Particles(sf::Vector2f origin, int n): points(sf::Points, n), pointDetails(n)
{
    this->n = n;
    for(int i = 0; i < n; ++i)
    {
        float rotation = (rand()%360) * (3.14/180);
        pointDetails[i].originalLifeTime = (rand()%3)+1;
        pointDetails[i].currentLifeTime = pointDetails[i].originalLifeTime;
        pointDetails[i].originalSpeed = (rand()%50) + 50;
        pointDetails[i].direction = sf::Vector2f(std::cos(rotation), -std::sin(rotation));
        points[i].position = origin;
        points[i].color = sf::Color::White;
    }
}

void Particles::showParticles(sf::RenderWindow &w)
{
    w.draw(points);
}

void Particles::update(float t)
{
    float ratio;
    for(int i = 0; i < n; ++i)
    {
        ratio = std::clamp(pointDetails[i].currentLifeTime/pointDetails[i].originalLifeTime, (float)0, (float)100);
        pointDetails[i].currentLifeTime -= t;
        pointDetails[i].apliedSpeed = pointDetails[i].originalSpeed * ratio;
        points[i].color.a = 255 * ratio;
        points[i].position.x += (pointDetails[i].direction.x * pointDetails[i].apliedSpeed) * t;
        points[i].position.y += (pointDetails[i].direction.y * pointDetails[i].apliedSpeed) * t;
    }
}

int Particles::getN()
{
    return n;
}

ParticleManager::ParticleManager() {}

void ParticleManager::newParticles(sf::Vector2f pos, int n)
{
    activeParticles.push_back({new Particles(pos, n), 3});
}

void ParticleManager::showParticles(sf::RenderWindow &w)
{
    for(auto a : activeParticles)
    {
        a.particle->showParticles(w);
    }
}

void ParticleManager::updateParticles(float t)
{
    for(auto &a : activeParticles)
    {
        a.time -= t;
        a.particle->update(t);

        if(a.time <= 0)
        {
            deleteItem(a);
        }
    }
}
void ParticleManager::deleteItem(const ParticleCollection toDelete)
{
    activeParticles.erase(std::remove(activeParticles.begin(), activeParticles.end(), toDelete), activeParticles.end());
}

void ParticleManager::freeParticles()
{
    for(auto a : activeParticles)
    {
        deleteItem(a);
    }
}