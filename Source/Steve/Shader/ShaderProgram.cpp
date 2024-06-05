#include "ShaderProgram.hpp"

#include <glad/glad.h>

ShaderProgram::ShaderProgram(const Shader &vertexShader,
                             const Shader &fragmentShader)
    : m_VertexShader(vertexShader), m_FragmentShader(fragmentShader)
{
}

uint32_t
ShaderProgram::GetID() const
{
   return m_ID;
}

Result<bool>
ShaderProgram::Allocate()
{
   m_ID = glCreateProgram();
   glAttachShader(m_ID, m_VertexShader.GetID());
   glAttachShader(m_ID, m_FragmentShader.GetID());
   glLinkProgram(m_ID);

   return true;
}
