#pragma once

#include <stdint.h>

#include <steve/core/pch>

/* ------------------------------------------------------------------------------------------------------- */

namespace steve {
   class VertexBufferLayout {
   private:
      // Vertex buffer configuration
      bool     m_Normalized;
      uint32_t m_Location;
      uint32_t m_AttributeSize;
      uint32_t m_Offset;

      // State
      bool m_HasApplied;

   public:
      VertexBufferLayout(uint32_t location, uint32_t attribute_size, uint32_t offset);
      ~VertexBufferLayout() = default;

      inline bool
      is_applied() const {
         return m_HasApplied;
      }

      inline uint32_t
      get_location() const {
         return m_Location;
      }

      inline uint32_t
      get_attribute_size() const {
         return m_AttributeSize;
      }

      inline uint32_t
      get_offset() const {
         return m_Offset;
      }

      VoidResult
      apply();
   };
}

/* ------------------------------------------------------------------------------------------------------- */
