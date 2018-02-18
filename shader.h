//
// Created by calle on 15/02/2018.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderProgram
{
public:
    unsigned int id;

    ShaderProgram(const char* vertexShaderSourceCodeFilePath, const char* fragmentShaderSourceCodeFilePath)
    {
        std::string vertexShaderSourceCode;
        std::string fragmentShaderSourceCode;
        std::ifstream vertexShaderSourceCodeFile;
        std::ifstream fragmentShaderSourceCodeFile;

        vertexShaderSourceCodeFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragmentShaderSourceCodeFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            vertexShaderSourceCodeFile.open(vertexShaderSourceCodeFilePath);
            fragmentShaderSourceCodeFile.open(fragmentShaderSourceCodeFilePath);

            std::stringstream vertexShaderSourceCodeStream, fragmentShaderSourceCodeStream;

            vertexShaderSourceCodeStream << vertexShaderSourceCodeFile.rdbuf();
            fragmentShaderSourceCodeStream << fragmentShaderSourceCodeFile.rdbuf();

            vertexShaderSourceCodeFile.close();
            fragmentShaderSourceCodeFile.close();

            vertexShaderSourceCode = vertexShaderSourceCodeStream.str();
            fragmentShaderSourceCode = fragmentShaderSourceCodeStream.str();
        }
        catch(std::ifstream::failure e)
        {
            std::cout << "Error: Failed to load shader source" << std::endl;
        }


        unsigned int vertexShaderId, fragmentShaderId;
        int success;
        char infoLog[512];
        const char* vertexShaderSourceCodeCString = vertexShaderSourceCode.c_str();
        const char* fragmentShaderSourceCodeCString = fragmentShaderSourceCode.c_str();

        vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShaderId, 1, &vertexShaderSourceCodeCString, NULL);
        glCompileShader(vertexShaderId);

        glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
            std::cout << "Error: Failed to compile vertex shader -> " << infoLog << std::endl;
        }


        fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderId, 1, &fragmentShaderSourceCodeCString, NULL);
        glCompileShader(fragmentShaderId);

        glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
            std::cout << "Error: Failed to compile fragment shader -> " << infoLog << std::endl;
        }



        id = glCreateProgram();
        glAttachShader(id, vertexShaderId);
        glAttachShader(id, fragmentShaderId);
        glLinkProgram(id);

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cout << "Error: Failed to link shader program -> " << infoLog << std::endl;
        }

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
    }

    void use()
    {
        glUseProgram(id);
    }

    //Set uniforms
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }
    void setVector4f(const std::string &name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
    }
};

#endif //OPENGL_SHADER_H
