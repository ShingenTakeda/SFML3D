#include <iostream>

#include "GLSLShader.hpp"

//YODO:Remember to program exeptions to the files

GLSLShader::GLSLShader(void)
{
    m_totalShaders             = 0;
    m_shaders[VERTEX_SHADER]   = 0;
    m_shaders[FRAGMENT_SHADER] = 0;
    m_shaders[GEOMETRY_SHADER] = 0;

    m_attributeList.clear();
    m_uniformLocationList.clear();
}

GLSLShader::~GLSLShader(void)
{
    m_attributeList.clear();
    m_uniformLocationList.clear();
}

void GLSLShader::DeleteShaderProgram()
{
    glDeleteProgram(m_program);
}

void GLSLShader::LoadFromString(GLenum shaderType, const std::string& pathToSource)
{
    GLuint shader = glCreateShader(shaderType);

    const char* ptmp = pathToSource.c_str();
    glShaderSource(shader, 1, &ptmp, NULL);

    //Check whetever the shader loaded or not
    GLint status;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
        std::cerr<<"Compile Log: "<<infoLog<<std::endl;

        delete [] infoLog;
    }

    m_shaders[m_totalShaders++] = shader;
}

void GLSLShader::CreateAndLinkProgram()
{
    m_program = glCreateProgram();

    if(m_shaders[VERTEX_SHADER] != 0)
    {
        glAttachShader(m_program, m_shaders[VERTEX_SHADER]);
    }

    if(m_shaders[FRAGMENT_SHADER] != 0)
    {
        glAttachShader(m_program, m_shaders[FRAGMENT_SHADER]);
    }

    if(m_shaders[GEOMETRY_SHADER] != 0)
    {
        glAttachShader(m_program, m_shaders[GEOMETRY_SHADER]);
    }

    //Link and check if the program links fine
    GLint status;
    glLinkProgram(m_program);
    glGetProgramiv(m_program, GL_LINK_STATUS, &status);

    if(status == GL_FALSE)
    {
        GLint infoLogLength;

        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength];
        glGetProgramInfoLog(m_program, infoLogLength, NULL, infoLog);
        std::cerr<<"Link Log: "<<infoLog<<std::endl;

        delete[] infoLog;
    }

    glDeleteShader(m_shaders[VERTEX_SHADER]);
    glDeleteShader(m_shaders[FRAGMENT_SHADER]);
    glDeleteShader(m_shaders[GEOMETRY_SHADER]);
}

void GLSLShader::Use()
{
    glUseProgram(m_program);
}

void GLSLShader::StopUsing()
{
    glUseProgram(0);
}

void GLSLShader::AddAttribute(const std::string& attribute)
{
    m_attributeList[attribute] = glGetAttribLocation(m_program, attribute.c_str());
}

GLuint GLSLShader::operator[](const std::string& attribute)
{
    return m_attributeList[attribute];
}

void GLSLShader::AddUniform(const std::string& uniform)
{
    m_uniformLocationList[uniform] = glGetUniformLocation(m_program, uniform.c_str());
}

GLuint GLSLShader::operator()(const std::string& uniform)
{
    return m_uniformLocationList[uniform];
}

#include <fstream>
void GLSLShader::LoadFromFile(GLenum whichShader, const std::string& filename)
{
    std::ifstream fp;
    fp.open(filename.c_str(), std::ios_base::in);

    if(fp)
    {
        std::string line, buffer;
        while(getline(fp, line))
        {
            buffer.append(line);
            buffer.append("\r\n");
        }

        //Copy to source
        LoadFromString(whichShader, buffer);
    }
    else
    {
        std::cerr<<"Error loading shader: "<<filename<<std::endl;
    }
}