#include <SFML/Graphics.hpp>

class TextureManager{
    public:
        TextureManager();
        sf::Texture* getShip();
        sf::Texture* getBullet();
        sf::Texture* getAsteroid();
        void freeTextures();
    private:
        sf::Texture *ship;
        sf::Texture *bullet;
        sf::Texture *asteroids;
};