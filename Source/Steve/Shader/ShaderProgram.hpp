#pragma once

#include <array>

#include <glm/mat4x4.hpp>

#include <Steve/Core/Result.tcc>

#include "Shader.hpp"

class ShaderProgram
{
private:
   uint32_t m_ID;
   Shader   m_VertexShader;
   Shader   m_FragmentShader;

   ShaderProgram();

public:
   ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader);

   uint32_t
   GetID() const;

   Result<bool>
   Allocate();

   Result<bool>
   Use();

   Result<bool>
   SetUniformMat4(const std::string &name, const glm::mat4 &matrix);

   static Result<ShaderProgram>
   FromFiles(std::string vertexPath, std::string fragmentPath);
};
