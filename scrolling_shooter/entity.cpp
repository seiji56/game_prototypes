#include "entity.hpp"

Entity::Entity(sf::Sprite* _sprite)
{
    sprite = _sprite;
    pos = sf::Vector2f(0, 0);
    vel = sf::Vector2f(0, 0);
    acc = sf::Vector2f(0, 0);
}

Entity::Entity(sf::Vector2f _pos, sf::Sprite* _sprite)
{
    sprite = _sprite;
    pos = _pos;
    vel = sf::Vector2f(0, 0);
    acc = sf::Vector2f(0, 0);
}

Entity::~Entity()
{
}

void Entity::e_update(sf::Time dt)
{
    pos += vel*dt.asSeconds() + acc*((dt.asSeconds()*dt.asSeconds())/2);
    vel += acc*dt.asSeconds();
}

void Entity::draw(sf::RenderTarget* canvas)
{
    canvas->draw(*sprite);
}

bool Entity::collides(Entity* entity)
{
    sf::Vector2f deltapos = pos - entity->getPos();
    return sqrt((deltapos.x*deltapos.x) + (deltapos.y*deltapos.y)) < (entity->getRadius() + radius);
}

//Setters

void Entity::setPos(sf::Vector2f _pos)
{
    pos = _pos;
}

void Entity::setVel(sf::Vector2f _vel)
{
    vel = _vel;
}

void Entity::setAcc(sf::Vector2f _acc)
{
    acc = _acc;
}

void Entity::setRadius(float _radius)
{
    radius = _radius;
}

void Entity::setFacing(float _facing)
{
    facing = _facing;
}

void Entity::setSprite(sf::Sprite* _sprite)
{
    sprite = _sprite;
}

//Getters

sf::Vector2f Entity::getPos()
{
    return pos;
}

sf::Vector2f Entity::getVel()
{
    return vel;
}

sf::Vector2f Entity::getAcc()
{
    return vel;
}

float Entity::getRadius()
{
    return radius;
}

float Entity::getFacing()
{
    return facing;
}

sf::Sprite* Entity::getSprite()
{
    return sprite;
}
