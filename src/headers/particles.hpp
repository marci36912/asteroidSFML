#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct ParticleDetail{
    sf::Vector2f direction;
    float originalLifeTime;
    float currentLifeTime;
    float originalSpeed;
    float apliedSpeed;
};

class Particles{
    public:
        Particles(sf::Vector2f origin, int n);
        void showParticles(sf::RenderWindow &w);
        void update(float t);
        int getN();
    private:
        sf::VertexArray points;
        std::vector<ParticleDetail> pointDetails;
        int n;
};

struct ParticleCollection{
    Particles *particle;
    float time;
    friend bool operator==(const ParticleCollection &l, const ParticleCollection &r)
    {
        return l.particle == r.particle && l.time == r.time;
    }
};

class ParticleManager{
    public:
        ParticleManager();
        void newParticles(sf::Vector2f pos, int n);
        void showParticles(sf::RenderWindow &w);
        void updateParticles(float t);
        void freeParticles();
    private:
        std::vector<ParticleCollection> activeParticles;
        void deleteItem(const ParticleCollection bb);
};