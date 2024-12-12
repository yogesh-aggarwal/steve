#include "vertex_array.hpp"

#include <glad/glad.h>

using namespace steve;

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
VertexArray::allocate_and_bind() {
   glGenVertexArrays(1, &m_ID);

   auto res = bind();
   RETURN_IF_ERROR(res);

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
VertexArray::bind() {
   glBindVertexArray(m_ID);

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
VertexArray::unbind() {
   glBindVertexArray(0);

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

void
VertexArray::flush() {
   m_HasInitialized = false;
}

/* ------------------------------------------------------------------------------------------------------- */
