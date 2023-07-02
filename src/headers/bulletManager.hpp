#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ship.hpp"
#include "bullet.hpp"

class BulletManager{
    public:
        BulletManager(Ship &s);
        void deleteBullets(float t);
        void deleteBullet(int n);
        void deleteBullet(Bullet *b);
        void shoot();
        void showBullets(sf::RenderWindow &w);
        void moveBullets(float t);
        void freeBullets();
        std::vector<Bullet *> bullets;
    private:
        float rotation;
        sf::Vector2f position;
        Ship *ship;
        Bullet *tmp;
        int i, j;
        float cooldown;
};