#pragma once

#include <vector>

#include <Steve/Core/Helpers.hpp>

#include "Styles/Bound.hpp"
#include "Styles/Styles.hpp"

namespace Steve::UI
{
   class Node
   {
   public:
      class InternalID
      {
      private:
         std::string m_ID;

      public:
         InternalID() : m_ID("") {}

         InternalID(const std::string &id) : m_ID(id) {}

         InternalID(const InternalID &other) : m_ID(other.m_ID) {}

         InternalID &
         operator=(const InternalID &other)
         {
            m_ID = other.m_ID;
            return *this;
         }

         inline bool
         operator==(const InternalID &other) const
         {
            return m_ID == other.m_ID;
         }

         inline bool
         operator!=(const InternalID &other) const
         {
            return !(*this == other);
         }

         inline std::string
         Get() const
         {
            return m_ID;
         }

         inline void
         Set(const std::string &id)
         {
            m_ID = id;
         }
      };

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

      class PaintBounds
      {
      private:
         StylingSpec::Bound m_VerticalBound;
         StylingSpec::Bound m_HorizontalBound;

      public:
         inline PaintBounds() : m_VerticalBound(0.0f), m_HorizontalBound(0.0f)
         {
         }

         inline PaintBounds(const StylingSpec::Bound &verticalBound,
                            const StylingSpec::Bound &horizontalBound)
             : m_VerticalBound(verticalBound),
               m_HorizontalBound(horizontalBound)
         {
         }

         inline PaintBounds(const PaintBounds &other)
             : m_VerticalBound(other.m_VerticalBound),
               m_HorizontalBound(other.m_HorizontalBound)
         {
         }

         inline PaintBounds &
         operator=(const PaintBounds &other)
         {
            m_VerticalBound   = other.m_VerticalBound;
            m_HorizontalBound = other.m_HorizontalBound;

            return *this;
         }

         inline bool
         operator==(const PaintBounds &other) const
         {
            return m_VerticalBound == other.m_VerticalBound &&
                   m_HorizontalBound == other.m_HorizontalBound;
         }

         inline bool
         operator!=(const PaintBounds &other) const
         {
            return !(*this == other);
         }

         inline StylingSpec::Bound &
         GetVerticalBound()
         {
            return m_VerticalBound;
         }

         inline StylingSpec::Bound &
         GetHorizontalBound()
         {
            return m_HorizontalBound;
         }

         inline void
         SetVerticalBound(const StylingSpec::Bound &bound)
         {
            m_VerticalBound = bound;
         }

         inline void
         SetHorizontalBound(const StylingSpec::Bound &bound)
         {
            m_HorizontalBound = bound;
         }

         inline void
         SetBounds(const StylingSpec::Bound &verticalBound,
                   const StylingSpec::Bound &horizontalBound)
         {
            m_VerticalBound   = verticalBound;
            m_HorizontalBound = horizontalBound;
         }

         inline void
         SetBounds(const PaintBounds &bounds)
         {
            m_VerticalBound   = bounds.m_VerticalBound;
            m_HorizontalBound = bounds.m_HorizontalBound;
         }

         inline void
         Reset()
         {
            m_VerticalBound   = 0.0f;
            m_HorizontalBound = 0.0f;
         }

         inline void
         ResetVerticalBound()
         {
            m_VerticalBound = 0.0f;
         }

         inline void
         ResetHorizontalBound()
         {
            m_HorizontalBound = 0.0f;
         }
      };

   protected:
      Properties  m_Properties;
      PaintBounds m_PaintBounds;

      InternalID             m_InternalID;
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

      inline const Properties &
      GetProperties() const
      {
         return m_Properties;
      }

      inline InternalID
      GetInternalID() const
      {
         return m_InternalID;
      }

      inline PaintBounds
      GetPaintBounds() const
      {
         return m_PaintBounds;
      }

      bool
      IsChildOf(Ref<Node> node) const;

      bool
      ContainsChildByInternalID(const InternalID &id) const;

      inline Ref<Node>
      GetParent() const
      {
         return m_Parent;
      }

      inline std::vector<Ref<Node>>
      GetChildren() const
      {
         return m_Children;
      }

      inline uint32_t
      GetChildrenCount() const
      {
         return m_Children.size();
      }

      void
      PushChild(Ref<Node> node);

      void
      PushChildren(const std::vector<Ref<Node>> &nodes);

      void
      PushChild(const Node &node);

      void
      PushChildren(const std::vector<Node> &nodes);

      void
      RemoveChildByIndex(uint32_t index);

      void
      RemoveChildByInternalID(const InternalID &id);

      void
      CalculateBounds();
   };
}
