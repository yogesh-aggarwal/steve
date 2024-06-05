
#pragma once

#include <vector>

#include <Steve/Core/Result.tcc>
#include <Steve/Objects/Vertex.hpp>
#include <Steve/Objects/VertexArray.hpp>
#include <Steve/Objects/VertexBuffer.hpp>
#include <Steve/Objects/IndexBuffer.hpp>
#include <Steve/Shader/ShaderProgram.hpp>

class Renderer
{
public:
   bool                m_HasInitialized;
   bool                m_HasBegunScene;
   std::vector<Vertex> m_Vertices;

   VertexArray   m_VertexArray;
   VertexBuffer  m_VertexBuffer;
   IndexBuffer   m_IndexBuffer;
   ShaderProgram m_ShaderProgram;

public:
   Renderer(ShaderProgram shaderProgram);
   ~Renderer();

   inline bool
   HasInitialized() const
   {
      return m_HasInitialized;
   }

   Result<bool>
   Initialize();

   Result<bool>
   BeginScene();

   Result<bool>
   EndScene();

   void
   Flush();

   Result<bool>
   DrawVertices(const std::vector<Vertex> &vertices);
};
