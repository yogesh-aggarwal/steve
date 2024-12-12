#pragma once

#include <steve/core/pch>

/* ------------------------------------------------------------------------------------------------------- */

namespace steve {
   class VertexArray {
   private:
      unsigned int m_ID;
      bool         m_HasInitialized = false;

   public:
      VertexArray()  = default;
      ~VertexArray() = default;

      VoidResult
      allocate_and_bind();

      VoidResult
      bind();

      VoidResult
      unbind();

      inline bool
      has_initialized() const {
         return m_HasInitialized;
      }

      void
      flush();
   };
}

/* ------------------------------------------------------------------------------------------------------- */
