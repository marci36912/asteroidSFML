#pragma once
#include <SFML/Graphics.hpp>
#include "movement.hpp"

//TODO
//make ship go bum

class Ship : public Movement{
    public:
        Ship(const sf::Texture *t);
        void showShip(sf::RenderWindow &w);
        void keyPressed();
        void KeyReleased(sf::Event e);
        void move(float t);
        void getPosition(float &r, sf::Vector2f &p);
        void checkAlive();
        void setAlive();
        bool getAlive();
        void freeLines();
        void addPoints(int n);
        sf::FloatRect getBoundingBox();
    private:
        sf::RectangleShape *lines;
        sf::Sprite ship;
        sf::Font font;
        sf::Text pointsText;
        int lives;
        unsigned int points;
        bool w, a, d;
        bool alive;
        bool invincible;
        bool couldLoadFont;
        float t;
        float respawnCooldown;
        float invincibilityCooldown;
        void rotate(float r);
        void addSpeed();
        void decreaseSpeed();
        void setSpeed();
        void fillLines();
        void setLinePosition();
};