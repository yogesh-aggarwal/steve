#pragma once

#include <steve/core/pch>

/* ------------------------------------------------------------------------------------------------------- */

namespace steve {
   class IndexBuffer {
   private:
      uint32_t m_ID;
      bool     m_HasInitialized;

   public:
      IndexBuffer() = default;

      inline uint32_t
      get_id() const;

      VoidResult
      bind_and_populate();

      VoidResult
      bind_and_upload_data(const std::vector<uint32_t> &data);
   };
}

/* ------------------------------------------------------------------------------------------------------- */
