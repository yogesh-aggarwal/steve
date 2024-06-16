#include "Node.hpp"

#include <iostream>
#include <algorithm>

#include <Steve/Application/ApplicationWindow.hpp>

Steve::UI::Node::Node()
    : m_InternalID(), m_Properties({}),
      m_PaintBounds(
          { m_Properties.styles.GetWidth(), m_Properties.styles.GetHeight() }),
      m_Parent(nullptr), m_Children({})
{
}

Steve::UI::Node::Node(const Node &other)
    : m_InternalID(other.m_InternalID), m_Properties(other.m_Properties),
      m_Parent(other.m_Parent), m_Children(other.m_Children),
      m_PaintBounds(other.m_PaintBounds)
{
}

Steve::UI::Node
Steve::UI::Node::WithProperties(const Properties &properties)
{
   Node node;
   node.m_Properties = properties;

   return node;
}

Steve::UI::Node
Steve::UI::Node::WithParent(Ref<Node> parent)
{
   Node node;
   node.m_Parent = parent;

   return node;
}

Steve::UI::Node
Steve::UI::Node::WithChildren(const std::vector<Ref<Node>> &children)
{
   Node node;
   node.m_Children = children;

   return node;
}

bool
Steve::UI::Node::IsChildOf(Ref<Node> node) const
{
   if (m_Parent == nullptr) { return false; }
   if (m_Parent == node) { return true; }

   return m_Parent->IsChildOf(node);
}

bool
Steve::UI::Node::ContainsChildByInternalID(const InternalID &id) const
{
   for (const auto &child : m_Children)
   {
      if (child->GetInternalID() == id) { return true; }
   }

   return false;
}

void
Steve::UI::Node::PushChild(Ref<Node> node)
{
   m_Children.push_back(node);
}

void
Steve::UI::Node::PushChildren(const std::vector<Ref<Node>> &nodes)
{
   m_Children.insert(m_Children.end(), nodes.begin(), nodes.end());
}

void
Steve::UI::Node::PushChild(const Node &node)
{
   PushChild(CreateRef<Node>(node));
}

void
Steve::UI::Node::PushChildren(const std::vector<Node> &nodes)
{
   std::vector<Ref<Node>> children;
   for (const auto &node : nodes)
      children.push_back(CreateRef<Node>(node));
   PushChildren(children);
}

void
Steve::UI::Node::RemoveChildByIndex(uint32_t index)
{
   m_Children.erase(m_Children.begin() + index);
}

void
Steve::UI::Node::RemoveChildByInternalID(const InternalID &id)
{
   for (size_t i = 0; i < m_Children.size(); i++)
   {
      if (m_Children[i]->GetInternalID() == id)
      {
         m_Children.erase(m_Children.begin() + i);
         break;
      }
   }
}

void
Steve::UI::Node::CalculateBounds()
{
   /* If the parent is null, then the bounds are the window bounds (for now) */
   if (!m_Parent)
   {
      /* Horizontal bounds */
      if (!m_PaintBounds.GetHorizontalBound().IsMaxBoundDefined())
         m_PaintBounds.GetHorizontalBound().SetMax(
             (float)ApplicationWindow::GetWidth());

      /* Vertical bounds */
      if (!m_PaintBounds.GetVerticalBound().IsMaxBoundDefined())
         m_PaintBounds.GetVerticalBound().SetMax(
             (float)ApplicationWindow::GetHeight());
   }
   /* Prepare paint bound */
   else
   {
      auto parentPadding     = m_Parent->GetProperties().styles.GetPadding();
      auto parentPaintBounds = m_Parent->GetPaintBounds();

      /**
       * *** Read it only when then sections of the below code mention about it.
       *
       * NOTE:
       *
       * If the defined width/height is less than the parent's vertical bound
       * then it's perfectly fine as there will be no overflow. But if
       * there's then we must try to prevent overflow artifcats such as
       * the current `Container` getting cut off by the parent's bounds.
       *
       * To do so, we'll reduce the indicated width/height by the parent's
       * padding and set it as the max bound. If the width/height is still
       * greater than the parent's max bound, then there will be a scroll
       * bar which has not implemented yet.
       *
       * TODO: Implement scroll bars.
       */

      /* Horizontal bounds */
      {
         auto definedWidth          = m_Properties.styles.GetWidth();
         auto parentHorizontalBound = parentPaintBounds.GetHorizontalBound();

         float nodeWidth = definedWidth.IsBoundDefined()
                               ? definedWidth.GetValue()
                               : parentHorizontalBound.GetMax();

         auto parentHorizontalPadding =
             parentPadding.GetLeft() + parentPadding.GetRight();

         /* Refer to the note above */
         bool isOverflowing = nodeWidth + parentHorizontalPadding >
                              parentHorizontalBound.GetMax();
         if (isOverflowing)
            nodeWidth =
                parentHorizontalBound.GetMax() - parentHorizontalPadding;

         m_PaintBounds.GetHorizontalBound().Set(nodeWidth);
         m_PaintBounds.SetXOffset(parentPadding.GetLeft());
      }

      /* Vertical bounds */
      {
         auto definedHeight       = m_Properties.styles.GetHeight();
         auto parentVerticalBound = parentPaintBounds.GetVerticalBound();

         float nodeHeight = definedHeight.IsBoundDefined()
                                ? definedHeight.GetValue()
                                : parentVerticalBound.GetMin();
         if (nodeHeight == -1.0f) nodeHeight = 0.0f;

         auto parentVerticalPadding =
             parentPadding.GetTop() + parentPadding.GetBottom();

         /* Refer to the note above */
         bool isOverflowing =
             nodeHeight + parentVerticalPadding > parentVerticalBound.GetMax();
         if (isOverflowing)
            nodeHeight = parentVerticalBound.GetMax() - parentVerticalPadding;

         m_PaintBounds.GetVerticalBound().Set(nodeHeight);
         m_PaintBounds.SetYOffset(parentPadding.GetTop());
      }
   }

   /* Make every child re-calculate its bounds */
   for (const auto &child : m_Children)
      child->CalculateBounds();
}
