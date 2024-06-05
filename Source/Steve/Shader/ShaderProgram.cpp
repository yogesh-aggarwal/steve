#include "ShaderProgram.hpp"

#include <glad/glad.h>

ShaderProgram::ShaderProgram() : m_VertexShader({}), m_FragmentShader({}) {}

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

   int  success;
   char infoLog[512];
   glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
   if (!success)
   {
      glGetProgramInfoLog(m_ID, 512, nullptr, infoLog);

      std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n"
                << infoLog << std::endl;

      return { false,
               new Error({ STEVE_SHADER_PROGRAM_INITIALIZE_FAILED,
                           "Failed to initialize shader program." }) };
   }

   return true;
}

Result<bool>
ShaderProgram::Use()
{
   glUseProgram(m_ID);
   return true;
}

Result<ShaderProgram>
ShaderProgram::FromFiles(std::string vertexPath, std::string fragmentPath)
{
   Result<bool> res { false };

   /* Vertex shader */
   auto vertexShader =
       Shader::FromFile(Shader::Type::Vertex, vertexPath)
           .WithErrorHandler([](Ref<Error> error) {
              error->Push(
                  { STEVE_SHADER_PROGRAM_INITIALIZE_FAILED,
                    "Failed to initialize shader program from shader files." });
           });
   if (!vertexShader) return { {}, vertexShader.error };
   res = vertexShader.value.Allocate().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_SHADER_PROGRAM_INITIALIZE_FAILED,
                    "Failed to initialize shader program from shader files." });
   });
   if (!res) return { {}, res.error };

   /* Fragment shader */
   auto fragmentShader =
       Shader::FromFile(Shader::Type::Fragment, fragmentPath)
           .WithErrorHandler([](Ref<Error> error) {
              error->Push(
                  { STEVE_SHADER_PROGRAM_INITIALIZE_FAILED,
                    "Failed to initialize shader program from shader files." });
           });
   if (!res) return { {}, res.error };
   res = fragmentShader.value.Allocate().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_SHADER_PROGRAM_INITIALIZE_FAILED,
                    "Failed to initialize shader program from shader files." });
   });
   if (!res) return { {}, fragmentShader.error };

   return { { vertexShader.value, fragmentShader.value } };
}
