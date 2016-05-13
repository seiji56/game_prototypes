#include "entity.hpp"
#include "input.hpp"

#ifndef _PLAYER_SHIP_
#define _PLAYER_SHIP_

class PlayerShip : public Entity
{
public:
    PlayerShip(Input *_input, float _speed, sf::Sprite *_sprite) : input(_input), speed(_speed), Entity(_sprite){}
    void update(sf::Time dt);
private:
    Input *input;
    float speed;
};

#endif // _PLAYER_SHIP_
