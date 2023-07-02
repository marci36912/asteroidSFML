#include <algorithm>
#include <iostream>
#include <vector>
#include "bulletManager.hpp"
#include "bullet.hpp"
#include "consts.hpp"

BulletManager::BulletManager(Ship &s)
{
    ship = &s;
    j = 0;
    cooldown = 0;
}

void BulletManager::deleteBullets(float t)
{
    i = 0;
    for(auto &a : bullets)
    {
        if(a->time <= 0)
        {
            deleteBullet(i);
        }
        else
        {
            a->time -= t;
        }
        i++;
    }

    cooldown -= t;
    cooldown = std::clamp((cooldown), 0.f, (float)COOLDOWNMAX);
}

void BulletManager::deleteBullet(int n)
{
    tmp = bullets[n];
    bullets.erase(bullets.begin() + n);
    if(tmp != NULL)
    {
        delete tmp;
        tmp = NULL;
    }
}

void BulletManager::deleteBullet(Bullet *b)
{
    i = 0;
    for(auto &a : bullets)
    {
        if(a == b)
        {
            deleteBullet(i);
        }
        i++;
    }
}

void BulletManager::shoot()
{
    if(cooldown<=0)
    {
        ship->getPosition(rotation, position);
        bullets.push_back(new Bullet(rotation + 90, position));

        if(++j==BULLETAMMOUNT)
        {
            cooldown += COOLDOWNMAX;
            j = 0;
        }
        else
        {
            cooldown += COOLDOWN;
        }
    }
}

void BulletManager::showBullets(sf::RenderWindow &w)
{
    for(auto &a : bullets)
    {
        a->showBullet(w);
    }
}

void BulletManager::moveBullets(float t)
{
    for(auto &a : bullets)
    {
        a->move(t);
    }
}

void BulletManager::freeBullets()
{
    i = 0;
    for(auto a : bullets)
    {
        deleteBullet(i);
        i++;
    }
}