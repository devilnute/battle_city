#include "ShaderProgram.h"

#include <iostream>

namespace Renderer
{
    ShaderProgram::ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader)
    {
        GLuint vetrexShaderID;
        if (!createShader(vertexShader, GL_VERTEX_SHADER, vetrexShaderID))
        {
            std::cerr << "VERTEX SHADER compile-time-error" << std::endl;
            return;
        }

        GLuint fragmentShaderID;
        if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
        {
            std::cerr << "FRAGMENT SHADER compile-time-error" << std::endl;
            glDeleteShader(vetrexShaderID);
            return;
        }

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vetrexShaderID);
        glAttachShader(m_ID, fragmentShaderID);
        glLinkProgram(m_ID);

        GLint success;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glad_glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: LINK-time-error:\n"
                      << infoLog << std::endl;
        }
        else
        {
            m_isCompiled = true;
        }

        glDeleteShader(vetrexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_ID);
    }

    void ShaderProgram::use() const
    {
        glUseProgram(m_ID);
    }

    bool ShaderProgram::createShader(const std::string &source, const GLenum shaderType, GLuint &shaderID)
    {
        shaderID = glCreateShader(shaderType);
        const char *code = source.c_str();
        glShaderSource(shaderID, 1, &code, nullptr);
        glCompileShader(shaderID);
        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glad_glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Compile-time-error:\n"
                      << infoLog << std::endl;
            return false;
        }
        return true;
    }

    ShaderProgram &ShaderProgram::operator=(ShaderProgram &&shaderProgram) noexcept
    {
        glDeleteProgram(m_ID);
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = 0;
        return *this;
    }

    ShaderProgram::ShaderProgram(ShaderProgram &&shaderProgram) noexcept
    {
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = 0;
    }
}
