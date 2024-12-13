#pragma once

#include <steve/core/pch>

#include "styles/bound.hpp"
#include "styles/styles.hpp"

namespace steve::ui {
   class Node {
   public:
      class InternalID {
      private:
         std::string m_ID;

      public:
         InternalID() : m_ID("") {}

         InternalID(const std::string &id) : m_ID(id) {}

         InternalID(const InternalID &other) : m_ID(other.m_ID) {}

         InternalID &
         operator=(const InternalID &other) {
            m_ID = other.m_ID;
            return *this;
         }

         inline bool
         operator==(const InternalID &other) const {
            return m_ID == other.m_ID;
         }

         inline bool
         operator!=(const InternalID &other) const {
            return !(*this == other);
         }

         inline std::string
         Get() const {
            return m_ID;
         }

         inline void
         Set(const std::string &id) {
            m_ID = id;
         }
      };

      struct Properties {
         std::string              id;
         std::string              tagName;
         std::vector<std::string> classes;

         Styles styles;

         Properties() : id(""), tagName(""), classes({}), styles() {}

         Properties(const std::string              &id,
                    const std::string              &tagName,
                    const std::vector<std::string> &classes,
                    const Styles                   &styles)
             : id(id), tagName(tagName), classes(classes), styles(styles) {}

         Properties(const Properties &other) = default;

         Properties &
         operator=(const Properties &other) = default;

         Properties(Properties &&other) noexcept = default;

         Properties &
         operator=(Properties &&other) noexcept = default;

         ~Properties() = default;

         inline bool
         operator==(const Properties &other) const {
            return id == other.id && tagName == other.tagName && classes == other.classes &&
                   styles == other.styles;
         }

         inline bool
         operator!=(const Properties &other) const {
            return !(*this == other);
         }
      };

      class PaintBounds {
      private:
         float m_XOffset;
         float m_YOffset;
         float m_CalculatedMinWidth;
         float m_CalculatedMaxWidth;

      public:
         inline PaintBounds()
             : m_XOffset(0.0f), m_YOffset(0.0f), m_CalculatedMinWidth(0.0f), m_CalculatedMaxWidth(0.0f) {}

         inline PaintBounds(float xOffset, float yOffset)
             : m_XOffset(xOffset), m_YOffset(yOffset), m_CalculatedMinWidth(0.0f),
               m_CalculatedMaxWidth(0.0f) {}

         inline PaintBounds(float xOffset, float yOffset, float calculatedMinWidth, float calculatedMaxWidth)
             : m_XOffset(xOffset), m_YOffset(yOffset), m_CalculatedMinWidth(calculatedMinWidth),
               m_CalculatedMaxWidth(calculatedMaxWidth) {}

         inline PaintBounds &
         operator=(const PaintBounds &other) {
            m_XOffset            = other.m_XOffset;
            m_YOffset            = other.m_YOffset;
            m_CalculatedMinWidth = other.m_CalculatedMinWidth;
            m_CalculatedMaxWidth = other.m_CalculatedMaxWidth;

            return *this;
         }

         inline bool
         operator==(const PaintBounds &other) const {
            return m_XOffset == other.m_XOffset && m_YOffset == other.m_YOffset &&
                   m_CalculatedMinWidth == other.m_CalculatedMinWidth &&
                   m_CalculatedMaxWidth == other.m_CalculatedMaxWidth;
         }

         inline bool
         operator!=(const PaintBounds &other) const {
            return !(*this == other);
         }

         inline float
         GetXOffset() const {
            return m_XOffset;
         }

         inline void
         SetXOffset(float xOffset) {
            m_XOffset = xOffset;
         }

         inline float
         GetYOffset() const {
            return m_YOffset;
         }

         inline void
         SetYOffset(float yOffset) {
            m_YOffset = yOffset;
         }

         inline void
         SetOffsets(float xOffset, float yOffset) {
            m_XOffset = xOffset;
            m_YOffset = yOffset;
         }

         inline float
         GetCalculatedMinWidth() const {
            return m_CalculatedMinWidth;
         }

         void
         SetCalculatedMinWidth(float calculatedMinWidth) {
            m_CalculatedMinWidth = calculatedMinWidth;
         }

         inline float
         GetCalculatedMaxWidth() const {
            return m_CalculatedMaxWidth;
         }

         void
         SetCalculatedMaxWidth(float calculatedMaxWidth) {
            m_CalculatedMaxWidth = calculatedMaxWidth;
         }

         inline void
         Reset() {
            m_XOffset            = 0.0f;
            m_YOffset            = 0.0f;
            m_CalculatedMinWidth = 0.0f;
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
      WithParent(Ref<Node> parent);

      static Node
      WithChildren(const std::vector<Ref<Node>> &children);

      inline Properties &
      GetProperties() {
         return m_Properties;
      }

      inline InternalID
      GetInternalID() const {
         return m_InternalID;
      }

      inline PaintBounds &
      GetPaintBounds() {
         return m_PaintBounds;
      }

      bool
      IsChildOf(Ref<Node> node) const;

      bool
      ContainsChildByInternalID(const InternalID &id) const;

      inline Ref<Node>
      GetParent() const {
         return m_Parent;
      }

      inline void
      SetParent(Ref<Node> parent) {
         m_Parent = parent;
      }

      inline std::vector<Ref<Node>>
      GetChildren() const {
         return m_Children;
      }

      inline uint32_t
      GetChildrenCount() const {
         return m_Children.size();
      }

      inline std::vector<Ref<Node>>
      GetSiblingNodes() const {
         if (m_Parent == nullptr) {
            return {};
         }
         return m_Parent->GetChildren();
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

   private:
      void
      CalculateMinBounds();

      void
      CalculatePaintBounds();
   };
}
