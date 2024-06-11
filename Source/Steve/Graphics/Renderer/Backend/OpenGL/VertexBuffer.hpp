#pragma once

#include <vector>

#include <glad/glad.h>

#include <Steve/Graphics/Renderer/Core/Vertex.hpp>

#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"

class VertexBuffer
{
private:
   uint32_t            m_ID;
   bool                m_HasInitialized;
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

   void
   Flush();

   inline uint32_t
   GetID() const
   {
      return m_ID;
   }

   inline bool
   HasInitialized() const
   {
      return m_HasInitialized;
   }
};
