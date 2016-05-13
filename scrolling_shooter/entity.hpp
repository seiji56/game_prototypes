#include "include.hpp"

#ifndef _ENTITY_
#define _ENTITY_

class Entity
{
public:
    Entity(sf::Sprite* _sprite);
    Entity(sf::Vector2f _pos, sf::Sprite* _sprite);
    ~Entity();

    virtual void update(sf::Time dt) = 0;//Should call e_update
    void draw(sf::RenderTarget *canvas);

    bool collides(Entity* entity);

    void setPos(sf::Vector2f _pos);
    void setVel(sf::Vector2f _vel);
    void setAcc(sf::Vector2f _acc);

    void setRadius(float _radius);
    void setFacing(float _facing);

    void setSprite(sf::Sprite* _sprite);

    sf::Vector2f getPos();
    sf::Vector2f getVel();
    sf::Vector2f getAcc();

    float getRadius();
    float getFacing();

    sf::Sprite* getSprite();
protected:
    void e_update(sf::Time dt);
    sf::Sprite* sprite;

    float radius;
    float facing;
    sf::Vector2f pos, vel, acc;
};

#endif // _ENTITY_
