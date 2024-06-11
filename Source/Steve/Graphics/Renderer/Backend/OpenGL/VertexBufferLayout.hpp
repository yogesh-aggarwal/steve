#pragma once

#include <stdint.h>

#include <Steve/Core/Result.tcc>

class VertexBufferLayout
{
private:
   // Vertex buffer configuration
   bool     m_Normalized;
   uint32_t m_Location;
   uint32_t m_AttributeSize;
   uint32_t m_Offset;

   // State
   bool m_HasApplied;

public:
   VertexBufferLayout(uint32_t location,
                      uint32_t attributeSize,
                      uint32_t offset);
   ~VertexBufferLayout() = default;

   inline bool
   IsApplied() const
   {
      return m_HasApplied;
   }

   inline uint32_t
   GetLocation() const
   {
      return m_Location;
   }

   inline uint32_t
   GetAttributeSize() const
   {
      return m_AttributeSize;
   }

   inline uint32_t
   GetOffset() const
   {
      return m_Offset;
   }

   Result<bool>
   Apply();
};
