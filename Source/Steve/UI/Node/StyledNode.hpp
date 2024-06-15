#pragma once

#include "Node.hpp"

namespace Steve::UI
{
   /**
    * @brief
    * A basic wrapper around the `Node` class to add functions related to
    * styling of it. If any class uses this class that simply means that it's
    * explicitly stating of styles being its first class citizen.
    *
    * @details
    * The class contain various functionality to read, modify & work with
    * styles & make up a rich support rather than using plain `std::map` or
    * something similar which will slows down the performance also down the road
    * as far rendering is concerned.
    */
   class StyledNode : public Node
   {
   public:
      StyledNode() = default;

      /**
       * Constructor to initialize the UI node with existing node.
       *
       * @param node Node that is to be copied over to the styled node.
       */
      StyledNode(const Node &node);

      /**
       * Named constructor to initialize the UI node with existing node.
       *
       * @param node Node that is to be copied over to the styled node.
       */
      static StyledNode
      FromNode(const Node &node);

      /**
       * Named constructor to initialize the UI node with existing stylings.
       *
       * @param styles Stylings that are to be copied over to the node.
       */
      static StyledNode
      WithStyles(const Styles &styles);

      /**
       * Helper function to override existing styling with the new one.
       *
       * @param styles Stylings that are to be copied over to the node.
       */
      void
      UpdateStyles(const Styles &styles);
   };
}
