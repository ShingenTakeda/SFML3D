#include <iostream>

#include <GL/glew.h>
#include <SFML/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "include/GLSLShader.hpp"
#include "dependencies/SOIL2/SOIL2.h"

//TODO: make the window resizible by making the openGL viewport into a SFML viewport somehow.
//TODO: Fix core dump

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
  "midia/shaders/shader.vert");

  shader.LoadFromFile(GL_FRAGMENT_SHADER,
  "midia/shaders/shader.frag");

  //Compile and link the shaders
  shader.CreateAndLinkProgram();
  shader.Use();

  //Add attributes and uniforms
  shader.AddAttribute("vVertex");
  shader.AddAttribute("vColor");
  shader.AddUniform("MVP");

  shader.StopUsing();

  //Setup the triangle vertices and geometry
  vertices[0].color = glm::vec3(1, 0, 0);
  vertices[1].color = glm::vec3(0, 1, 0);
  vertices[2].color = glm::vec3(0, 0, 1);

  vertices[0].position = glm::vec3(-1, -1, 0);
  vertices[1].position = glm::vec3(0, 1, 0);
  vertices[2].position = glm::vec3(1, -1, 0);

  //Setup the triangle indices
  indices[0] = 0;
  indices[1] = 1;
  indices[2] = 2;

  //Setting up the vbo and vao for the triangle
  glGenVertexArrays(1, &vaoID);
  glGenBuffers(1, &vboVerticesID);
  glGenBuffers(1, &vboIndicesID);
  GLsizei stride = sizeof(Vertex);

  glBindVertexArray(vaoID);

    glBindBuffer (GL_ARRAY_BUFFER, vboVerticesID);

		//pass triangle vertices to buffer object
		glBufferData (GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

		//enable vertex attribute array for position
		glEnableVertexAttribArray(shader["vVertex"]);
		glVertexAttribPointer(shader["vVertex"], 3, GL_FLOAT, GL_FALSE,stride,0);

		//enable vertex attribute array for colour
		glEnableVertexAttribArray(shader["vColor"]);
		glVertexAttribPointer(shader["vColor"], 3, GL_FLOAT, GL_FALSE,stride, (const GLvoid*)offsetof(Vertex, color));
		
		//pass indices to element array buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

	std::cout<<"Initialization successfull"<<std::endl;
}

void OnRender()
{
  //Clear depth and color buffers
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  //Bind the shader
  shader.Use();

  //Pass the uniform shader
  glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV));

  //Draw the triangle
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

  //Unbind the shader
  shader.StopUsing();
}

void OnShutDown()
{
  //Destroy the shader
  shader.DeleteShaderProgram();

  //Delete the vao and vbo
  glDeleteBuffers(1, &vboVerticesID);
  glDeleteBuffers(1 , &vboIndicesID);
  glDeleteVertexArrays(1, &vaoID);
}

int main() 
{
  //Setting up a clock for updates
  sf::Clock clock;
  sf::Time timeElapsed;
  sf::Time dt = clock.restart();

  timeElapsed += dt;

  float dtAsSeconds = dt.asSeconds();

  //Context setting for using openGL on SFML
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
  //std::cout<<"\tVendor: "<<glGetString (GL_VENDOR)<<std::endl;
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
        OnShutDown();
        window.setActive(false);
      }
    }
    window.setActive(true);

    //Draw openGl
    OnInit();
    OnRender();

    //Maybe put this on the render function
    window.display();
  }

  return 0;
}
