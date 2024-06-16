#pragma once

#include "../Node/StyledNode.hpp"

namespace Steve::UI
{
   class Container : public StyledNode
   {
   private:
   public:
      Container();
      ~Container() = default;

      inline Container(const StyledNode &node) : StyledNode(node) {}

      static Container
      FromStyledNode(const StyledNode &node)
      {
         return Container(node);
      }
   };
}
