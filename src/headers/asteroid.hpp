#pragma once
#include <SFML/Graphics.hpp>
#include "movement.hpp"

class Asteroid : public Movement{
    public:
        Asteroid();
        Asteroid(int n, float r, sf::Vector2f p);
        static void setAsteroidTextures(sf::Texture *t);
        void showAsteroid(sf::RenderWindow &w);
        bool getHit();
        void setHit();
        void move(float t);
        sf::FloatRect getBoundingBox();
        sf::Vector2f getPosition();
    private:
        static sf::Texture *asteroidTextures;
        sf::Sprite asteroid;
        bool gotHit;
};