#include <iostream>

#include <GL/glew.h>
#include <SFML/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "include/GLSLShader.hpp"
#include "dependencies/SOIL2/SOIL2.h"

const GLint WIDTH = 800, HEIGHT = 600;

GLSLShader shader;

//Vertex array and vertex buffer objects IDs
GLuint vaoID;
GLuint vboVerticesID;
GLuint vboIndicesID;

struct Vertex
{
  glm::vec3 position;
  glm::vec3 color;
};

//Triangle vertices and indices
Vertex vertices[3];
GLushort indices[3];

//Projection and modelview
glm::mat4 P = glm::mat4(1);
glm::mat4 MV = glm::mat4(1);

//TODO: Manage to cast timeElapsed into a GLfloat

void OnInit()
{
  //Load the shaders
  shader.LoadFromFile(GL_VERTEX_SHADER,
  "shader/shader.vert");

  shader.LoadFromFile(GL_FRAGMENT_SHADER,
  "shaders/shader.frag");

  //Compile and link the shaders
  shader.CreateAndLinkProgram();
  shader.Use();

  //Add attributes and uniforms
  shader.AddAttribute("vVertex");
  shader.AddAttribute("vColor");
  shader.AddUniform("MVP");

  shader.StopUsing();
}

void OnRender()
{
  //Clear depth and color buffers
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

int main() 
{
  //Setting up a clock for updates
  sf::Clock clock;
  sf::Time timeElapsed;
  sf::Time dt = clock.restart();

  timeElapsed += dt;

  float dtAsSeconds = dt.asSeconds();

  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;

  //Setting the openGL version
  settings.majorVersion = 3;
  settings.minorVersion = 3;

  settings.attributeFlags = sf::ContextSettings::Core;

  //GLEW A.K.A opengl stuff here
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  if(GLEW_OK != err)
  {
    std::cerr<<"Error"<<glewGetErrorString(err)<<std::endl;
  }
  else
  {
    if(GLEW_VERSION_3_3)
    {
      std::cout<<"Driver supports openGL 3.3\nDetails:"<<std::endl;
    }
  }

  std::cout<<"\tUsing glew "<<glewGetString(GLEW_VERSION)<<std::endl;
  std::cout<<"\tVendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"\tRenderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"\tVersion: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"\tGLSL: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Opening the window
  sf::Window window(sf::VideoMode(WIDTH, HEIGHT, 32), 
  "OpenGL Lessons", sf::Style::Titlebar | sf::Style::Close, settings);


  bool running = true;

  while (running) 
  {
    sf::Event windowEvent;

    while (window.pollEvent(windowEvent)) 
    {
      if(windowEvent.type == sf::Event::Closed)
      {
        window.close();
      }
    }
    window.setActive();

    //Draw openGl
    OnInit();
    OnRender();

    window.display();
  }

  return 0;
}
