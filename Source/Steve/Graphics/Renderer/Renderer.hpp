
#pragma once

#include <vector>

#include <Steve/Core/Result.tcc>

#include "Backend/Backend.hpp"

namespace Renderer
{
   struct State
   {
      bool                hasInitialized;
      bool                hasBegunScene;
      std::vector<Vertex> vertices;

      glm::vec4 clearColor;

      VertexArray   vertexArray;
      VertexBuffer  vertexBuffer;
      IndexBuffer   indexBuffer;
      ShaderProgram shaderProgram;
   };

   inline bool
   HasInitialized();

   Result<bool>
   Initialize();

   Result<bool>
   BeginScene();

   Result<bool>
   EndScene();

   std::vector<Vertex>
   GetVertices();

   glm::vec4
   GetClearColor();

   void
   SetClearColor(const glm::vec4 &color);

   void
   Flush();

   void
   DrawVertices(const std::vector<Vertex> &vertices);

   void
   PrintVertices();
};
