#include "renderer.hpp"

#include <glm/ext.hpp>

#include <steve/lib/graphics/shaders.hpp>
#include <steve/lib/application/window.hpp>

using namespace steve;

/* ------------------------------------------------------------------------------------------------------- */

Ref<steve::renderer::State> s_RendererState = nullptr;

/* ------------------------------------------------------------------------------------------------------- */

bool
steve::renderer::has_initialized() {
   return false;
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
steve::renderer::initialize() {
   auto _ = Ok();

   // Initialize shaders
   auto shader_program = ShaderProgram::from_source(STEVE_SHADER_SOURCE_VERTEX, STEVE_SHADER_SOURCE_FRAGMENT)
                             .except("Failed to initialize shader program from sources.");
   RETURN_IF_ERROR(shader_program);
   _ = shader_program.get_value().allocate().except("Failed to allocate shader program.");
   RETURN_IF_ERROR(_);

   // Initialize vertex array
   VertexArray vao {};
   _ = vao.allocate_and_bind().except("Failed to intialize renderer state.");
   RETURN_IF_ERROR(_);

   // Initialize vertex buffer
   VertexBuffer vbo {};
   _ = vbo.bind_and_allocate().except("Failed to intialize renderer state.");
   RETURN_IF_ERROR(_);

   // Initialize index buffer
   IndexBuffer ibo {};
   _ = ibo.bind_and_populate().except("Failed to intialize renderer state.");
   RETURN_IF_ERROR(_);

   // Initialize vertex buffer layout
   VertexBufferLayout positionLayout(0, 3, 0);
   _ = positionLayout.apply().except("Failed to intialize renderer state.");
   RETURN_IF_ERROR(_);

   // Initialize color buffer layout
   VertexBufferLayout colorLayout(1, 4, 3);
   _ = colorLayout.apply().except("Failed to intialize renderer state.");
   RETURN_IF_ERROR(_);

   // Initialize renderer state
   State m_State = {
      .has_initialized = true,
      .has_begun_scene = false,
      .vertices        = std::vector<Vertex>(MAX_VERTICES),

      .clear_color = glm::vec4(0.12f, 0.12f, 0.12f, 0.12f),   // black

      .vertex_array   = vao,
      .vertex_buffer  = vbo,
      .index_buffer   = ibo,
      .shader_program = shader_program.get_value(),
   };
   s_RendererState = CreateRef<State>(m_State);

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
steve::renderer::begin_scene() {
   if (!s_RendererState->has_initialized) {
      return Error("Renderer not initialized");
   }
   if (s_RendererState->has_begun_scene) {
      return Error("Renderer scene already begun");
   }

   s_RendererState->has_begun_scene = true;
   s_RendererState->vertices.clear();

   auto _ = s_RendererState->shader_program.use();

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
steve::renderer::end_scene() {
   if (!s_RendererState->has_initialized) {
      return Error("Renderer not initialized");
   }
   if (!s_RendererState->has_begun_scene) {
      return Error("Renderer scene has not begun");
   }
   if (s_RendererState->vertices.empty()) {
      return Ok();
   }

   glClearColor(s_RendererState->clear_color.r,
                s_RendererState->clear_color.g,
                s_RendererState->clear_color.b,
                s_RendererState->clear_color.a);
   glClear(GL_COLOR_BUFFER_BIT);

   glm::mat4 projectionMat = glm::ortho(0.0f,
                                        (float)application::Window::get_width(),
                                        (float)application::Window::get_height(),
                                        0.0f,
                                        -1.0f,
                                        1.0f);

   auto res = Ok();

   // Set uniform
   res = s_RendererState->shader_program.set_uniform_mat4("u_Projection", projectionMat);
   RETURN_IF_ERROR(res);

   // Bind vertex array and buffers
   res = s_RendererState->vertex_buffer.bind_and_upload_data(s_RendererState->vertices);
   RETURN_IF_ERROR(res);

   // Bind shader program
   res = s_RendererState->shader_program.use();
   RETURN_IF_ERROR(res);

   glDrawElements(GL_TRIANGLES, MAX_INDICES, GL_UNSIGNED_INT, nullptr);

   flush();

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

std::vector<Vertex>
steve::renderer::get_vertices() {
   return s_RendererState->vertices;
}

/* ------------------------------------------------------------------------------------------------------- */

glm::vec4
steve::renderer::get_clear_color() {
   return s_RendererState->clear_color;
}

/* ------------------------------------------------------------------------------------------------------- */

void
steve::renderer::set_clear_color(const glm::vec4 &color) {
   s_RendererState->clear_color = color;
}

/* ------------------------------------------------------------------------------------------------------- */

void
steve::renderer::flush() {
   s_RendererState->has_begun_scene = false;
   s_RendererState->vertices.clear();
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
steve::renderer::draw_vertices(const std::vector<Vertex> &vertices) {
   auto newSize = s_RendererState->vertices.size() + vertices.size();
   if (newSize > MAX_VERTICES) {
      return Error("Too many vertices");
   }

   s_RendererState->vertices.insert(s_RendererState->vertices.end(), vertices.begin(), vertices.end());

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

void
steve::renderer::print_vertices() {
   system("clear");

   const int shellColumns = 110;

   printf("%s\n", std::string(shellColumns, '-').c_str());
   printf("x\t\ty\t\tz\t\tr\t\tg\t\tb\t\ta\n");
   printf("%s\n", std::string(shellColumns, '-').c_str());

   for (const auto &vertex : s_RendererState->vertices) {
      printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\n",
             vertex.position.x,
             vertex.position.y,
             vertex.position.z,
             vertex.color.r,
             vertex.color.g,
             vertex.color.b,
             vertex.color.a);
   }
   printf("%s\n", std::string(shellColumns, '-').c_str());
}

/* ------------------------------------------------------------------------------------------------------- */
