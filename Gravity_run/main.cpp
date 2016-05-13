#include <SFML/Graphics.hpp>
#ifdef __linux__
#include <X11/Xlib.h>
#endif // __linux__
#include <stdio.h>
#include <time.h>

bool keyW = false;
bool keyS = false;
bool keyUP = false;
bool keyDOWN = false;

float gravity = 500;

float charactery = 60;
float charactervy = 0;

float velx = 50;

float difficulty = 10;

void render_t(sf::RenderWindow *window)
{
    while(window->isOpen())
    {
        window->clear();
        //Drawing code
        sf::RectangleShape up;
        up.setSize(sf::Vector2f(800, 50));
        up.setFillColor(sf::Color::White);
        up.setPosition(sf::Vector2f(0, 0));
        window->draw(up);
        sf::RectangleShape down;
        down.setSize(sf::Vector2f(800, 50));
        down.setFillColor(sf::Color::White);
        down.setPosition(sf::Vector2f(0, 350));
        window->draw(down);

        sf::CircleShape character(10);
        character.setOrigin(10, 10);
        character.setFillColor(sf::Color::Blue);
        character.setPosition(sf::Vector2f(30, charactery));
        window->draw(character);

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
        switch(evn.key.code)
        {
        case sf::Keyboard::Space:
            gravity *= -1;
            break;
        default:
            break;
        }
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
        charactervy += gravity*time.asSeconds();
        charactery += charactervy*time.asSeconds();

        if(charactery < 60){charactery = 60; charactervy = 0;}
        if(charactery > 340){charactery = 340; charactervy = 0;}

        velx *= 1 + difficulty*.01*time.asSeconds();
    }
}

int main()
{
#ifdef __linux__//Call XInitThreads in case of linux compilation
    XInitThreads();
#endif // __linux__
    sf::RenderWindow window(sf::VideoMode(800, 400), "Gravity run");

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
