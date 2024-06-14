#pragma once

#include "../Node/StyledNode.hpp"

namespace Steve::DOM
{
   class Container : public StyledNode
   {
   private:
   public:
      Container();
      ~Container() = default;
   };
}
