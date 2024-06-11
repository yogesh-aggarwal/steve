#pragma once

#include "Styles.hpp"

namespace Steve::DOM
{
   class Node
   {
   private:
      Styles m_Styles;

   public:
      Node()  = default;
      ~Node() = default;
   };
}
