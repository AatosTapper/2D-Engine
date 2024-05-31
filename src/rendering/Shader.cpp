#include "Shader.h"

#include "eng_util.h"

#include <iostream>
#include <fstream>

Shader::Shader(const std::string &vertex_path, const std::string &fragment_path) : m_freed(false)
{
    unsigned int vertex_shader = m_compile_shader(m_read_shader(vertex_path), GL_VERTEX_SHADER);
    unsigned int fragment_shader = m_compile_shader(m_read_shader(fragment_path), GL_FRAGMENT_SHADER);
    m_create_shader_program(vertex_shader, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
    if (!m_freed)
        glDeleteProgram(m_id);
}

void Shader::use() const
{
    glUseProgram(m_id);
}

void Shader::free()
{
    if (!m_freed)
    {
        glDeleteProgram(m_id);
        m_freed = true;
    }
}

int Shader::get_location(const std::string &name) const
{
    return glGetUniformLocation(m_id, name.c_str());
}

void Shader::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_uint(const std::string &name, unsigned int value) const
{
    glUniform1ui(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_2f(const std::string &name, float v1, float v2) const
{
    glUniform2f(glGetUniformLocation(m_id, name.c_str()), v1, v2);
}

void Shader::set_3f(const std::string &name, float v1, float v2, float v3) const
{
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), v1, v2, v3);
}

void Shader::set_4f(const std::string &name, float v1, float v2, float v3, float v4) const
{
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), v1, v2, v3, v4);
}

void Shader::set_vec3f(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::set_mat3f(const std::string &name, const glm::mat3 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_mat4f(const std::string &name, const glm::mat4 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

std::string Shader::m_read_shader(const std::string &filename) const
{
    std::string source;
    std::string line;
    std::ifstream file(filename);

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            source.append(line);
            source.push_back('\n'); // windows will freak out without this...
        }
        file.close();
    }
    else
    {
        ERR("Couldn't open shader " << filename);
    }

    return source;
}

unsigned int Shader::m_compile_shader(const std::string &source, GLenum type) const
{
    unsigned int shader;
    shader = glCreateShader(type);

    const char *c_source = source.c_str();
    glShaderSource(shader, 1, &c_source, NULL);

    glCompileShader(shader);

    // error checking
    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, info_log);

        switch (type)
        {
        case GL_VERTEX_SHADER:
            std::cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n" << info_log << std::endl;
            break;
        
        case GL_FRAGMENT_SHADER:
            std::cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n" << info_log << std::endl;
            break;

        default:
            break;
        }
        
        return 0;
    }

    return shader;
}

void Shader::m_create_shader_program(unsigned int vertex_shader, unsigned int fragment_shader)
{
    m_id = glCreateProgram();

    glAttachShader(m_id, vertex_shader);
    glAttachShader(m_id, fragment_shader);
    glLinkProgram(m_id);

    // error checking
    int success;
    char info_log[512];
    glGetProgramiv(m_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(m_id, 512, NULL, info_log);
        std::cout << "ERROR::PROGRAM_LINKING_FAILED\n" << info_log << std::endl;
    }
}