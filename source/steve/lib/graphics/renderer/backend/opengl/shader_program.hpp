#pragma once

#include "shader.hpp"

#include <glm/mat4x4.hpp>

#include <steve/core/pch>

/* ------------------------------------------------------------------------------------------------------- */

namespace steve {
   class ShaderProgram {
   private:
      uint32_t m_ID;
      Shader   m_VertexShader;
      Shader   m_FragmentShader;

      ShaderProgram();

   public:
      ShaderProgram(const Shader &vertex_shader, const Shader &fragment_shader);

      uint32_t
      get_id() const;

      VoidResult
      allocate();

      VoidResult
      use();

      VoidResult
      set_uniform_mat4(const std::string &name, const glm::mat4 &matrix);

      static Result<ShaderProgram>
      from_source(const std::string &vertex_shader_source, const std::string &fragment_shader_source);

      static Result<ShaderProgram>
      from_files(const std::string &vertex_shader_path, const std::string &fragment_shader_path);
   };
}

/* ------------------------------------------------------------------------------------------------------- */
