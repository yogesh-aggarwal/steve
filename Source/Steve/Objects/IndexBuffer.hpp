#pragma once

#include <vector>
#include <Steve/Core/Result.tcc>

class IndexBuffer
{
private:
   uint32_t m_ID;
   bool     m_HasInitialized;

public:
   IndexBuffer() = default;

   Result<bool>
   BindAndPopulate();

   Result<bool>
   BindAndUploadData(const std::vector<uint32_t> &data);

   inline uint32_t
   GetID() const
   {
      return m_ID;
   }
};
