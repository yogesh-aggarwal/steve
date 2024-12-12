#include "index_buffer.hpp"

#include <glad/glad.h>

/* ------------------------------------------------------------------------------------------------------- */

inline uint32_t
steve::IndexBuffer::get_id() const {
   return m_ID;
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
steve::IndexBuffer::bind_and_populate() {
   if (!m_HasInitialized) {
      glGenBuffers(1, &m_ID);
      m_HasInitialized = true;
   }

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);

   uint32_t indices[MAX_INDICES];
   for (uint32_t i = 0; i < MAX_QUADS; i++) {
      // Two traingles per quad: 0, 1, 2 and 2, 3, 0
      // -------------------------------------------
      // | 0         1 | 0, 1, 2
      indices[i * 6 + 0] = i * 4 + 0;
      indices[i * 6 + 1] = i * 4 + 1;
      indices[i * 6 + 2] = i * 4 + 2;
      // | 3         2 | 2, 3, 0
      indices[i * 6 + 3] = i * 4 + 2;
      indices[i * 6 + 4] = i * 4 + 3;
      indices[i * 6 + 5] = i * 4 + 0;
      // -------------------------------------------
   }

   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
steve::IndexBuffer::bind_and_upload_data(const std::vector<uint32_t> &data) {
   if (!m_HasInitialized) {
      glGenBuffers(1, &m_ID);
      m_HasInitialized = true;
   }

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(uint32_t), data.data(), GL_STATIC_DRAW);

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */
