#include "Renderer.hpp"

#include <Steve/Core/Helpers.hpp>

Ref<Renderer::State> state = nullptr;

bool
Renderer::HasInitialized()
{
   return false;
}

Result<bool>
Renderer::Initialize()
{
   auto _ = Result<bool> { false };

   ShaderProgram shaderProgram =
       ShaderProgram::FromFiles("../Shaders/vertex.vs",
                                "../Shaders/fragment.fs")
           .value;
   _ = shaderProgram.Allocate();

   VertexArray vao {};
   _ = vao.AllocateAndBind();
   if (!_)
   {
      return { false,
               new Error({ STEVE_RENDERER_STATE_INITIALIZATION_FAILED,
                           "Failed to intialize renderer state." }) };
   }

   VertexBuffer vbo {};
   _ = vbo.BindAndAllocate();
   if (!_)
   {
      return { false,
               new Error({ STEVE_RENDERER_STATE_INITIALIZATION_FAILED,
                           "Failed to intialize renderer state." }) };
   }

   IndexBuffer ibo {};
   _ = ibo.BindAndPopulate();
   if (!_)
   {
      return { false,
               new Error({ STEVE_RENDERER_STATE_INITIALIZATION_FAILED,
                           "Failed to intialize renderer state." }) };
   }

   VertexBufferLayout positionLayout(0, 3, 0);
   _ = positionLayout.Apply();
   if (!_)
   {
      return { false,
               new Error({ STEVE_RENDERER_STATE_INITIALIZATION_FAILED,
                           "Failed to intialize renderer state." }) };
   }

   VertexBufferLayout colorLayout(1, 4, 3);
   _ = colorLayout.Apply();
   if (!_)
   {
      return { false,
               new Error({ STEVE_RENDERER_STATE_INITIALIZATION_FAILED,
                           "Failed to intialize renderer state." }) };
   }

   State m_State = {
      .hasInitialized = true,
      .hasBegunScene  = false,
      .vertices       = std::vector<Vertex>(MAX_VERTICES),
      .vertexArray    = vao,
      .vertexBuffer   = vbo,
      .indexBuffer    = ibo,
      .shaderProgram  = shaderProgram,
   };
   state = CreateRef<State>(m_State);

   return true;
}

Result<bool>
Renderer::BeginScene()
{
   if (!state->hasInitialized)
   {
      return { false,
               new Error({ STEVE_RENDERER_NOT_INITIALIZED,
                           "Renderer not initialized" }) };
   }
   if (state->hasBegunScene)
   {
      return { false,
               new Error({ STEVE_RENDERER_SCENE_ALREADY_BEGUN,
                           "Renderer scene already begun" }) };
   }

   state->hasBegunScene = true;
   state->vertices.clear();

   state->shaderProgram.Use();

   return true;
}

Result<bool>
Renderer::EndScene()
{
   if (!state->hasInitialized)
   {
      return { false,
               new Error({ STEVE_RENDERER_NOT_INITIALIZED,
                           "Renderer not initialized" }) };
   }
   if (!state->hasBegunScene)
   {
      return { false,
               new Error({ STEVE_RENDERER_SCENE_HAS_NOT_BEGUN,
                           "Renderer scene has not begun" }) };
   }
   if (state->vertices.empty()) { return true; }

   auto _ = Result<bool> { false };

   _ = state->vertexBuffer.BindAndUploadData(state->vertices);
   _ = state->shaderProgram.Use();
   glDrawElements(GL_TRIANGLES, MAX_INDICES, GL_UNSIGNED_INT, nullptr);

   Flush();

   return true;
}

std::vector<Vertex>
Renderer::GetVertices()
{
   return state->vertices;
}

void
Renderer::Flush()
{
   state->hasBegunScene = false;
   state->vertices.clear();

   state->vertexArray.Flush();
   state->vertexBuffer.Flush();
}

void
Renderer::DrawVertices(const std::vector<Vertex> &vertices)
{
   auto newSize = state->vertices.size() + vertices.size();
   if (newSize > MAX_VERTICES)
   {
      std::cerr << "Too many vertices" << std::endl;
      return;
   }

   state->vertices.insert(state->vertices.end(),
                          vertices.begin(),
                          vertices.end());
}
