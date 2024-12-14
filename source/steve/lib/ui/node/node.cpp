#include "node.hpp"

#include <iostream>
#include <algorithm>

#include <steve/lib/application/window.hpp>

/* ------------------------------------------------------------------------------------------------------- */

using namespace steve;

/* ------------------------------------------------------------------------------------------------------- */

ui::Node::Node() : m_InternalID(), m_Properties({}), m_PaintBounds(), m_Parent(nullptr), m_Children({}) {}

/* ------------------------------------------------------------------------------------------------------- */

ui::Node::Node(const Node &other)
    : m_InternalID(other.m_InternalID), m_Properties(other.m_Properties), m_Parent(other.m_Parent),
      m_Children(other.m_Children), m_PaintBounds(other.m_PaintBounds) {}

/* ------------------------------------------------------------------------------------------------------- */

ui::Node
ui::Node::WithProperties(const Properties &properties) {
   Node node;
   node.m_Properties = properties;

   return node;
}

/* ------------------------------------------------------------------------------------------------------- */

ui::Node
ui::Node::WithParent(Ref<Node> parent) {
   Node node;
   node.m_Parent = parent;

   return node;
}

/* ------------------------------------------------------------------------------------------------------- */

ui::Node
ui::Node::WithChildren(const std::vector<Ref<Node>> &children) {
   Node node;
   node.m_Children = children;

   return node;
}

/* ------------------------------------------------------------------------------------------------------- */

bool
ui::Node::IsChildOf(Ref<Node> node) const {
   if (m_Parent == nullptr) {
      return false;
   }
   if (m_Parent == node) {
      return true;
   }

   return m_Parent->IsChildOf(node);
}

/* ------------------------------------------------------------------------------------------------------- */

bool
ui::Node::ContainsChildByInternalID(const InternalID &id) const {
   for (const auto &child : m_Children) {
      if (child->GetInternalID() == id) {
         return true;
      }
   }

   return false;
}

/* ------------------------------------------------------------------------------------------------------- */

void
ui::Node::PushChild(Ref<Node> node) {
   m_Children.push_back(node);
}

/* ------------------------------------------------------------------------------------------------------- */

void
ui::Node::PushChildren(const std::vector<Ref<Node>> &nodes) {
   m_Children.insert(m_Children.end(), nodes.begin(), nodes.end());
}

/* ------------------------------------------------------------------------------------------------------- */

void
ui::Node::PushChild(const Node &node) {
   PushChild(CreateRef<Node>(node));
}

/* ------------------------------------------------------------------------------------------------------- */

void
ui::Node::PushChildren(const std::vector<Node> &nodes) {
   std::vector<Ref<Node>> children;
   for (const auto &node : nodes)
      children.push_back(CreateRef<Node>(node));
   PushChildren(children);
}

/* ------------------------------------------------------------------------------------------------------- */

void
ui::Node::RemoveChildByIndex(uint32_t index) {
   m_Children.erase(m_Children.begin() + index);
}

/* ------------------------------------------------------------------------------------------------------- */

void
ui::Node::RemoveChildByInternalID(const InternalID &id) {
   for (size_t i = 0; i < m_Children.size(); i++) {
      if (m_Children[i]->GetInternalID() == id) {
         m_Children.erase(m_Children.begin() + i);
         break;
      }
   }
}

/* ------------------------------------------------------------------------------------------------------- */

void
ui::Node::CalculateBounds() {
   if (!m_Parent) {
      m_PaintBounds.SetCalculatedMaxWidth(m_Properties.styles.GetWidth().GetValue());
      m_PaintBounds.SetCalculatedMinWidth(m_Properties.styles.GetWidth().GetValue());
   }

   CalculateMinBounds();
   CalculatePaintBounds();
}

/* ------------------------------------------------------------------------------------------------------- */

void
ui::Node::CalculateMinBounds() {
   // If the node has children, calculate the bounds of the children first.
   float minWidth = m_Properties.styles.GetWidth().GetMin();
   if (m_Children.size()) {
      // Make every child calculate its minimum width
      for (auto child : m_Children)
         child->CalculateMinBounds();

      // Calculate the minimum width of the children and set it as the minimum
      // width of current node (because it's the parent of all of them).
      float childrenMinWidthSum = 0;
      for (const auto &child : m_Children)
         childrenMinWidthSum += child->GetPaintBounds().GetCalculatedMinWidth();

      // The minimum width of the parent node is the maximum between the minimum
      // width of the parent node and the sum of the minimum width of all
      // children.
      minWidth = std::max(minWidth, childrenMinWidthSum);
   }

   // TODO: Include other factors as well such as fonts and paddings.

   // Set the calculated minimum width of the node.
   m_PaintBounds.SetCalculatedMinWidth(minWidth);
}

/* ------------------------------------------------------------------------------------------------------- */

void
ui::Node::CalculatePaintBounds() {
   if (!m_Children.size())
      return;

   int nNodesWithWidth = 0;
   for (auto child : m_Children)
      if (child->GetPaintBounds().GetCalculatedMinWidth())
         nNodesWithWidth++;

   float width         = m_PaintBounds.GetCalculatedMaxWidth();
   float eachNodeWidth = width / nNodesWithWidth;

   float variableWidth     = width;
   int   nStaticWidthNodes = 0;
   for (auto child : m_Children) {
      const float minNodeWidth = child->GetPaintBounds().GetCalculatedMinWidth();
      if (minNodeWidth > eachNodeWidth) {
         variableWidth -= minNodeWidth;
         nStaticWidthNodes++;
      }
   }

   int   nVariableNodes        = nNodesWithWidth - nStaticWidthNodes;
   float eachVariableNodeWidth = variableWidth / nVariableNodes;

   float xOffset = 0;
   for (auto child : m_Children) {
      float width = child->GetPaintBounds().GetCalculatedMinWidth();
      if (width < eachNodeWidth)
         width = eachVariableNodeWidth;

      child->GetPaintBounds().SetXOffset(xOffset);
      child->GetPaintBounds().SetYOffset(0);
      child->GetPaintBounds().SetCalculatedMaxWidth(width);

      child->CalculatePaintBounds();

      xOffset += width;
   }
}

/* ------------------------------------------------------------------------------------------------------- */
