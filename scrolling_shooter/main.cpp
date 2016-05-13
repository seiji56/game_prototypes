#include "input.hpp"
#include "assets_manager.hpp"
#include "player_ship.hpp"

float difficulty = 10;

AssetsManager assets;

PlayerShip *p_ship;

void render_t(sf::RenderWindow *window)
{
    while(window->isOpen())
    {
        window->clear();
        //Draw Here
        if(p_ship)p_ship->draw(window);
        //
        window->display();
    }
}

void handleEvn(sf::Event &evn, sf::RenderWindow* window)
{
    switch(evn.type)
    {
    case sf::Event::Closed:
        window->close();
        break;
    case sf::Event::KeyPressed:
        In.keys[evn.key.code] = true;
        break;
    case sf::Event::KeyReleased:
        In.keys[evn.key.code] = false;
        break;
    case sf::Event::MouseButtonPressed:
        In.mouse[evn.mouseButton.button] = true;
        break;
    case sf::Event::MouseButtonReleased:
        In.mouse[evn.mouseButton.button] = false;
        break;
    default:
        break;
    }
}

void proc_t(sf::RenderWindow* window)
{
    sf::Clock clock;
    while(window->isOpen())
    {
        sf::Time time = clock.restart();
        //Code
        //
    }
}

int main()
{
#ifdef __linux__//Call XInitThreads in case of linux compilation
    XInitThreads();
#endif // __linux__
    sf::RenderWindow window(sf::VideoMode(800, 600), "scrolling_shooter");

    srand(time(0));
    //Start Threads

    sf::Thread rendering_thread(&render_t, &window);
    sf::Thread processing_thread(&proc_t, &window);

    rendering_thread.launch();
    processing_thread.launch();


    //Event loop

    while(window.isOpen())
    {
        sf::Event evn;
        while(window.pollEvent(evn))
        {
            handleEvn(evn, &window);
        }
    }

    rendering_thread.wait();
    processing_thread.wait();
}
