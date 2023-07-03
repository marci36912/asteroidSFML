#pragma once
#include <SFML/Graphics.hpp>

class Movement{
    public:
        static void changeDebug();
    protected:
        sf::Vector2f speed;
        float rotation;
        float getSine();
        float getCosine();
        double radian(float a);
        void checkBounds(sf::Transformable &t);
        void updateRotation(sf::Transformable &t);
        void updateRotation(float r);
        void clampSpeed(float lower, float upper, int n);
        void showDebug(sf::FloatRect t, sf::RenderWindow &w);
    private:
        static bool debug;
        sf::RectangleShape hitbox;
};