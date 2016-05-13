#include "include.hpp"

#ifndef _ASSETS_MAN_
#define _ASSETS_MAN_

class AssetsManager
{
public:
    AssetsManager();

    sf::Texture* loadTexture(std::string path, std::string name);
    sf::Texture* getTexture(std::string name);
    void unloadTexture(std::string name);

    sf::Sprite* createSprite(std::string texture, std::string name);
    void deleteSprite(std::string name);

private:
    std::map<std::string, sf::Texture*> textures;
    std::map<std::string, sf::Sprite*> sprites;
};
#endif // _ASSETS_MAN_
