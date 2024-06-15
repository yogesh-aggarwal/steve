#include "Node.hpp"

Steve::DOM::Node::Node()
    : m_InternalID(), m_Properties({}), m_Parent(nullptr), m_Children({})
{
}

Steve::DOM::Node::Node(const Node &other)
{
   m_Properties = other.m_Properties;
   m_Parent     = other.m_Parent;
   m_Children   = other.m_Children;
}

Steve::DOM::Node
Steve::DOM::Node::WithProperties(const Properties &properties)
{
   Node node;
   node.m_Properties = properties;

   return node;
}

Steve::DOM::Node
Steve::DOM::Node::WithParent(const Ref<Node> &parent)
{
   Node node;
   node.m_Parent = parent;

   return node;
}

Steve::DOM::Node
Steve::DOM::Node::WithChildren(const std::vector<Ref<Node>> &children)
{
   Node node;
   node.m_Children = children;

   return node;
}

bool
Steve::DOM::Node::IsChildOf(Ref<Node> node) const
{
   if (m_Parent == nullptr) { return false; }
   if (m_Parent == node) { return true; }

   return m_Parent->IsChildOf(node);
}

bool
Steve::DOM::Node::ContainsChildByInternalID(const InternalID &id) const
{
   for (const auto &child : m_Children)
   {
      if (child->GetInternalID() == id) { return true; }
   }

   return false;
}

void
Steve::DOM::Node::PushChild(Ref<Node> node)
{
   m_Children.push_back(node);
}

void
Steve::DOM::Node::PushChildren(const std::vector<Ref<Node>> &nodes)
{
   m_Children.insert(m_Children.end(), nodes.begin(), nodes.end());
}

void
Steve::DOM::Node::PushChild(const Node &node)
{
   PushChild(CreateRef<Node>(node));
}

void
Steve::DOM::Node::PushChildren(const std::vector<Node> &nodes)
{
   std::vector<Ref<Node>> children;
   for (const auto &node : nodes)
      children.push_back(CreateRef<Node>(node));
   PushChildren(children);
}

void
Steve::DOM::Node::RemoveChildByIndex(uint32_t index)
{
   m_Children.erase(m_Children.begin() + index);
}

void
Steve::DOM::Node::RemoveChildByInternalID(const InternalID &id)
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
