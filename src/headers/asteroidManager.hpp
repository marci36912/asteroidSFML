#include <SFML/Graphics.hpp>
#include <vector>
#include "bulletManager.hpp"
#include "asteroid.hpp"
#include "ship.hpp"

struct AsteroidHolder{
    Asteroid * a;
    int n;
};

class AsteroidManager{
    public:
        AsteroidManager(Ship &s, BulletManager &b);
        void spawnManager(float t);
        void showAsteroids(sf::RenderWindow &w);
        void moveAsteroids(float t);
        void freeAsteroids();
    private:
        sf::FloatRect tmp;
        int i, j, z, t;
        int spawned;
        int spawnedTotal;
        float cooldown;
        bool tmpB;
        Ship *ship;
        BulletManager *bulletManager;
        std::vector<AsteroidHolder> asteroids;
        int getRandomN();
        int getRandomRotation();
        int getRandomPosition();
        void checkBounds();
        void checkIfDestroyed();
        void deleteFromList(AsteroidHolder a);
};