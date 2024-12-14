#include "shader_program.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

/* ------------------------------------------------------------------------------------------------------- */

using namespace steve;

/* ------------------------------------------------------------------------------------------------------- */

ShaderProgram::ShaderProgram() : m_VertexShader({}), m_FragmentShader({}) {}

/* ------------------------------------------------------------------------------------------------------- */

ShaderProgram::ShaderProgram(const Shader &vertex_shader, const Shader &fragment_shader)
    : m_VertexShader(vertex_shader), m_FragmentShader(fragment_shader) {}

/* ------------------------------------------------------------------------------------------------------- */

uint32_t
ShaderProgram::get_id() const {
   return m_ID;
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
ShaderProgram::allocate() {
   m_ID = glCreateProgram();
   glAttachShader(m_ID, m_VertexShader.get_id());
   glAttachShader(m_ID, m_FragmentShader.get_id());
   glLinkProgram(m_ID);

   int  success;
   char infoLog[512];
   glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
   if (!success) {
      glGetProgramInfoLog(m_ID, 512, nullptr, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
      return Error("Failed to initialize shader program.");
   }

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
ShaderProgram::use() {
   glUseProgram(m_ID);
   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

Result<ShaderProgram>
ShaderProgram::from_source(const std::string &vertex_shader_source,
                           const std::string &fragment_shader_source) {
   VoidResult res = Ok();

   /* Vertex shader */
   auto vertex_shader = Shader::from_source(Shader::Type::Vertex, vertex_shader_source);
   res = vertex_shader.allocate().except("Failed to initialize vertex shader program from sources.");
   RETURN_IF_ERROR(res);

   /* Fragment shader */
   auto fragment_shader = Shader::from_source(Shader::Type::Fragment, fragment_shader_source);
   res = fragment_shader.allocate().except("Failed to initialize fragment shader program from sources.");
   RETURN_IF_ERROR(res);

   return ShaderProgram(vertex_shader, fragment_shader);
}

/* ------------------------------------------------------------------------------------------------------- */

Result<ShaderProgram>
ShaderProgram::from_files(const std::string &vertex_shader_path, const std::string &fragment_shader_path) {
   VoidResult res = Ok();

   /* Vertex shader */
   auto vertex_shader = Shader::from_file(Shader::Type::Vertex, vertex_shader_path)
                            .except("Failed to initialize vertex shader program from files.");
   RETURN_IF_ERROR(vertex_shader);
   res = vertex_shader.get_value()
             .allocate()   //
             .except("Failed to initialize vertex shader program from files.");
   RETURN_IF_ERROR(res);

   /* Fragment shader */
   auto fragment_shader = Shader::from_file(Shader::Type::Fragment, fragment_shader_path)
                              .except("Failed to initialize fragment shader program from files.");
   RETURN_IF_ERROR(fragment_shader);
   res = fragment_shader.get_value()
             .allocate()   //
             .except("Failed to initialize fragment shader program from files.");
   RETURN_IF_ERROR(res);

   return ShaderProgram(vertex_shader.get_value(), fragment_shader.get_value());
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
ShaderProgram::set_uniform_mat4(const std::string &name, const glm::mat4 &data) {
   int location = glGetUniformLocation(m_ID, name.c_str());
   if (location == -1) {
      return Error("Failed to find uniform in shader program.");
   }

   glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */
