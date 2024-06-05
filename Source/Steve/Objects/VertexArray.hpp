#pragma once

#include <Steve/Core/Result.tcc>

class VertexArray
{
private:
   unsigned int m_ID;

public:
   VertexArray()  = default;
   ~VertexArray() = default;

   Result<bool>
   AllocateAndBind();

   Result<bool>
   Bind();

   Result<bool>
   Unbind();
};
