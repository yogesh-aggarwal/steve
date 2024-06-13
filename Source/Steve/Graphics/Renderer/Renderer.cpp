#include "Renderer.hpp"

#include <iostream>

#include <glm/ext.hpp>

#include <Steve/Core/Shaders.hpp>
#include <Steve/Core/Helpers.hpp>
#include <Steve/Application/ApplicationWindow.hpp>

Ref<Renderer::State> s_RendererState = nullptr;

bool
Renderer::HasInitialized()
{
   return false;
}

Result<bool>
Renderer::Initialize()
{
   auto _ = Result<bool> { false };

   auto shaderProgram =
       ShaderProgram::FromSource(STEVE_SHADER_SOURCE_VERTEX,
                                 STEVE_SHADER_SOURCE_FRAGMENT)
           .WithErrorHandler([](Ref<Error> error) {
              error->Push({ STEVE_RENDERER_STATE_INITIALIZATION_FAILED,
                            "Failed to intialize renderer state." });
           });
   if (!shaderProgram) return { false, shaderProgram.error };

   _ = shaderProgram.value.Allocate().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_RENDERER_STATE_INITIALIZATION_FAILED,
                    "Failed to intialize renderer state." });
   });
   if (!_) return { false, _.error };

   VertexArray vao {};
   _ = vao.AllocateAndBind().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_RENDERER_STATE_INITIALIZATION_FAILED,
                    "Failed to intialize renderer state." });
   });
   if (!_) return { false, _.error };

   VertexBuffer vbo {};
   _ = vbo.BindAndAllocate().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_RENDERER_STATE_INITIALIZATION_FAILED,
                    "Failed to intialize renderer state." });
   });
   if (!_) return { false, _.error };

   IndexBuffer ibo {};
   _ = ibo.BindAndPopulate().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_RENDERER_STATE_INITIALIZATION_FAILED,
                    "Failed to intialize renderer state." });
   });
   if (!_) return { false, _.error };

   VertexBufferLayout positionLayout(0, 3, 0);
   _ = positionLayout.Apply().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_RENDERER_STATE_INITIALIZATION_FAILED,
                    "Failed to intialize renderer state." });
   });
   if (!_) return { false, _.error };

   VertexBufferLayout colorLayout(1, 4, 3);
   _ = colorLayout.Apply().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_RENDERER_STATE_INITIALIZATION_FAILED,
                    "Failed to intialize renderer state." });
   });
   if (!_) return { false, _.error };

   State m_State = {
      .hasInitialized = true,
      .hasBegunScene  = false,
      .vertices       = std::vector<Vertex>(MAX_VERTICES),

      .clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),   // black

      .vertexArray   = vao,
      .vertexBuffer  = vbo,
      .indexBuffer   = ibo,
      .shaderProgram = shaderProgram.value,
   };
   s_RendererState = CreateRef<State>(m_State);

   return true;
}

Result<bool>
Renderer::BeginScene()
{
   if (!s_RendererState->hasInitialized)
   {
      return { false,
               new Error({ STEVE_RENDERER_NOT_INITIALIZED,
                           "Renderer not initialized" }) };
   }
   if (s_RendererState->hasBegunScene)
   {
      return { false,
               new Error({ STEVE_RENDERER_SCENE_ALREADY_BEGUN,
                           "Renderer scene already begun" }) };
   }

   s_RendererState->hasBegunScene = true;
   s_RendererState->vertices.clear();

   auto _ = s_RendererState->shaderProgram.Use();

   return true;
}

Result<bool>
Renderer::EndScene()
{
   if (!s_RendererState->hasInitialized)
   {
      return { false,
               new Error({ STEVE_RENDERER_NOT_INITIALIZED,
                           "Renderer not initialized" }) };
   }
   if (!s_RendererState->hasBegunScene)
   {
      return { false,
               new Error({ STEVE_RENDERER_SCENE_HAS_NOT_BEGUN,
                           "Renderer scene has not begun" }) };
   }
   if (s_RendererState->vertices.empty()) { return true; }

   auto _ = Result<bool> { false };

   glClearColor(s_RendererState->clearColor.r,
                s_RendererState->clearColor.g,
                s_RendererState->clearColor.b,
                s_RendererState->clearColor.a);
   glClear(GL_COLOR_BUFFER_BIT);

   glm::mat4 projectionMat = glm::ortho(0.0f,
                                        (float)ApplicationWindow::GetWidth(),
                                        (float)ApplicationWindow::GetHeight(),
                                        0.0f,
                                        -1.0f,
                                        1.0f);

   _ = s_RendererState->shaderProgram.SetUniformMat4("u_Projection",
                                                     projectionMat);
   if (!_) return { false, _.error };

   _ = s_RendererState->vertexBuffer.BindAndUploadData(
       s_RendererState->vertices);
   if (!_) return { false, _.error };

   _ = s_RendererState->shaderProgram.Use();
   if (!_) return { false, _.error };

   glDrawElements(GL_TRIANGLES, MAX_INDICES, GL_UNSIGNED_INT, nullptr);

   Flush();

   return true;
}

std::vector<Vertex>
Renderer::GetVertices()
{
   return s_RendererState->vertices;
}

glm::vec4
Renderer::GetClearColor()
{
   return s_RendererState->clearColor;
}

void
Renderer::SetClearColor(const glm::vec4 &color)
{
   s_RendererState->clearColor = color;
}

void
Renderer::Flush()
{
   s_RendererState->hasBegunScene = false;
   s_RendererState->vertices.clear();
}

void
Renderer::DrawVertices(const std::vector<Vertex> &vertices)
{
   auto newSize = s_RendererState->vertices.size() + vertices.size();
   if (newSize > MAX_VERTICES)
   {
      std::cerr << "Too many vertices" << std::endl;
      return;
   }

   s_RendererState->vertices.insert(s_RendererState->vertices.end(),
                                    vertices.begin(),
                                    vertices.end());
}

void
Renderer::PrintVertices()
{
   system("clear");

   const int shellColumns = 110;

   printf("%s\n", std::string(shellColumns, '-').c_str());
   printf("x\t\ty\t\tz\t\tr\t\tg\t\tb\t\ta\n");
   printf("%s\n", std::string(shellColumns, '-').c_str());

   for (const auto &vertex : s_RendererState->vertices)
   {
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
