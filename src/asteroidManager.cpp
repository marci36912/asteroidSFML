#include <stdio.h>
#include <iostream>
#include <time.h>
#include <algorithm>
#include "asteroidManager.hpp"
#include "bulletManager.hpp"
#include "bullet.hpp"
#include "consts.hpp"
#include "asteroid.hpp"
#include "ship.hpp"

AsteroidManager::AsteroidManager(Ship &s, BulletManager &b)
{
    srand(time(NULL));
    ship = &s;
    bulletManager = &b;
    spawned = 0;
    spawnedTotal = 0;
    cooldown = 0;
}

int AsteroidManager::getRandomN()
{
    return rand() % 3;
}

int AsteroidManager::getRandomRotation()
{
    return rand() % 360;
}

int AsteroidManager::getRandomPosition()
{
    return rand() % WIN_HEIGTH;
}

void AsteroidManager::spawnManager(float t)
{
    if(cooldown == 0)
    {
        //spawn
        if(spawnedTotal < MAXASTEROIDS)
        {
            asteroids.push_back({new Asteroid(getRandomN(), getRandomRotation(), sf::Vector2f(0, getRandomPosition())), 0});

            spawned++;
            spawnedTotal++;
        }
        else if(spawnedTotal >= MAXASTEROIDS && spawned == 0)
        {
            spawnedTotal = 0;
        }

        cooldown = ASTEROIDSPAWNCOOLDOWN;
    }
    else
    {
        cooldown -= t;
        cooldown = std::clamp((cooldown), 0.f, (float)ASTEROIDSPAWNCOOLDOWN);
    }

    checkBounds();
    checkIfDestroyed();
}

void AsteroidManager::showAsteroids(sf::RenderWindow &w)
{
    for(auto a : asteroids)
    {
        a.a->showAsteroid(w);
    }
}

void AsteroidManager::moveAsteroids(float t)
{
    for(auto &a : asteroids)
    {
        a.a->move(t);
    }
}

void AsteroidManager::checkBounds()
{
    for(auto &a : asteroids)
    {
        z = 0;
        tmp = a.a->getBoundingBox();
        if(ship->getBoundingBox().intersects(tmp) && !(a.a->getHit()))
        {
            //asteroid bumbum
            if(ship->getAlive())
            {
                a.a->setHit();
                ship->setAlive();
            }
            return;
        }

        for(auto b : bulletManager->bullets)
        {
            if(b->getBoundingBox().intersects(tmp) && !(a.a->getHit()))
            {
                //asteroid bumbumbum
                a.a->setHit();
                bulletManager->deleteBullet(b);
                break;
            }
            z++;
        }
    }
}

void AsteroidManager::deleteFromList(AsteroidHolder a)
{
    i = 0;
    for(auto aste : asteroids)
    {
        if(aste.a == a.a)
        {
            if(aste.a != NULL)
            {
                delete aste.a;
                aste.a = NULL;
            }
            asteroids.erase(asteroids.begin() + i);
            break;
        }
        i++;
    }
}

void AsteroidManager::checkIfDestroyed()
{
    i = 0;
    for(auto a : asteroids)
    {
        tmpB = a.a->getHit();
        t = a.n;
        if(tmpB && a.n != 2)
        {
            t++;
            for(j = 0; j < 2; j++)
            {
                spawned++;
                asteroids.push_back({new Asteroid(getRandomN() + (3*t), getRandomRotation(), a.a->getPosition()), t});
            }
            deleteFromList(a);
            spawned--;
            ship->addPoints(POINTBIG);
        }
        else if(tmpB)
        {
            deleteFromList(a);
            spawned--;
            ship->addPoints(POINTSMALL);
        }
        i++;
    }
}

void AsteroidManager::freeAsteroids()
{
    for(auto a : asteroids)
    {
        deleteFromList(a);
    }
}