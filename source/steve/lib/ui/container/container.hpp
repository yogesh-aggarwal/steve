#pragma once

#include <steve/lib/ui/node/styled_node.hpp>

namespace steve::ui {
   class Container : public StyledNode {
   private:
   public:
      Container();
      ~Container() = default;

      inline Container(const StyledNode &node) : StyledNode(node) {}

      static Container
      FromStyledNode(const StyledNode &node) {
         return Container(node);
      }
   };
}
