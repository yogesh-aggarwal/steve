#pragma once

#include <vector>

#include <glad/glad.h>

#include <Steve/Objects/Vertex.hpp>
#include <Steve/Objects/VertexArray.hpp>
#include <Steve/Objects/VertexBufferLayout.hpp>

class VertexBuffer
{
private:
   bool                m_HasInitialized;
   uint32_t            m_ID;
   std::vector<Vertex> m_Vertices {};

public:
   VertexBuffer() = default;

   Result<bool>
   BindAndAllocate();

   Result<bool>
   BindAndUploadData(const std::vector<Vertex> &data);

   Result<bool>
   Bind();

   Result<bool>
   Unbind();

   inline uint32_t
   GetID() const
   {
      return m_ID;
   }
};
