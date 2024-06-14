#pragma once

#include <vector>

#include <Steve/Core/Helpers.hpp>

#include "Styles/Styles.hpp"

namespace Steve::DOM
{
   class Node
   {
   public:
      struct Properties
      {
         std::string              id;
         std::string              tagName;
         std::vector<std::string> classes;

         Styles styles;

         Properties() : id(""), tagName(""), classes({}), styles() {}

         Properties(const std::string              &id,
                    const std::string              &tagName,
                    const std::vector<std::string> &classes,
                    const Styles                   &styles)
             : id(id), tagName(tagName), classes(classes), styles(styles)
         {
         }

         Properties(const Properties &other) = default;

         Properties &
         operator=(const Properties &other) = default;

         Properties(Properties &&other) noexcept = default;

         Properties &
         operator=(Properties &&other) noexcept = default;

         ~Properties() = default;

         inline bool
         operator==(const Properties &other) const
         {
            return id == other.id && tagName == other.tagName &&
                   classes == other.classes && styles == other.styles;
         }

         inline bool
         operator!=(const Properties &other) const
         {
            return !(*this == other);
         }
      };

   protected:
      Properties m_Properties;

      Ref<Node>              m_Parent;
      std::vector<Ref<Node>> m_Children;

   public:
      Node();

      Node(const Node &other);

      static Node
      WithProperties(const Properties &properties);

      static Node
      WithParent(const Ref<Node> &parent);

      static Node
      WithChildren(const std::vector<Ref<Node>> &children);
   };
}
