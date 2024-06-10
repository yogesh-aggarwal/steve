
#pragma once

#include <vector>

#include <Steve/Core/Result.tcc>
#include <Steve/Objects/Vertex.hpp>
#include <Steve/Objects/VertexArray.hpp>
#include <Steve/Objects/VertexBuffer.hpp>
#include <Steve/Objects/IndexBuffer.hpp>
#include <Steve/Shader/ShaderProgram.hpp>

namespace Renderer
{
   struct State
   {
      bool                hasInitialized;
      bool                hasBegunScene;
      std::vector<Vertex> vertices;

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

   void
   Flush();

   void
   DrawVertices(const std::vector<Vertex> &vertices);

   void
   PrintVertices();
};
