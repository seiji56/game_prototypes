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

float leftpady = 200;
float rightpady = 200;
float padvel = 200;

float ballx = 400;
float bally = 200;
float ballxv = 100;
float ballyv = 100;

float difficulty = 10;

void render_t(sf::RenderWindow *window)
{
    while(window->isOpen())
    {
        window->clear();
        //Drawing code
        sf::RectangleShape pad;
        pad.setSize(sf::Vector2f(10, 60));
        pad.setOrigin(5, 30);
        pad.setFillColor(sf::Color::White);
        pad.setPosition(sf::Vector2f(10, leftpady));
        window->draw(pad);
        pad.setPosition(sf::Vector2f(790, rightpady));
        window->draw(pad);

        sf::CircleShape ball(5);
        ball.setOrigin(5, 5);
        ball.setFillColor(sf::Color::White);
        ball.setPosition(sf::Vector2f(ballx, bally));
        window->draw(ball);

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
        case sf::Keyboard::W:
            keyW = true;
            break;
        case sf::Keyboard::S:
            keyS = true;
            break;
        case sf::Keyboard::Up:
            keyUP = true;
            break;
        case sf::Keyboard::Down:
            keyDOWN = true;
            break;
        default:
            break;
        }
        break;
    case sf::Event::KeyReleased:
        switch(evn.key.code)
        {
        case sf::Keyboard::W:
            keyW = false;
            break;
        case sf::Keyboard::S:
            keyS = false;
            break;
        case sf::Keyboard::Up:
            keyUP = false;
            break;
        case sf::Keyboard::Down:
            keyDOWN = false;
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
        if((ballx < 20 && ballx > 10) && (bally > leftpady - 30 && bally < leftpady + 30)){ballx = 20; ballxv = -ballxv;}
        if((ballx < 790 && ballx > 780) && (bally > rightpady - 30 && bally < rightpady + 30)){ballx = 780; ballxv = -ballxv;}
        if(bally < 5){bally = 5; ballyv = -ballyv;}
        if(bally > 395){bally = 395; ballyv = -ballyv;}
        sf::Time time = clock.restart();
        ballx += ballxv*time.asSeconds();
        bally += ballyv*time.asSeconds();

        ballxv *= 1 + difficulty*.01*time.asSeconds();;
        ballyv *= 1 + difficulty*.01*time.asSeconds();;

        if(keyW && leftpady > 30)leftpady -= padvel*time.asSeconds();
        if(keyS && leftpady < 400-30)leftpady += padvel*time.asSeconds();
        if(keyUP && rightpady > 30)rightpady -= padvel*time.asSeconds();
        if(keyDOWN && rightpady < 400-30)rightpady += padvel*time.asSeconds();
    }
}

int main()
{
#ifdef __linux__//Call XInitThreads in case of linux compilation
    XInitThreads();
#endif // __linux__
    sf::RenderWindow window(sf::VideoMode(800, 400), "Pong");

    srand(time(0));

    ballxv = (1/rand())*100 + 100;
    ballxv *= rand()%2?1:-1;
    ballyv = (1/rand())*100 + 100;
    ballyv *= rand()%2?1:-1;
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
