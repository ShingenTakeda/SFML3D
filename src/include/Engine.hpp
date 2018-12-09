#pragma once
#include <SFML/Window.hpp>
#include <GL/glew.h>

using namespace sf;

class Engine
{
    private:
        Window m_Window;

        ContextSettings m_Settings;

        Time m_GameTimeTotal;

        void update(float dtAsSeconds);
        void draw();
        void input();

    public:
        Engine();

        void run();
};