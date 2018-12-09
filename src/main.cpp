#include <iostream>

#include <GL/glew.h>
#include <SFML/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "dependencies/SOIL2/SOIL2.h"

#include "include/Shader.hpp"

const GLint WIDTH = 800, HEIGHT = 600;

//TODO: Manage to cast timeElapsed into a GLfloat

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

  //Opening the window
  sf::Window window(sf::VideoMode(WIDTH, HEIGHT, 32), "OpenGL Lessons", sf::Style::Titlebar | sf::Style::Close, settings);

  glewExperimental = GL_TRUE;

  if (GLEW_OK != glewInit()) 
  {
    std::cout << "Failed to initialize GLEW!" << std::endl;

    return EXIT_FAILURE;
  }

  bool running = true;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

 Shader ourShader("midia/shaders/core.vs", "midia/shaders/core.frag");

  //Texturing a rectangle
  GLfloat vertices[] =
  {
    //Position            //Color             //Texture Coordinates
    0.5f, 0.5f, 0.0f,     1.0f, 0.0f, 0.0f,    1.0f, 1.0f,         //Top right
    0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,         //Bottom right
    -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,         //Bottom left
    -0.5f, 0.5, 0.0f,     1.0f, 0.0f, 0.0f,    0.0f, 1.0f          //Top left
  };

  GLuint indices[] =
  {
    0, 1, 3,   //First triangle
    1, 2, 3    //Second triangle
  };

  //Making the buffers and the vertex array
  GLuint VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices)), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(indices)), indices, GL_STATIC_DRAW);

  //Creating the position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0);
  glEnableVertexAttribArray(0);

  //Create the color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  //Create a texture coordinate attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) (6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  
  GLuint texture;

  int width, height;
  glGenTextures(1, &texture),
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  unsigned char *image = SOIL_load_image("midia/images/image2.png", &width, &height, 0, SOIL_LOAD_RGBA);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);

  glBindVertexArray(0);

  while (running) 
  {
    sf::Event windowEvent;

    //TODO: Fix this warning
    while (window.pollEvent(windowEvent)) 
    {
      switch (windowEvent.type) 
      {
        case sf::Event::Closed:
          running = false;

          break;
      }
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.Use();

    glm::mat4 transform;
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, static_cast<GLfloat> (dtAsSeconds * -0.5f), glm::vec3(0.0f, 0.0f, 1.0f));

    GLint transformLocation = glGetUniformLocation(ourShader.Program, "transform");

    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(ourShader.Program, "Our Texture"), 0);

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    //Draw openGl

    window.display();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  window.close();

  return 0;
}
