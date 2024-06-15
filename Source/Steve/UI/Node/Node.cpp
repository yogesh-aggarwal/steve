#include "Node.hpp"

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
Steve::UI::Node::WithParent(const Ref<Node> &parent)
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
      m_PaintBounds.GetHorizontalBound().Set(
          (float)ApplicationWindow::GetWidth());
      m_PaintBounds.GetVerticalBound().Set(
          (float)ApplicationWindow::GetHeight());

      /* Horizontal bounds */
      if (!m_PaintBounds.GetHorizontalBound().IsMaxBoundDefined()) {}

      /* Vertical bounds */
      if (!m_PaintBounds.GetVerticalBound().IsMaxBoundDefined()) {}

      return;
   }

   /* Prepare paint bound */
   {
      auto parentPaintBounds     = m_Parent->GetPaintBounds();
      auto parentHorizontalBound = parentPaintBounds.GetHorizontalBound();
      auto parentVerticalBound   = parentPaintBounds.GetVerticalBound();
      auto paintHorizontalBound  = m_PaintBounds.GetHorizontalBound();
      auto paintVerticalBound    = m_PaintBounds.GetVerticalBound();
      auto definedWidth          = m_Properties.styles.GetWidth();
      auto definedHeight         = m_Properties.styles.GetHeight();

      /* Horizontal bounds */
      if (parentHorizontalBound.GetMax() > paintHorizontalBound.GetMax())
         paintHorizontalBound.SetMax(parentHorizontalBound.GetMax());
      else if (definedWidth.GetMin() > paintHorizontalBound.GetMin())
         paintHorizontalBound.SetMin(definedWidth.GetMin());

      /* Vertical bounds */
      if (parentVerticalBound.GetMax() > paintVerticalBound.GetMax())
         paintVerticalBound.SetMax(parentVerticalBound.GetMax());
      else if (definedHeight.GetMin() > paintVerticalBound.GetMin())
         paintVerticalBound.SetMin(definedHeight.GetMin());
   }

   /* Make every child re-calculate its bounds */
   for (const auto &child : m_Children)
      child->CalculateBounds();
}
