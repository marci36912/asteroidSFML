#pragma once
#include <SFML/Graphics.hpp>
#include "movement.hpp"

class Bullet : public Movement{
    public:
        Bullet();
        Bullet(float r, sf::Vector2f p);
        static void setBulletTexture(sf::Texture *t);
        void showBullet(sf::RenderWindow &w);
        sf::FloatRect getBoundingBox();
        void move(float t);
        float time;
    private:
        static sf::Texture *bulletTexture;
        sf::Sprite bullet;
};