#pragma once

#include <Steve/Core/Result.tcc>

class VertexArray
{
private:
   unsigned int m_ID;
   bool         m_HasInitialized = false;

public:
   VertexArray()  = default;
   ~VertexArray() = default;

   Result<bool>
   AllocateAndBind();

   Result<bool>
   Bind();

   Result<bool>
   Unbind();

   inline bool
   HasInitialized() const
   {
      return m_HasInitialized;
   }

   void
   Flush();
};
