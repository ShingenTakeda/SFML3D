#pragma once
#include <map>

#include <GL/glew.h>


class GLSLShader
{
    public:
        GLSLShader(void);
        ~GLSLShader(void);
        void LoadFromString(GLenum whichShader, const std::string& pathToSource);
        void LoadFromFile(GLenum whichShader, const std::string& filename);
        void CreateAndLinkProgram();
        void Use();
        void StopUsing();
        void AddAttribute(const std::string& attribute);
        void AddUniform(const std::string& uniform);

        GLuint operator[] (const std::string& attribute);
        GLuint operator() (const std::string& uniform);

        void DeleteShaderProgram();

    private:
        enum ShaderType{VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER};
        GLuint m_program;
        int m_totalShaders;
        GLuint m_shaders[3];
        std::map<std::string, GLuint> m_attributeList;
        std::map<std::string, GLuint> m_uniformLocationList;
};