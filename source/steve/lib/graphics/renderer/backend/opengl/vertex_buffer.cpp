#include "vertex_buffer.hpp"

/* ------------------------------------------------------------------------------------------------------- */

using namespace steve;

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
VertexBuffer::bind_and_allocate() {
   // TODO: Check for errors

   if (!m_HasInitialized) {
      glGenBuffers(1, &m_ID);
      m_HasInitialized = true;
   }

   glBindBuffer(GL_ARRAY_BUFFER, m_ID);
   glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
VertexBuffer::bind_and_upload_data(const std::vector<Vertex> &data) {
   if (!m_HasInitialized) {
      return Error("Vertex buffer not initialized.");
   }

   if (data.size() > MAX_VERTICES) {
      return Error("Too many vertices.");
   }

   glBindBuffer(GL_ARRAY_BUFFER, m_ID);

   // DGLERROR;

   glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(Vertex), data.data());

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
VertexBuffer::bind() {
   // TODO: Check for errors

   if (!m_HasInitialized) {
      return Error("Vertex buffer not initialized.");
   }

   glBindBuffer(GL_ARRAY_BUFFER, m_ID);

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
VertexBuffer::unbind() {
   // TODO: Check for errors

   if (!m_HasInitialized) {
      return Error("Vertex buffer not initialized.");
   }

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

void
VertexBuffer::flush() {
   m_HasInitialized = false;
}

/* ------------------------------------------------------------------------------------------------------- */
