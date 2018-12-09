#include "include/Engine.hpp"

Engine::Engine()
{
    //Getting the dimensions of the window
    const GLfloat WINDOW_WIDTH = 800.0f;
    const GLfloat WINDOW_HEIGHT = 600.0f;

    m_Settings.depthBits = 24;
    m_Settings.stencilBits = 8;

    m_Window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "3d Engine",sf::Style::Titlebar | sf::Style::Close, m_Settings);
}

void Engine::run()
{
    //Timing
    Clock clock;

    while(m_Window.isOpen())
    {
        Time dt = clock.restart();

        //Game time total
        m_GameTimeTotal += dt;

        float dtAsSeconds = dt.asSeconds();

        //input();
        //update(dtAsSeconds);
        //draw();
    }
}