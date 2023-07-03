#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "ship.hpp"
#include "consts.hpp"

Ship::Ship(const sf::Texture *t)
{
    speed = sf::Vector2f(0,0);
    w = a = d = false;
    lives = LIVES;
    alive = true;
    invincible = false;
    invincibilityCooldown = 0;
    points = 0;

    ship.setTexture(*t);

    sf::Vector2u tmp = t->getSize();
    ship.setOrigin(sf::Vector2f(tmp.x/2, tmp.y/2));
    ship.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGTH/2));

    if(font.loadFromFile("./fonts/hyperspace.ttf"))
    {
        pointsText.setFont(font);
        pointsText.setCharacterSize(24);
        pointsText.setFillColor(sf::Color::White);
        pointsText.setFillColor(sf::Color::White);
        pointsText.setPosition(10, 10);
        couldLoadFont = true;
    }
    else
    {
        couldLoadFont = false;
    }

    lines = new sf::RectangleShape[4];
    fillLines();
}

void Ship::showShip(sf::RenderWindow &w)
{
    if(alive)
    {
        showDebug(ship.getGlobalBounds(), w);
        w.draw(ship);
    }
    else
    {
        for(int i = 0; i < lives; i++)
        {
            w.draw(lines[i]);
            lines[i].rotate(t * 250);
        }
    }

    if(couldLoadFont)
        w.draw(pointsText);
}

void Ship::keyPressed()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        w = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        a = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        d = true;
    }
}

void Ship::KeyReleased(sf::Event e)
{
    switch(e.key.code)
    {
        case sf::Keyboard::W:
            w = false;
            break;
        case sf::Keyboard::A:
            a = false;
            break;
        case sf::Keyboard::D:
            d = false;
            break;
        case sf::Keyboard::G:
            Movement::changeDebug();
        default:
            break;
    }
}

void Ship::rotate(float r)
{
    ship.rotate(r*ROTATESPEED);
}

void Ship::move(float t)
{
    this->t = t;

    if(w)
        addSpeed();
    else
        decreaseSpeed();

    if(a) 
        rotate(-(t*SPEED));
    else if(d) 
        rotate(t*SPEED);

    setSpeed();
}

void Ship::addSpeed()
{
    updateRotation(ship);
    speed.x += getSine() * t * SPEED;
    speed.y += -(getCosine() * t * SPEED);
}

void Ship::decreaseSpeed()
{
    if(speed.x > 0)
    {
        speed.x -= t*2;
        clampSpeed(0, 1000, 1);
    }
    else if(speed.x < 0)
    {
        speed.x += t*2;
        clampSpeed(-1000, 0, 1);
    }
    if(speed.y > 0)
    {
        speed.y -= t*2;
        clampSpeed(0, 1000, 2);
    }
    else if(speed.y < 0)
    {
        speed.y += t*2;
        clampSpeed(-1000, 0, 2);
    }
}

void Ship::setSpeed()
{
    clampSpeed(-MAXSPEED, MAXSPEED, 3);
    ship.move(speed);
    checkBounds(ship);
}

void Ship::getPosition(float &r, sf::Vector2f &p)
{
    r = ship.getRotation();
    p = ship.getPosition();
}

sf::FloatRect Ship::getBoundingBox()
{
    return ship.getGlobalBounds();
}

void Ship::checkAlive()
{
    if(!alive && lives != 0 && respawnCooldown < 0)
    {
        ship.setPosition(sf::Vector2f(WIN_WIDTH/2, WIN_HEIGTH/2));
        ship.setColor(sf::Color::Red);
        alive = true;
        invincible = true;
        invincibilityCooldown = INVINCIBILITY;
    }
    else if(invincible && invincibilityCooldown < 0)
    {
        ship.setColor(sf::Color::White);
        invincible = false;
    }
    respawnCooldown -= t;
    invincibilityCooldown -= t;
}

void Ship::setAlive()
{
    if(!invincible)
    {
        alive = false;
        lives--;
        respawnCooldown = DEATHCOOLDOWN;
        speed = sf::Vector2f(0,0);
        setLinePosition();
    }

}

bool Ship::getAlive()
{
    return alive;
}

void Ship::fillLines()
{
    int w = 5;
    int h = 25;

    for(int i = 0; i < 4; i++)
    {
        lines[i] = sf::RectangleShape(sf::Vector2f(w, h));
        lines[i].setOrigin(sf::Vector2f(w/2,h/2));
    }
}

void Ship::setLinePosition()
{
    int d = 50;
    sf::Vector2f tmp = ship.getPosition();
    lines[0].setPosition(sf::Vector2f(tmp.x-d, tmp.y));
    lines[1].setPosition(sf::Vector2f(tmp.x+d, tmp.y));
    lines[2].setPosition(sf::Vector2f(tmp.x, tmp.y-d));
    lines[3].setPosition(sf::Vector2f(tmp.x, tmp.y+d));
}

void Ship::freeLines()
{
    if(lines != NULL)
    {
        delete[] lines;
        lines = NULL;
    }
}

void Ship::addPoints(int n)
{
    points += n;

    if(couldLoadFont)
        pointsText.setString(lives != 0 ? std::to_string(points) : ("You lost! Your final point: " + std::to_string(points)));
}