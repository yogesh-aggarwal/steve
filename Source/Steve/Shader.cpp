#include "Shader.hpp"

#include <string>
#include <fstream>
#include <glad/glad.h>

#include <Steve/Core/Helpers.hpp>

Shader::Shader(Type type) : m_Type(type) {}

Shader
Shader::FromSource(Type type, std::string source)
{
   Shader shader(type);
   shader.m_Source = source;

   return shader;
}

Result<Shader>
Shader::FromFile(Type type, std::string path)
{
   auto res = ReadFile(path).WithErrorHandler([&](Ref<Error> error) {
      error->Push({ STEVE_SHADER_INTIALIZE_FROM_FILE_FAILED,
                    "Failed to initialize shader from file: " + path });
   });
   if (!res) return { Shader(type), res.error };

   auto shader = Shader::FromSource(type, res.value);
   return shader;
}

uint32_t
Shader::GetID() const
{
   return m_ID;
}

std::string
Shader::GetSource() const
{
   return m_Source;
}

Result<bool>
Shader::Allocate()
{
   int shaderType = -1;
   switch (m_Type)
   {
   case Vertex: shaderType = GL_VERTEX_SHADER; break;
   case Fragment: shaderType = GL_FRAGMENT_SHADER; break;
   default: {
      return { false,
               new Error({ STEVE_INVALID_SHADER_TYPE,
                           "Invalid shader type provided: " +
                               std::to_string(m_Type) }) };
   }
   }

   m_ID = glCreateShader(shaderType);

   auto shaderSource = m_Source.c_str();
   glShaderSource(m_ID, 1, &shaderSource, nullptr);
   glCompileShader(m_ID);

   int success;
   glGetShaderiv(m_ID, GL_COMPILE_STATUS, &success);
   if (!success)
   {
      char infoLog[512];
      glGetShaderInfoLog(m_ID, 512, NULL, infoLog);
      return { false, new Error({ STEVE_SHADER_COMPILE_FAILED, infoLog }) };
   }

   return true;
}

Result<std::string>
Shader::ReadFile(const std::string &path)
{
   try
   {
      std::ifstream file(path);
      if (!file.is_open())
         return { "",
                  new Error({ FILE_IO, "Unable to open the file: " + path }) };

      std::string content;
      std::string line;
      while (std::getline(file, line))
         content += line + "\n";

      return { content };
   }
   catch (const std::exception &e)
   {
      return { "",
               new Error({ FILE_IO,
                           "Failed to read the file: " + path + " (" +
                               e.what() + ")" }) };
   }
}
