#include "ShaderProgram.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

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
ShaderProgram::FromSource(const std::string &vertexSource,
                          const std::string &fragmentSource)
{
   Result<bool> res { false };

   /* Vertex shader */
   auto vertexShader = Shader::FromSource(Shader::Type::Vertex, vertexSource);
   res = vertexShader.Allocate().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_SHADER_PROGRAM_INITIALIZE_FAILED,
                    "Failed to initialize shader program from shader files." });
   });
   if (!res) return { {}, res.error };

   /* Fragment shader */
   auto fragmentShader =
       Shader::FromSource(Shader::Type::Fragment, fragmentSource);
   res = fragmentShader.Allocate().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_SHADER_PROGRAM_INITIALIZE_FAILED,
                    "Failed to initialize shader program from shader files." });
   });
   if (!res) return { {}, res.error };

   return { { vertexShader, fragmentShader } };
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

Result<bool>
ShaderProgram::SetUniformMat4(const std::string &name, const glm::mat4 &data)
{
   int location = glGetUniformLocation(m_ID, name.c_str());
   if (location == -1)
   {
      return { false,
               new Error({ STEVE_SHADER_PROGRAM_UNIFORM_NOT_FOUND,
                           "Failed to find uniform in shader program." }) };
   }

   glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
   return true;
}
