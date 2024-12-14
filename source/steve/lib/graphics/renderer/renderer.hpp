#pragma once

#include "backend/backend.hpp"

#include <steve/core/pch>

/* ------------------------------------------------------------------------------------------------------- */

namespace steve::renderer {
   struct State {
      bool                has_initialized;
      bool                has_begun_scene;
      std::vector<Vertex> vertices;

      glm::vec4 clear_color;

      VertexArray   vertex_array;
      VertexBuffer  vertex_buffer;
      IndexBuffer   index_buffer;
      ShaderProgram shader_program;
   };

   inline bool
   has_initialized();

   VoidResult
   initialize();

   VoidResult
   begin_scene();

   VoidResult
   end_scene();

   std::vector<Vertex>
   get_vertices();

   glm::vec4
   get_clear_color();

   void
   set_clear_color(const glm::vec4 &color);

   void
   flush();

   VoidResult
   draw_vertices(const std::vector<Vertex> &vertices);

   void
   print_vertices();
};

/* ------------------------------------------------------------------------------------------------------- */
