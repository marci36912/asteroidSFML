#include <string>
#include <iostream>
#include "textures.hpp"

TextureManager::TextureManager()
{
    ship = new sf::Texture;
    bullet = new sf::Texture;
    std::string utl = "Loading image failed: ";
    if(!ship->loadFromFile("sprites/ship.png"))
        std::cout << utl << "ship" << std::endl;
    if(!bullet->loadFromFile("sprites/bullet.png"))
        std::cout << utl << "bullet" << std::endl;

    asteroids = new sf::Texture[9];
    std::string file;

    for(int i = 0; i < 9; i++)
    {
        file = "sprites/asteroid";
        file += std::to_string(i+1);
        file += ".png";

        if(!asteroids[i].loadFromFile(file))
            std::cout << utl << file << std::endl;
    }
}

void TextureManager::freeTextures()
{
    if(ship != NULL)
    {
        delete ship;
        ship = NULL;
    }
    if(bullet != NULL)
    {
        delete bullet;
        bullet = NULL;
    }
    if(asteroids != NULL)
    {
        delete[] asteroids; //segs fault when called in destructor???
        asteroids = NULL;
    }
}

sf::Texture* TextureManager::getShip()
{
    return ship;
}

sf::Texture* TextureManager::getBullet()
{
    return bullet;
}

sf::Texture* TextureManager::getAsteroid()
{
    return asteroids;
}
