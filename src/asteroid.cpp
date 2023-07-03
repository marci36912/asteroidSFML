#include "asteroid.hpp"
#include "consts.hpp"

sf::Texture *Asteroid::asteroidTextures;

Asteroid::Asteroid()
{

}

Asteroid::Asteroid(int n, float r, sf::Vector2f p)
{
    asteroid.setTexture(*(asteroidTextures + n));
    asteroid.rotate(r);
    asteroid.setPosition(p);
    updateRotation(r);
    gotHit = false;
}

void Asteroid::setAsteroidTextures(sf::Texture *t)
{
    asteroidTextures = t;
}

void Asteroid::showAsteroid(sf::RenderWindow &w)
{
    showDebug(getBoundingBox(), w);
    w.draw(asteroid);
}

bool Asteroid::getHit()
{
    return gotHit;
}

void Asteroid::setHit()
{
    gotHit = true;
}

void Asteroid::move(float t)
{
    speed.x = -getCosine() * t * ASTEROIDSPEED;
    speed.y = getSine() * t * ASTEROIDSPEED;
    asteroid.move(speed);
    checkBounds(asteroid);
}

sf::FloatRect Asteroid::getBoundingBox()
{
    return asteroid.getGlobalBounds();
}

sf::Vector2f Asteroid::getPosition()
{
    return asteroid.getPosition();
}