#include "player_ship.hpp"

void PlayerShip::update(sf::Time dt)
{
    if(input->keys[sf::Keyboard::W] || input->keys[sf::Keyboard::Up])     vel.y = -speed;
    if(input->keys[sf::Keyboard::S] || input->keys[sf::Keyboard::Down])   vel.y = speed;
    if(input->keys[sf::Keyboard::A] || input->keys[sf::Keyboard::Right])  vel.x = -speed;
    if(input->keys[sf::Keyboard::D] || input->keys[sf::Keyboard::Left])   vel.x = speed;

    e_update(dt);
}
