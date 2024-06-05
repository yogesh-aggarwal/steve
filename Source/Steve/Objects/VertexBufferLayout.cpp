#include "VertexBufferLayout.hpp"

#include <glad/glad.h>
#include <Steve/Objects/Vertex.hpp>

VertexBufferLayout::VertexBufferLayout(uint32_t location,
                                       uint32_t attributeSize,
                                       uint32_t offset)
    : m_Location(location), m_AttributeSize(attributeSize), m_Offset(offset)
{
}

Result<bool>
VertexBufferLayout::Apply()
{
   glEnableVertexAttribArray(m_Location);
   glVertexAttribPointer(m_Location,
                         m_AttributeSize,
                         GL_FLOAT,
                         GL_FALSE,
                         sizeof(Vertex),
                         (void *)(m_Offset * sizeof(float)));

   // TODO: Check for errors
   m_HasApplied = true;

   return true;
}
