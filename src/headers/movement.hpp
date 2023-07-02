#pragma once
#include <SFML/Graphics.hpp>

class Movement{
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
};