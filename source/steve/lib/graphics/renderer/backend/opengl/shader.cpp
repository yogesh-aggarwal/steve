#include "shader.hpp"

#include <string>
#include <fstream>
#include <glad/glad.h>

#include <steve/core/pch>

/* ------------------------------------------------------------------------------------------------------- */

using namespace steve;

/* ------------------------------------------------------------------------------------------------------- */

Shader::Shader(Type type) : m_Type(type) {}

/* ------------------------------------------------------------------------------------------------------- */

Shader
Shader::from_source(Type type, std::string source) {
   Shader shader(type);
   shader.m_Source = source;

   return shader;
}

/* ------------------------------------------------------------------------------------------------------- */

Result<Shader>
Shader::from_file(Type type, std::string path) {
   // auto res = Utility::ReadFile(path).WithErrorHandler([&](Ref<Error> error) {
   //    error->Push(
   //        { STEVE_SHADER_INTIALIZE_FROM_FILE_FAILED, "Failed to initialize shader from file: " + path });
   // });
   // if (!res)
   //    return { Shader(type), res.error };

   /// TODO:
   auto shader = Shader::from_source(type, "");
   return shader;
}

/* ------------------------------------------------------------------------------------------------------- */

uint32_t
Shader::get_id() const {
   return m_ID;
}

/* ------------------------------------------------------------------------------------------------------- */

std::string
Shader::get_source() const {
   return m_Source;
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
Shader::allocate() {
   int shader_type = -1;
   switch (m_Type) {
   case Vertex: shader_type = GL_VERTEX_SHADER; break;
   case Fragment: shader_type = GL_FRAGMENT_SHADER; break;
   default: {
      return Error("Invalid shader type provided: " + std::to_string(m_Type));
   }
   }

   m_ID = glCreateShader(shader_type);

   auto shaderSource = m_Source.c_str();
   glShaderSource(m_ID, 1, &shaderSource, nullptr);
   glCompileShader(m_ID);

   int success;
   glGetShaderiv(m_ID, GL_COMPILE_STATUS, &success);
   if (!success) {
      char info_log[512];
      glGetShaderInfoLog(m_ID, 512, NULL, info_log);

      return Error(info_log);
   }

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */
