#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include "movement.hpp"
#include "consts.hpp"

bool Movement::debug = false;

float Movement::getSine()
{
    return std::sin(radian(rotation));
}

float Movement::getCosine()
{
    return std::cos(radian(rotation));
}

double Movement::radian(float a)
{
    return a * 3.1415926 / 180;
}

void Movement::checkBounds(sf::Transformable &t)
{
    sf::Vector2f c = t.getPosition();

    if(c.x > WIN_WIDTH)
    {
        c.x = 0;
        t.setPosition(c);
    }
    else if(c.x < 0)
    {
        c.x = WIN_WIDTH;
        t.setPosition(c);
    }
    else if(c.y > WIN_HEIGTH)
    {
        c.y = 0;
        t.setPosition(c);
    }
    else if(c.y < 0)
    {
        c.y = WIN_HEIGTH;
        t.setPosition(c);
    }

}

void Movement::updateRotation(sf::Transformable &t)
{
    rotation = t.getRotation();
}

void Movement::updateRotation(float r)
{
    rotation = r;
}

void Movement::clampSpeed(float lower, float upper, int n)
{
    switch(n)
    {
        case 1:
            speed.x = std::clamp(speed.x, lower, upper);
            break;
        case 2:
            speed.y = std::clamp(speed.y, lower, upper);
            break;
        case 3:
            speed.x = std::clamp(speed.x, lower, upper);
            speed.y = std::clamp(speed.y, lower, upper);
            break;
        default:
            break;
    }
}

void Movement::showDebug(sf::FloatRect t, sf::RenderWindow &w)
{
    if(debug)
    {
        hitbox.setSize(sf::Vector2f(t.height, t.width));
        hitbox.setOutlineColor(sf::Color(255,0,0,255));
        hitbox.setOutlineThickness(1);
        hitbox.setFillColor(sf::Color(0,0,0,0));
        hitbox.setPosition(sf::Vector2f(t.left, t.top));

        w.draw(hitbox);
    }
}

void Movement::changeDebug()
{
    debug = !debug;
}