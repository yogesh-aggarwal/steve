#pragma once

#include "vertex_array.hpp"
#include "vertex_buffer_layout.hpp"

#include <vector>
#include <glad/glad.h>

#include <steve/lib/graphics/renderer/vertex.hpp>

/* ------------------------------------------------------------------------------------------------------- */

namespace steve {
   class VertexBuffer {
   private:
      uint32_t            m_ID;
      bool                m_HasInitialized;
      std::vector<Vertex> m_Vertices {};

   public:
      VertexBuffer() = default;

      VoidResult
      bind_and_allocate();

      VoidResult
      bind_and_upload_data(const std::vector<Vertex> &data);

      VoidResult
      bind();

      VoidResult
      unbind();

      void
      flush();

      inline uint32_t
      get_id() const {
         return m_ID;
      }

      inline bool
      has_initialized() const {
         return m_HasInitialized;
      }
   };
}

/* ------------------------------------------------------------------------------------------------------- */