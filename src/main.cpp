#include <SFML/Graphics.hpp>
#include <iostream>
#include "textures.hpp"
#include "ship.hpp"
#include "bullet.hpp"
#include "consts.hpp"
#include "bulletManager.hpp"
#include "asteroid.hpp"
#include "asteroidManager.hpp"

int main()
{
    TextureManager tex;
    Ship ship(tex.getShip());
    Bullet::setBulletTexture(tex.getBullet());
    Asteroid::setAsteroidTextures(tex.getAsteroid());
    BulletManager bulletManager(ship);
    AsteroidManager asteroidManager(ship, bulletManager);
    sf::Clock c;
    sf::Time t;
    float deltaTime = 0;
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGTH), "asteroid");
    window.setFramerateLimit(MAXFPS);

    while (window.isOpen())
    {
        c.restart();
        sf::Event event;

        deltaTime = t.asSeconds();

        ship.move(deltaTime);
        ship.checkAlive(deltaTime);

        bulletManager.deleteBullets(deltaTime);
        bulletManager.moveBullets(deltaTime);

        asteroidManager.spawnManager(deltaTime);
        asteroidManager.moveAsteroids(deltaTime);
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(ship.getAlive())
                    {
                        ship.keyPressed();
                        if(event.key.code == sf::Keyboard::Space)
                            bulletManager.shoot();
                    }
                    break;
                case sf::Event::KeyReleased:
                    ship.KeyReleased(event);
                    break;
                default:
                    break;
            }
        }

        window.clear();
        ship.showShip(window);
        bulletManager.showBullets(window);
        asteroidManager.showAsteroids(window);
        window.display();

        t = c.getElapsedTime();
    }

    bulletManager.freeBullets();
    asteroidManager.freeAsteroids();
    ship.freeLines();
    tex.freeTextures();

    return 0;
}
