#include "bullet.hpp"
#include "consts.hpp"

sf::Texture *Bullet::bulletTexture;
Bullet::Bullet(){};
Bullet::Bullet(float r, sf::Vector2f p)
{
    bullet.rotate(r);
    bullet.setPosition(p);
    bullet.setTexture(*bulletTexture);
    updateRotation(r);
    time = BULLETLIFESPAM;
}

void Bullet::showBullet(sf::RenderWindow &w)
{
    showDebug(getBoundingBox(), w);
    w.draw(bullet);
}

void Bullet::setBulletTexture(sf::Texture *t)
{
    bulletTexture = t;
}

void Bullet::move(float t)
{
    speed.x = -getCosine() * t * BULLETSPEED;
    speed.y = -getSine() * t * BULLETSPEED;
    bullet.move(speed);
    checkBounds(bullet);
}

sf::FloatRect Bullet::getBoundingBox()
{
    return bullet.getGlobalBounds();
}