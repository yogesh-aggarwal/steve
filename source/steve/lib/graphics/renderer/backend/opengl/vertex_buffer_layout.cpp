#include "vertex_buffer_layout.hpp"

#include <glad/glad.h>

#include <steve/lib/graphics/renderer/vertex.hpp>

using namespace steve;

/* ------------------------------------------------------------------------------------------------------- */

VertexBufferLayout::VertexBufferLayout(uint32_t location, uint32_t attributeSize, uint32_t offset)
    : m_Location(location), m_AttributeSize(attributeSize), m_Offset(offset) {}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
VertexBufferLayout::apply() {
   glEnableVertexAttribArray(m_Location);
   glVertexAttribPointer(m_Location,
                         m_AttributeSize,
                         GL_FLOAT,
                         GL_FALSE,
                         sizeof(Vertex),
                         (void *)(m_Offset * sizeof(float)));

   // TODO: Check for errors
   m_HasApplied = true;

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */
